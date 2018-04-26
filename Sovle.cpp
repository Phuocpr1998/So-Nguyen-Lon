#include "stdafx.h"
#include "Solve.h"

// đưa bit vào vị trí k của biến data
void SetBit(QInt& data, int k, bool bit) {
	int index = k / BIT;// ô có bit cần bật
	int indexBit = BIT - 1 - k % BIT; // vị trí bit trong ô cần bật
	if (bit == 1)
		data.data[index] |= (bit << indexBit); // bật chuyển bit thứ k lên 1
	else
		data.data[index] &= ~(1 << indexBit); // chuyển bit thứ k về 0
}

// lấy ra bit tại vị trí vt trong data
bool GetBit(QInt& data, int k)
{
	int index = k / BIT;// ô có bit cần lấy
	int indexBit = BIT - 1 - k % BIT; // vị trí bit trong ô cần lấy
	return (data.data[index] >> indexBit) & 1;
}

// chia chuỗi cho 2 lấy dư là phần bit
string Divide2String(string value, bool &bit)
{
	// 0 is 48
	if ((int)value[value.length() - 1] % 2 == 0)
		bit = 0;
	else
		bit = 1;
	// chia 2
	string temp = "";
	int d = 0, n = value.length(), mod = 0;

	for (int i = 0; i < n; i++)
	{
		// lấy từng phần tử chia cho 2 lấy dư
		d = (int)(value[i] - '0') + mod * 10;
		mod = d % 2;
		d /= 2;
		if (d == 0 && i == 0)
			continue;

		temp += to_string(d);
	}
	return temp;
}
// chuyển bù 2
QInt soBu2(QInt data)
{
	// chuyển số bù 1:
	for (int i = 0; i < LENGTH; i++)
	{
		data.data[i] = ~data.data[i];
	}
	// +1 chuyển bù 2
	int bitNho = 1;// bit nhớ
	for (int i = 127; i >= 0; i--)
	{
		if (bitNho == 1)
		{
			bool b = GetBit(data, i);
			if (b == 1)
			{
				SetBit(data, i, 0);
			}
			else
			{
				bitNho = 0;
				SetBit(data, i, 1);
			}
		}
	}
	return data;
}

// cộng chuỗi hai số dương
string StringPlus(string str1, string str2)
{
	string value = "";
	if (str2.length() > str1.length())
	{
		string temp = str1;
		str1 = str2;
		str2 = temp;
	}

	// cộng
	string result = "";
	int n = str1.length(), k = 0, d = 0;
	int m = str1.length() - str2.length();
	for (int i = n - 1; i >= 0; i--)
	{
		if (i - m >= 0)
		{
			d = (int)(str1[i] - '0') + (int)(str2[i - m] - '0') + k;
		}
		else if (k != 0)
		{
			d = (int)(str1[i] - '0') + k;
		}
		else if (k == 0)
		{
			d = (int)(str1[i] - '0');
		}

		k = d / 10;
		d %= 10;
		result += to_string(d);
	}
	// có thể tràn
	if (k != 0)
		result += to_string(k);

	// đọc ngược dãy lại lấy kết quả cộng
	n = result.length();
	for (int i = n - 1; i >= 0; i--)
	{
		value += result[i];
	}

	return value;
}
// nhân chuỗi với 2
string MultiString2(string data)
{
	string temp = "";
	int n = data.length();
	int d = 0, k = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		d = (int)(data[i] - '0') * 2 + k;
		k = d / 10;
		d %= 10;

		temp += to_string(d);
	}

	if (k != 0)
		temp += to_string(k);

	string result = "";
	n = temp.length();
	for (int i = n - 1; i >= 0; i--)
	{
		result += temp[i];
	}
	return result;
}
// hàm tính lũy thừa 2
string exp2String(int exp)
{
	string result = "1";
	if (exp < 0)
	{
		return "0";
	}
	for (int i = 0; i < exp; i++)
	{
		result = MultiString2(result);
	}
	return result;
}
//
QInt convertStringToQInt(string value)
{
	QInt x;
	x = 0;
	bool negative = false;

	if (value[0] == '-')
	{
		negative = true;
		value[0] = '0';
	}
	else if (value[0] == '+')
	{
		value[0] = '0';
	}
	bool bit = 0;
	int vt = 127;
	while (value != "0" && value != "")
	{
		value = Divide2String(value, bit);
		SetBit(x, vt, bit);
		vt--;
	}

	if (negative == true) // số âm thì lưu bù 2
	{
		x = soBu2(x);
	}
	return x;
}
//
string convertQIntToString(QInt x)
{
	string value = "";
	if (GetBit(x, 0) == 1) // số âm
	{
		x = soBu2(x);
		value += "-";
	}

	string result = "0";
	for (int i = 127; i >= 1; i--)
	{
		if (GetBit(x, i) == 1)
		{
			result = StringPlus(result, exp2String(128 - 1 - i));
		}
	}

	value += result;
	return value;
}
// 
void ScanQInt(QInt &x)
{
	string temp = "";
	cout << "Nhap so nguyen: ";
	cin >> temp;
	x = convertStringToQInt(temp);
}

//
void PrintQInt(QInt x)
{
	string value = convertQIntToString(x);
	cout << value;
}

QInt operator+(QInt num1, QInt num2) 
{
	QInt sum;
	sum = 0;
	int index, indexBit, mark = 0;
	for (int i = SIZE - 1; i >= 0; i--) 
	{
		int s = GetBit(num1,i) + GetBit(num2,i) + mark; //cộng từng bit có nhớ
		if (s == 1) 
		{ // nếu tổng là 1
			mark = 0; //nhớ 0
			SetBit(sum, i, 1);// chuyển bit thứ i thành 1
		}
		else if (s == 2) 
		{// nếu tổng là 2
			mark = 1;//nhớ 1
			SetBit(sum, i, 0);// chuyển bit thứ i thành 0
		}
		else if (s == 3) 
		{// nếu tổng là 3
			mark = 1;//nhớ 1
			SetBit(sum, i, 1);// chuyển bit thứ i thành 1
		}
		else if (s == 0) 
		{ // nếu tổng là 0
			mark = 0;//nhớ 0
			SetBit(sum, i, 0);// chuyển bit thứ i thành 0
		}
	}
	return sum; // trả về tổng
}

QInt operator-(QInt num1, QInt num2) {
	QInt temp, sub;
	temp = 0;
	sub = 0;
	temp = soBu2(num2); // lấy số bù 2 của num2
	sub = num1 + temp;	// dùng toán tử cộng cộng 2 số
	return sub;			//trả về kết quả
}

QInt operator&(QInt num1, QInt num2) {
	QInt result;
	result = 0;
	for (int i = 0; i < LENGTH; i++) {
		result.data[i] = num1.data[i] & num2.data[i];
	}
	return result;
}

QInt operator|(QInt num1, QInt num2) {
	QInt result;
	result = 0;
	for (int i = 0; i < LENGTH; i++) {
		result.data[i] = num1.data[i] | num2.data[i];
	}
	return result;
}

QInt operator^(QInt num1, QInt num2) {
	QInt result;
	result = 0;
	for (int i = 0; i < LENGTH; i++) {
		result.data[i] = num1.data[i] ^ num2.data[i];
	}
	return result;
}

QInt operator~(QInt num) {
	QInt result;
	result = 0;
	for (int i = 0; i < LENGTH; i++) {
		result.data[i] = ~num.data[i];
	}
	return result;
}

QInt operator >> (QInt num, int countBit) {
	QInt result;
	result = 0;
	while (countBit > 0) {
		int count = 0;
		if (countBit > 31) {
			count = 31;
			countBit -= 31;
		}
		else
		{
			count = countBit;
			countBit = 0;
		}
		int temp1 = 0, temp2;
		temp1 = (num.data[0] << (BIT - count));		//nếu bit đầu tiên bằng 1 thì ta dịch theo kiểu toán học ngược lại thì theo kiểu luận lý
		result.data[0] = num.data[0] >> count;
		for (int i = 1; i < LENGTH; i++) {
			temp2 = (num.data[i] << (BIT - count));	//giữ lại count bit cuối của num.data[i]
			bool flag = false;						//biến làm cờ
			if (num.data[i] < 0) {					// nếu bit đầu của num.data[i] == 1
				num.data[i] &= ~(1 << (BIT - 1));	// chuyển bit đầu của num.data[i] về 0
				flag = true;						//đánh dấu có chuyển
			}
			result.data[i] = (num.data[i] >> count) | temp1;	//thêm count bit dư ở chỉ số trước vào đầu
			if (flag == true)						//nếu có chuyển bit thì trả lại như cũ
				result.data[i] |= (1 << (BIT - count - 1));
			temp1 = temp2;
		}
		num = result;
	}
	return result;
}

QInt operator >> (QInt num, QInt countBit)
{
	return num >> countBit.data[LENGTH - 1];
}

QInt operator<<(QInt num, int countBit) {
	QInt result;
	result = 0;
	while (countBit > 0) {
		int count = 0;
		if (countBit > 31) {
			count = 31;
			countBit -= 31;
		}
		else
		{
			count = countBit;
			countBit = 0;
		}
		int temp1 = 0, temp2;
		temp1 = (num.data[LENGTH - 1] >> (BIT - count)) << (BIT - count);
		result.data[LENGTH - 1] = (num.data[LENGTH - 1] << count);
		for (int i = LENGTH - 2; i >= 0; i--) 
		{
			temp2 = (num.data[i] >> (BIT - count)) << (BIT - count);	//trong temp2 chỉ chứa count bit cuối của num.data[i] các bit còn lại bằng 0
			int t = (temp1 >> (BIT - 1)) & 1;
			bool flag = false;
			if (t == 1) {											// nếu bit đầu tiên của temp1 == 1 thì phải chuyển về 0 để thực hiện dòng (*) bên dưới để đưa count bit đầu về 0
				temp1 &= ~(1 << (BIT - 1));							//01111111...11
				flag = true;
			}
			temp1 >>= (BIT - count);									//(*)
			if (flag == true)
				temp1 |= (1 << (count - 1));						//trả lại bit đã thay đổi ở trên
			result.data[i] = (num.data[i] << count) | temp1;		//dòng này chạy đúng khi count bit đầu của temp1 == 0 vì thế cần thuật toán bên trên
			temp1 = temp2;
		}
		num = result;
	}
	return result;
}

QInt operator<<(QInt num, QInt countBit)
{
	return num << countBit.data[LENGTH - 1];
}

QInt negativeToPositive(QInt num) {
	QInt temp;
	temp = 0;
	SetBit(temp, 127, 1);
	num = ~(num - temp);
	return num;
}

QInt operator/(QInt num1, QInt num2) { // num1 là số bị chia num2 là số chia
	QInt mod;
	mod = 0;
	
	int k = SIZE, Q = 0;
	bool flag = false; // biến đánh dấu kết quả là âm hay dương (âm, dương) = (false, true)
	bool signNum1, signNum2;
	signNum1 = GetBit(num1, 0);
	signNum2 = GetBit(num2, 0);
	if (signNum1 == signNum2)
		flag = true;
	if (signNum1 == 1 && signNum2 == 0) {
		num2 = soBu2(num2);
		num1 = negativeToPositive(num1);
	}
	else {
		if (signNum1 == 1 && signNum2 == 1) {
			num1 = negativeToPositive(num1);
			num2 = negativeToPositive(num2);
		}
	}
	//
	if (GetBit(num2, 0) == 0)
		num2 = soBu2(num2);

	while (k >= 0) {
		int bit = GetBit(num1, 0);
		num1 = num1 << 1;
		num1.data[LENGTH - 1] = num1.data[LENGTH - 1] | Q;
		mod = mod << 1;
		mod.data[LENGTH - 1] = mod.data[LENGTH - 1] | bit;
		mod = mod + num2;
		if (GetBit(mod, 0) == 1) {
			Q = 0;
			mod = mod - num2;
		}
		else {
			Q = 1;
		}
		--k;
	}
	if (!flag)
		num1 = soBu2(num1);
	return num1;
}

QInt operator*(QInt num1, QInt num2) {
	QInt mod;
	mod = 0;

	bool signNum1, signNum2;
	signNum1 = GetBit(num1, 0);
	signNum2 = GetBit(num2, 0);
	// nếu hai số là số âm (bù 2) thì chuyển về số dương để nhân
	if (signNum1 == 1 && signNum2 == 1) {
		num1 = negativeToPositive(num1);
		num2 = negativeToPositive(num2);
	}

	int k = SIZE;
	int endNum2;
	while (k > 0) {
		endNum2 = GetBit(num2, k - 1);
		if (endNum2 == 1) {
			mod = mod + num1;
		}
		num1 = num1 << 1;
		k--;
	}
	return mod;
}

istream& operator >> (istream &is, QInt & x)
{
	string temp = "";
	is >> temp;
	x = convertStringToQInt(temp);
	return is;
}

ostream& operator<<(ostream &os, const QInt &x)
{
	os << convertQIntToString(x);
	return os;
}

bool * DecToBin(QInt x) 
{
	bool *result = new bool[128]; //cap phat cho mang ket qua
	
	for (int i = 127; i >= 0; i--) {
		result[i] = GetBit(x, i);
	}
	return result;
}

QInt BinToDec(const bool *bit) 
{
	QInt result;
	result = 0; // khởi tạo giá trị đầu
	for (int n = 0; n < 4; n++) {
		result.data[n] = 0;
	}
	int i = 127;
	for (i; i >= 0; i--) {
		SetBit(result, i, bit[i]);
	}
	return result;
}

char *BinToHex(const bool *bit) 
{
	char *result = new char[33];//mảng char kết quả
	int k = 0;//k là chỉ số của mảng kết quả bắt đầu từ 0
	for (int i = 0; i < 128; i++) 
	{ //xét từng phàn tử trên mảng bool bit
		int kq = 0;
		for (int j = 3; j >= 0; j--) {
			if (bit[i] == 1) {
				kq += pow(2, j);
			}
			i++;
		}
		i--;
		int value = kq % 16;
		if (value < 10) {//nếu kết quả phép chia là số nhỏ hơn 10 thì cộng cho 48
			result[k++] = value + 48;
		}
		else//còn lại cộng cho 55
			result[k++] = value + 55;
	}
	result[k] = '\0';
	return result;
}


char *DecToHex(QInt x) {
	char* result = new char[33];
	int k = 31;
	for (int i = 3; i >= 0; i--) {
		for (int j = 0; j <= 7; j++) {
			int value = (x.data[i] >> 4*j) & 15;
			if (value < 10)
				result[k--] = value + 48;
			else
				result[k--] = value + 55;
		}
	}
	result[32] = '\0';
	return result;
}

bool* convertStringToBinary(string value){
	bool * result = new bool[128];
	int indexBin = 127;
	int strLen = value.length() - 1;
	for (int i = strLen; i >= 0; i--)
	{
		if (value[i] == '1')
			result[indexBin] = 1;
		else
			result[indexBin] = 0;
		indexBin--;
	}
	while (indexBin >= 0)
	{
		result[indexBin] = 0;
		indexBin--;
	}
	return result;
}

void DocfilevaXuli(fstream &fin, fstream &fout) {
	string s = "";

	if (!fin.is_open() || !fout.is_open())
		return;

	while (!fin.eof())
	{
		getline(fin, s);
		if (s == "")
			continue;

		int begin = 0;
		int end = s.find_first_of(" ", begin); //tim vi tri cua dau cach dau tien
		
		string temp1 = s.substr(begin, end - begin); //luu gia tri tu begin toi dau cach 1
		begin = end + 1;
		end = s.find_first_of(" ", begin); // tim vi tri dau cach tiep theo
		
		string temp2 = s.substr(begin, end - begin); // luu gia tri tu dau cach 1 toi dau cach thu 2
		begin = end + 1;

		int n;
		if (temp2 != "2" && temp2 != "10" && temp2 != "16" && temp2 != "~")
			n = 1; //kiem tra thuoc truong hop tinh toan hay chuyen doi
		else if (temp2 != "~")
			n = 2;
		else if (temp2 == "~") // xử lý toán tử not (~)
		{
			end = s.find_first_of(" ", begin);
			string temp3 = s.substr(begin, end - 1);

			QInt num;

			if (temp1 == "10")
				num = convertStringToQInt(temp3);
			else if (temp1 == "16")
				num = HexToDec(temp3.c_str());
			else if (temp1 == "2")
				num = BinToDec(convertStringToBinary(temp3));

			num = ~num;

			if (temp1 == "10")
				fout << convertQIntToString(num) << endl;
			else if (temp1 == "16")
				fout << delete0(DecToHex(num)) << endl;
			else if (temp1 == "2")
				fout << delete0(DecToBin2(num)) << endl;

			continue;
		}

		if (n == 1) //thuc hien tinh toan
		{ 
			end = s.find_first_of(" ", begin);
			string dau = s.substr(begin, end - begin); //dau
			begin = end + 1;
			end = s.find_first_of(" ", begin); // bo~ cai dau o giua~ ra
			string temp3 = s.substr(begin, end - begin); //luu gia tri cuoi cung
			
			QInt a, b, result;
			
			if (temp1 == "10")
			{
				a = convertStringToQInt(temp2);
				if (dau == "<<" || dau == ">>")
					b = stoi(temp3);
				else
					b = convertStringToQInt(temp3);
			}
			else if (temp1 == "2")
			{
				a = BinToDec(convertStringToBinary(temp2));
				if (dau == "<<" || dau == ">>")
					b = stoi(temp3);
				else
					b = BinToDec(convertStringToBinary(temp3));
			}
			else if (temp1 == "16")
			{
				a = HexToDec(temp2.c_str());
				if (dau == "<<" || dau == ">>")
					b = stoi(temp3);
				else
					b = HexToDec(temp3.c_str());
			}
			
			if (dau == "+")
			{
				result = a + b;
			}
			else if (dau == "-")
			{
				result = a - b;
			}
			else if (dau == "*")
			{
				result = a * b;
			}
			else if (dau == "/")
			{
				result = a / b;
			}
			else if (dau == ">>")
			{
				result = a >> b;
			}
			else if (dau == "<<")
			{
				result = a << b;
			}
			else if (dau == "&")
			{
				result = a & b;
			}
			else if (dau == "|")
			{
				result = a | b;
			}
			else if (dau == "^")
			{
				result = a ^ b;
			}

			string rs = "";

			if (temp1 == "10")
			{
				rs = convertQIntToString(result);
			}
			else if (temp1 == "2")
			{
				rs = delete0(DecToBin2(result));
			}
			else if (temp1 == "16")
			{
				rs = delete0(DecToHex(result));
			}

			fout << rs << endl;
		}
		else if (n == 2) //n==2 thuc hien chuyen doi
		{ 
			end = s.find_first_of(" ", begin);
			string temp3 = s.substr(begin, end - 1);

			// ham chuyen do i temp3 dua vao (temp1, temp2)
			if (temp1 == "10" && temp2 == "2")
			{
				QInt dec;
				dec = convertStringToQInt(temp3);
				fout << delete0(DecToBin2(dec)) << endl;
			}
			else if (temp1 == "10" && temp2 == "16")
			{
				QInt dec = convertStringToQInt(temp3);
				fout << delete0(DecToHex(dec)) << endl;
			}
			else if (temp1 == "2" && temp2 == "10")
			{
				bool* bin = convertStringToBinary(temp3);
				fout << BinToDec(bin) << endl;
				delete[] bin;
			}
			else if (temp1 == "2" && temp2 == "16")
			{
				bool * bin = convertStringToBinary(temp3);
				fout << delete0(BinToHex(bin)) << endl;
				delete[] bin;
			}
			else if (temp1 == "16" && temp2 == "2")
			{
				fout << delete0(DecToBin2(HexToDec(temp3.c_str()))) << endl;
			}
			else if (temp1 == "16" && temp2 == "10")
			{
				fout << HexToDec(temp3.c_str()) << endl;
			}
		}
	}

}


QInt HexToDec(const char* hex) {
	// kiểm tra xem chuỗi hex có đủ 32 ký tự ko
	string temp(hex);
	if (temp.length() < 32)
	{
		while (temp.length() != 32)
		{
			temp = "0" + temp;
		}
	}
	else if (temp.length() > 32)
	{
		temp = temp.substr(temp.length() - 32);
	}
	hex = temp.c_str();

	QInt result;
	result = 0;
	bool check = true; // kiểm tra xem có phải là những số 0 đầu tiên ko để bỏ qua
	for (int i = 0; i < BIT; i++) {
		int t = 0, index;
		if (hex[i] != '0') // nếu gặp kí tự khác 0 thì đánh dấu
			check = false;
		if (!check) { 
			index = i / 8; // vị trí của ô trong data
			if (hex[i] <= 70 && hex[i] >= 65)
				t = hex[i] - 55; // nếu là A...F
			else
				t = hex[i] - 48;// nếu là 0...9
			result.data[index] = result.data[index] | (t << ((7 - i) * 4)); // chèn t vào result
		}
	}
	return result;
}

char * DecToBin2(QInt x)
{
	char *result = new char[129]; //cap phat cho mang ket qua

	for (int i = 127; i >= 0; i--) {
		result[i] = GetBit(x, i) + '0';
	}
	result[128] = '\0';
	return result;
}


string delete0(string str)
{
	// xóa bớt số 0
	int vt = 0;
	for (vt = 0; vt < str.length(); vt++)
	{
		if (str[vt] != '0')
			break;
	}
	return str.substr(vt);
}

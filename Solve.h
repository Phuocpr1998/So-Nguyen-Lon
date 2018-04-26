#ifndef SOLVE_H
#define SOLVE_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#define SIZE 128
#define LENGTH 4
#define BIT 32


struct QInt
{
	int data[4];
	// hàm set giá trị ban đầu giá trị truyền vào là kiểu int và dương
	QInt& operator=(unsigned int x)
	{
		for (int i = 0; i < 4; i++)
			data[i] = 0;
		data[3] = x;
		return *this;
	}
};


void SetBit(QInt& data, int k, bool bit);
// lấy ra bit tại vị trí vt trong data
bool GetBit(QInt& data, int k);
// chia chuỗi cho 2 lấy dư là phần bit
string Divide2String(string value, bool &bit);
// chuyển bù 2
QInt soBu2(QInt data);
// cộng chuỗi hai số dương
string StringPlus(string str1, string str2);
// nhân chuỗi với 2
string MultiString2(string data);
// hàm tính lũy thừa 2
string exp2String(int exp);

QInt convertStringToQInt(string value);
string convertQIntToString(QInt x);

// a
void ScanQInt(QInt &x);
// b
void PrintQInt(QInt x);
// 
istream& operator >> (istream &is, QInt & x);
ostream& operator<<(ostream &os, const QInt &x);
//
bool * DecToBin(QInt x);
QInt BinToDec(const bool *bit);
char *BinToHex(const bool *bit);
char *DecToHex(QInt x);
//
QInt operator+(QInt num1, QInt num2);
QInt operator-(QInt num1, QInt num2);
QInt negativeToPositive(QInt num);
QInt operator/(QInt num1, QInt num2);
QInt operator*(QInt num1, QInt num2);
//
QInt operator&(QInt num1, QInt num2);
QInt operator|(QInt num1, QInt num2);
QInt operator^(QInt num1, QInt num2);
QInt operator~(QInt num);
//
QInt operator >> (QInt num, int countBit);
QInt operator >> (QInt num, QInt countBit);
QInt operator<<(QInt num, int countBit);
QInt operator<<(QInt num, QInt countBit);
//
bool* convertStringToBinary(string value);
void DocfilevaXuli(fstream &fin, fstream &fout);
//
QInt HexToDec(const char* hex);
char * DecToBin2(QInt x);
//xóa bits 0 thừa
string delete0(string str);
#endif

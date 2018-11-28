/*
 * 1.1.cpp
 *
 *  Created on: 2018Äê8ÔÂ4ÈÕ
 *      Author: ç÷
 */
#include <iostream>
#include <climits>
#include <string>
#include <sstream>

using namespace std;

int strtest() {
	char *sBuf = "test";
	int iNum = 5;
	long lCount = 1000000;
	double dMoney = 500000000.98;

	string strt = sBuf;
	cout << strt << endl;
	cout << to_string(iNum) << endl;
	cout << to_string(lCount) << endl;
	cout << to_string(dMoney) << endl;

	cout << "hello world!" << endl;
	return 0;
}

template<class Type>
Type stringToNum(const string& str) {
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}
int strtest1() {
	string str("00801.9988");
	const char *sBuf = str.c_str();
	cout << stringToNum<int>(str) << endl;
	cout << stringToNum<double>(str) << endl;
	cout << sBuf << endl;
	system("pause");
	return 0;
}

int strtest2() {
	string str("00801.9988");
	stringstream stream;
	stream << str;
	double dMoney;
	stream >> dMoney;
	cout << dMoney << endl;

	int iNum = 1000;
	stream.clear();
	stream << iNum;
	stream >> dMoney;
	cout << dMoney << endl;

	return 0;
}

int strtest3() {
	string str("00801.9988");
	double dMoney = stod(str);
	cout << dMoney << endl;
	return 0;
}

int strtest4(){
	wchar_t bob = L'P';

	wcout << L"tall" <<	endl;
	wcout << sizeof(bob) <<	endl;
	return 0 ;
}

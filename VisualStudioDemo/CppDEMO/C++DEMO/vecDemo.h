//vector object practice

#pragma once
#include <iostream>
#include <vector>
#include <array>
#define LEN 4
using namespace std;

template <typename T>
class vecDemo
{
public:
	vecDemo();
	~vecDemo();

	void printVar();
private:
	T d_var[LEN];
	vector<T> vec_var;
	array<T, LEN> arr_var;

};


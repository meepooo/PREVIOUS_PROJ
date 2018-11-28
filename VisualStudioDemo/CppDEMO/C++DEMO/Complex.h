//math complex number Operation
#pragma once
#include <iostream>

class Complex
{
public:
	Complex();
	Complex(double r, double i);
	~Complex();
	Complex operator+(Complex c);
	Complex operator-(Complex c);
	Complex operator*(Complex c);
	Complex operator/(Complex c);
	void display();
private:
	double real;
	double imag;
};


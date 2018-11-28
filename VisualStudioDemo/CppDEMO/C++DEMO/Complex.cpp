#include "Complex.h"



Complex::Complex()
{
	real = 0;
	imag = 0;
}

Complex::Complex(double r,double i)
{
	real = r;
	imag = i;
}

Complex::~Complex()
{
}

Complex Complex::operator+(Complex c)
{
	real += c.real;
	imag += c.imag;
	return Complex(*this);
}
Complex Complex::operator-(Complex c)
{
	real -= c.real;
	imag -= c.imag;
	return Complex(*this);
}
Complex Complex::operator*(Complex c)
{
	real *= c.real;
	imag *= c.imag;
	return Complex(*this);
}

Complex Complex::operator/(Complex c)
{
	real /= c.real;
	imag /= c.imag;
	return Complex(*this);
}

void Complex::display()
{
	std::cout << "(" << real << "," << imag << ")" << std::endl;
}
//
//int main()
//{
//	Complex c1(3.0, 4.0);
//	Complex c2(1.0,0.0);
//	Complex c;
//	c = c1 + c2;
//	c.display();
//	std::cin.get();
//
//	return 0;
//}
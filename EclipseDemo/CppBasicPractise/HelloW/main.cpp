#include <iostream>
#include <climits>
#include "HelloW.h"

using namespace std;

int main()
{
	double a=1.23;
	double b = 3 ;
	string s1 = "Hello";
	string s2 = "World";
	//decltype(a) b;

	cout << "Max(s1, s2): " << Max(s1, s2) << endl;

	strtest5(a, b);
	std::cout << a << "|" << b << std::endl ;

    int n1=2,n2=10;

    double d1=1.5,d2=5.6;

    cout<< "��С����:"<<minxxx(n1,n2)<<endl;

    cout<< "��Сʵ��:"<<minxxx(d1,d2)<<endl;

	return 0 ;
}

/*
 * 1.1.cpp
 *
 *  Created on: 2018Äê8ÔÂ4ÈÕ
 *      Author: ç÷
 */
#include <iostream>
#include <climits>

using namespace std;
int test11()
{
	int a=65;
/*	cin >> a ;*/
	cout << "a=" << a << endl;
	cout << hex ;
	cout << "a=" << a << endl;
	cout << oct ;
	cout << "a=" << a << endl;
	cout << dec ;
	cout << "sizeof a:" << sizeof(a) << endl ;
	cout << "short limits:" << SHRT_MAX << endl ;
	cout << "int limits:" << INT_MAX << endl ;
	cout << "long limits:" << LONG_MAX << endl ;
	cout << "long long limits:" << LLONG_MAX << endl ;
/*	cin.get();*/
	cout.put(a);

	return 0;
}



//指向指针的指针

#include <iostream>
#include <climits>
#include <string>
#include <cstring>
using namespace std;
int test423()
{
	int array[5] {1,2,3,4,5};
	
	int *point = array ;
	
	int **p = &point ;
	
	cout << "*point:" << *point << endl ;

	cout << "**p:" << **p << endl ;

	cout << "*(*p+1):" << *(*p+1) << endl ;

	struct year_month_day
	{
		int year ;
		string month ;
		char day[10] ;
	};

	year_month_day y01, y02, y03 ;

	year_month_day *pa =&y01;
	pa->year=1992;
	pa->month="5月";
	strcpy(pa->day,"11号");

	year_month_day **p3 = &pa ;
	cout << "pa:" << (*pa).month << endl ;
	cout << "**p3:" << (**p3).year << endl ;

	return 0;
}

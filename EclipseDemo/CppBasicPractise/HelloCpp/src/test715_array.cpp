#include <iostream>
#include <fstream>
#include <string>
#include <array>

using namespace std;

int test715()
{
	const int seasons = 4 ;
	const array<string, seasons> sName =
	{
			"Spring","Summer","Fall","Winter"
	};
	cout << "show:" ;
	cout << sName[0] ;
	cout << sName[1] ;
	cout << sName[2] ;
	cout << sName[3] ;

	return 0;
}

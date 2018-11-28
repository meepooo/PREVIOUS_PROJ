#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int test616()
{
	ifstream infile;
	string value;
	infile.open("1.txt");

	while(infile>>value)
	{
		cout << value << ' ';
	}
	infile.close();
	cout << endl << "end file!" << endl ;
	return 0;
}

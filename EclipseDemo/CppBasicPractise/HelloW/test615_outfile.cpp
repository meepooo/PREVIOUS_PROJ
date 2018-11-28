#include <iostream>
#include <fstream>

using namespace std;
int test615()
{
	ofstream outfile;
	outfile.open("1.txt");
	outfile << "hello world!" << endl;
	outfile.close();
	cout << "hello world!" << endl ;
	return 0;
}

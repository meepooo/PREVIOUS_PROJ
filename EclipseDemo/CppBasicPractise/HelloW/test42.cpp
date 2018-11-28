#include <iostream>
#include <climits>
#include <string>

using namespace std;
int test42()
{
	cout << "Hello World" << endl ;
	cout << R"("R hello world!")" <<  endl ;
	cout << R"+*("(hello world!)")+*" << endl ;

	return 0;
}

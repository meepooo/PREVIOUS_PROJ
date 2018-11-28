#include <iostream>
#include <climits>
#include <string>

using namespace std;
int test47()
{
	int *p = new int [10] ;
	
	cout << "Hello World" << endl ;
	
	delete [] p ;
	
	return 0;
}

#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int square(int a)
{
	return a*a;
}

typedef int(*funhander_t)(int);

funhander_t fun(int ch)
{
	return ch >= 'a' && ch <= 'z' ? ::tolower : ::toupper;
}

//int main()
//{
//	vector<int> v{ 1,2,3,4,5,-5,0 };
//	
//	transform(v.begin(),v.end(),v.begin(), square);//template
//	
//	transform(v.begin(), v.end(), ostream_iterator<int>(cout, " "), square);//print out
//	
//	transform(istream_iterator<int>(cin), istream_iterator<int>(), ostream_iterator<int>(cout, " "), square);//cin,do square,cout
//	
//	return 0;
//}
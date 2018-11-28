#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <string>

using namespace std;

int main()
{
	vector<int> v{ 1,2,-1,-2,100,50,-10000 };
	auto iter1 = v.begin();
	auto iter2 = v.end();

	cout << "ÅÅÐòÇ°:";
	copy(iter1, iter2, ostream_iterator<int>(cout, " "));
	cout << endl;

	sort(iter1, iter2, greater<int>());
	cout << "ÅÅÐòºó:";
	copy(iter1, iter2, ostream_iterator<int>(cout, " "));
	cout << endl;
	//find_if and greater function usage
	auto p=find_if(iter1,iter2,bind2nd(greater<int>(), 50));
	cout << *p << endl;

	v.push_back(23);

	return 0;
}
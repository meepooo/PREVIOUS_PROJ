#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>

using namespace std;

//输出指定的顺序容器的元素
template <class T>
void printContainer(const T& a)
{
	// use for deal with it
	//for (auto &e : a)
	//	cout << e << endl;

	copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));// use copy func
}

//int main()
//{
//	//use vector
//	vector<int> v{ 1,2,3,4,5,-5,0 };
//	//printContainer<vector <int>>(v);
//	cout << "vector v";
//	printContainer(v);
//
//	cout << endl;
//
//	deque<int> d;
//	for (int i = 0; i < 10; i++)
//	{
//		int x;
//		cin >> x;
//		d.push_front(x);
//	}
//	//printContainer<deque<int>>(d);
//	cout << "d deque:";
//	printContainer(d);
//	cout << endl;
//
//	list<int> l(d.rbegin(), d.rend());
//	cout << "l list:";
//	printContainer(l);
//	cout << endl;
//
//	list<int> l1(d.begin(), d.end());
//	cout << "l1 list";
//	printContainer(l);
//	cout << endl;
//
//	cout << "copy cout:";
//	copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
//	cout << endl;
//
//	cout << "list splice:";
//	l.splice(l.begin(), l1, l1.begin(), l1.end());
//	printContainer(l);
//
//	return 0;
//}
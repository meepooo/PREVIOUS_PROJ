#include <vector>
#include <iostream>

using namespace std;

class A {
public:
	A(vector<int> a) :arr(a) {}//constructor
	A(const A& a) :arr(a.arr) {}//copy constructor
	void print()
	{
		for (auto &e : arr)
			cout << e << " ";
		cout << endl;
	}
	~A() {}//destructor
private:
	vector<int> arr;
};
//
//int main()
//{
//	vector<int> arr1 = { 100,200,300 };
//
//	A src(arr1);
//	src.print();
//
//	A copy(src);//call copy constructor
//	copy.print();
//
//	int a;
//	cout << sizeof(a) << endl;
//	return 0;
//}

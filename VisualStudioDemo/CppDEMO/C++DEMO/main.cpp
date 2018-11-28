#include <iostream>
#include <list>

using namespace std;

class A {
public:
	A() {};
	~A() {};
	A(int i) :a(i) {};
private:
	int a;
};

class B: public A {
public:
	B() {};
	~B() {};
	B(int i, int j) :A(i), b(j) {};
private:
	int b;
};
int main()
{
	B b(1, 2);

	list<int> l;
	cerr << "error" << endl;
	return 0;
}
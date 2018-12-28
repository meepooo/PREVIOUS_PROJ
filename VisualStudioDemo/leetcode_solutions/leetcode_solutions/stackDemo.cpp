#include "stackDemo.h"



stackDemo::stackDemo()
{
}


stackDemo::~stackDemo()
{
}

int stackDemo::getStack()
{
	stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);

	cout << boolalpha << s.empty() << endl;
	cout << s.top() << endl;

	s.pop();
	cout << s.top() << endl;

	
	return 0;
}

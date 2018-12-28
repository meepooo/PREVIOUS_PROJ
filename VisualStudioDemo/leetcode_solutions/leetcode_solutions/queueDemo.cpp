#include "queueDemo.h"



queueDemo::queueDemo()
{
}


queueDemo::~queueDemo()
{
}

int queueDemo::getQueue()
{
	queue<int> q;
	q.push(1);
	q.push(3);
	q.push(5);

	// queue first element
	cout << q.front() << endl;

	q.pop();

	cout << q.front() << endl;
	cout << q.back() << endl; // queue last element

	cout << "q.size:" << q.size() << ",q.empty():" << q.empty();
	return 0;
}

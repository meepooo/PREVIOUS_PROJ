#include "DataStructure.h"
#include <iostream>

template <class T>
DataStructure<T>::DataStructure()
{
	p = &data;
}

template<class T>
DataStructure<T>::DataStructure(T dt)
{
	p = &data;
	*p = dt;
}

template <class T>
DataStructure<T>::~DataStructure()
{
	p = NULL;
}

template<class T>
const T DataStructure<T>::getData()
{
	if (p == NULL)
		return 0;

	return T(*p);
}

template<class T>
void DataStructure<T>::setData(const T& dt)
{
	*p = dt;
}

//class DataStucture main function for test only
using namespace std;
//int main()
//{
//	cout << "hello world!" << endl;
//
//	DataStructure<int> data(1);
//	cout << data.getData() << endl;
//
//	DataStructure<double> *p = new DataStructure<double>;
//	cout << p->getData() << endl;
//	p->setData(2.02);
//	cout << p->getData() << endl;
//
//	cin.get();
//	return 0;
//}
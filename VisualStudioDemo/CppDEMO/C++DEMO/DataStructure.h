#pragma once
//a data structure class, pointer p operate variable data
//include link list

template <class T>
class DataStructure
{
public:
	DataStructure();
	DataStructure(T dt);
	~DataStructure();
	const T getData();
	void setData(const T& dt);//can not change data value
private:
	T data;
	T* p;//p pointer to data
};


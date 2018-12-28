#include "mapDemo.h"


//begin()          返回指向map头部的迭代器
//clear()         删除所有元素
//count()          返回指定元素出现的次数
//empty()          如果map为空则返回true
//end()            返回指向map末尾的迭代器
//equal_range()    返回特殊条目的迭代器对
//erase()          删除一个元素
//find()           查找一个元素
//get_allocator()  返回map的配置器
//insert()         插入元素
//key_comp()       返回比较元素key的函数
//lower_bound()    返回键值 >= 给定元素的第一个位置
//max_size()       返回可以容纳的最大元素个数
//rbegin()         返回一个指向map尾部的逆向迭代器
//rend()           返回一个指向map头部的逆向迭代器
//size()           返回map中元素的个数
//swap()            交换两个map
//upper_bound()     返回键值>给定元素的第一个位置
//value_comp()      返回比较元素value的函数

mapDemo::mapDemo()
{
}


mapDemo::~mapDemo()
{
}

int mapDemo::getMap()
{
	map<int, string> map1;
	map1[1] = "lilei";
	map1[2] = "hanmeimei";
	map1[3] = "poly";

	// insert new pair element
	pair<int, string> value(100,"BOSS");
	map1.insert(value);

	for (auto it : map1)
	{
		cout << it.first << ":" << it.second << endl;
	}

	map<int, string>::iterator it = map1.begin();
	it->second = "NONE";
	cout << it->first << ":" << it->second << endl;

	map1.erase(1);
	for (auto it : map1)
	{
		cout << it.first << ":" << it.second << endl;
	}

	return 0;
}

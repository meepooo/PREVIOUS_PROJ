﻿#include "listDemo.h"

//Lst1.assign() 给list赋值 
//Lst1.back() 返回最后一个元素 
//Lst1.begin() 返回指向第一个元素的迭代器 
//Lst1.clear() 删除所有元素 
//Lst1.empty() 如果list是空的则返回true 
//Lst1.end() 返回末尾的迭代器 
//Lst1.erase() 删除一个元素 
//Lst1.front() 返回第一个元素 
//Lst1.get_allocator() 返回list的配置器 
//Lst1.insert() 插入一个元素到list中 
//Lst1.max_size() 返回list能容纳的最大元素数量 
//Lst1.merge() 合并两个list 
//Lst1.pop_back() 删除最后一个元素 
//Lst1.pop_front() 删除第一个元素 
//Lst1.push_back() 在list的末尾添加一个元素 
//Lst1.push_front() 在list的头部添加一个元素 
//Lst1.rbegin() 返回指向第一个元素的逆向迭代器 
//Lst1.remove() 从list删除元素 
//Lst1.remove_if() 按指定条件删除元素 
//Lst1.rend() 指向list末尾的逆向迭代器 
//Lst1.resize() 改变list的大小 
//Lst1.reverse() 把list的元素倒转 
//Lst1.size() 返回list中的元素个数 
//Lst1.sort() 给list排序 
//Lst1.splice() 合并两个list 
//Lst1.swap() 交换两个list 
//Lst1.unique() 删除list中重复的元素

listDemo::listDemo()
{
}


listDemo::~listDemo()
{
}

int listDemo::getList()
{
	list<int> l;

	l.insert(l.begin(), 0);

	list<int>::iterator it = l.begin();

	// 任意位置插入
	l.insert(l.end(), 222);
	l.insert(l.end(), 333);
	l.insert(l.end(), 444);
	l.insert(it, 555);

	// 链表首插入
	l.push_front(1);

	// 链表尾插入
	l.push_back(2);

	for (auto it : l)
	{
		cout << it << endl;
	}

	l.sort();
	for (auto it : l)
	{
		cout << it << endl;
	}
	return 0;
}

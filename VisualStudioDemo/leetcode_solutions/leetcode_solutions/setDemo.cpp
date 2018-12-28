#include "setDemo.h"

//1. begin()--返回指向第一个元素的迭代器
//
//2. clear()--清除所有元素
//
//3. count()--返回某个值元素的个数
//
//4. empty()--如果集合为空，返回true
//
//5. end()--返回指向最后一个元素的迭代器
//
//6. equal_range()--返回集合中与给定值相等的上下限的两个迭代器
//
//7. erase()--删除集合中的元素
//
//8. find()--返回一个指向被查找到元素的迭代器
//
//9. get_allocator()--返回集合的分配器
//
//10. insert()--在集合中插入元素
//
//11. lower_bound()--返回指向大于（或等于）某值的第一个元素的迭代器
//
//12. key_comp()--返回一个用于元素间值比较的函数
//
//13. max_size()--返回集合能容纳的元素的最大限值
//
//14. rbegin()--返回指向集合中最后一个元素的反向迭代器
//
//15. rend()--返回指向集合中第一个元素的反向迭代器
//
//16. size()--集合中元素的数目
//
//17. swap()--交换两个集合变量
//
//18. upper_bound()--返回大于某个值元素的迭代器
//
//19. value_comp()--返回一个用于比较元素间的值的函数

setDemo::setDemo()
{
}


setDemo::~setDemo()
{
}

int setDemo::getSet()
{
	int arr[5]= { 1,2,3,4,100 };

	set<int> s1(arr, arr+5);
	
	// insert into set, auto sort
	s1.insert(10);
	s1.erase(1);
	for (auto it : s1)
	{
		cout << it << endl;
	}

	auto it1 = s1.find(3);
	if (it1 != s1.end())
		cout << "3 found" << endl;
	else
		cout << "3 not found" << endl;

	auto it2 = s1.find(1);
	if (it2 != s1.end())
		cout << "1 found" << endl;
	else
		cout << "1 not found" << endl;

	return 0;
}

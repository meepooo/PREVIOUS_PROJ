#include "setDemo.h"

//1. begin()--����ָ���һ��Ԫ�صĵ�����
//
//2. clear()--�������Ԫ��
//
//3. count()--����ĳ��ֵԪ�صĸ���
//
//4. empty()--�������Ϊ�գ�����true
//
//5. end()--����ָ�����һ��Ԫ�صĵ�����
//
//6. equal_range()--���ؼ����������ֵ��ȵ������޵�����������
//
//7. erase()--ɾ�������е�Ԫ��
//
//8. find()--����һ��ָ�򱻲��ҵ�Ԫ�صĵ�����
//
//9. get_allocator()--���ؼ��ϵķ�����
//
//10. insert()--�ڼ����в���Ԫ��
//
//11. lower_bound()--����ָ����ڣ�����ڣ�ĳֵ�ĵ�һ��Ԫ�صĵ�����
//
//12. key_comp()--����һ������Ԫ�ؼ�ֵ�Ƚϵĺ���
//
//13. max_size()--���ؼ��������ɵ�Ԫ�ص������ֵ
//
//14. rbegin()--����ָ�򼯺������һ��Ԫ�صķ��������
//
//15. rend()--����ָ�򼯺��е�һ��Ԫ�صķ��������
//
//16. size()--������Ԫ�ص���Ŀ
//
//17. swap()--�����������ϱ���
//
//18. upper_bound()--���ش���ĳ��ֵԪ�صĵ�����
//
//19. value_comp()--����һ�����ڱȽ�Ԫ�ؼ��ֵ�ĺ���

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

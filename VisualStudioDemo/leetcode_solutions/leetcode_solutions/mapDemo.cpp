#include "mapDemo.h"


//begin()          ����ָ��mapͷ���ĵ�����
//clear()         ɾ������Ԫ��
//count()          ����ָ��Ԫ�س��ֵĴ���
//empty()          ���mapΪ���򷵻�true
//end()            ����ָ��mapĩβ�ĵ�����
//equal_range()    ����������Ŀ�ĵ�������
//erase()          ɾ��һ��Ԫ��
//find()           ����һ��Ԫ��
//get_allocator()  ����map��������
//insert()         ����Ԫ��
//key_comp()       ���رȽ�Ԫ��key�ĺ���
//lower_bound()    ���ؼ�ֵ >= ����Ԫ�صĵ�һ��λ��
//max_size()       ���ؿ������ɵ����Ԫ�ظ���
//rbegin()         ����һ��ָ��mapβ�������������
//rend()           ����һ��ָ��mapͷ�������������
//size()           ����map��Ԫ�صĸ���
//swap()            ��������map
//upper_bound()     ���ؼ�ֵ>����Ԫ�صĵ�һ��λ��
//value_comp()      ���رȽ�Ԫ��value�ĺ���

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

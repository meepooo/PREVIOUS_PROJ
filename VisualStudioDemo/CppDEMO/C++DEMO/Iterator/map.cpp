#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

using namespace std;

//int main()
//{
//	//map
//	map<string, int> m;
//	m.insert(make_pair("����",4));
//	m.insert(pair<string,int>("��ѧ",6));
//	auto iter = m.find("����");
//	cout << iter->first << "," << iter->second << endl;
//
//	iter = m.find("��ѧ");
//	cout << iter->first << "," << iter->second << endl;
//
//	//multimap
//	multimap<string, string> mm;
//	mm.insert(make_pair("Ӣ��", "������"));
//	mm.insert(make_pair("����", "���"));
//
//	auto iter1 = mm.find("Ӣ��");
//	cout << iter1->first << "," << iter1->second << endl;
//
//	iter1 = mm.find("����");
//	cout << iter1->first << "," << iter1->second << endl;
//
//	return 0;
//}
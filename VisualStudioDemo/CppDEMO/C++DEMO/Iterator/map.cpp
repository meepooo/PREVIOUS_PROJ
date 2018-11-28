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
//	m.insert(make_pair("语文",4));
//	m.insert(pair<string,int>("数学",6));
//	auto iter = m.find("语文");
//	cout << iter->first << "," << iter->second << endl;
//
//	iter = m.find("数学");
//	cout << iter->first << "," << iter->second << endl;
//
//	//multimap
//	multimap<string, string> mm;
//	mm.insert(make_pair("英语", "四六级"));
//	mm.insert(make_pair("体育", "达标"));
//
//	auto iter1 = mm.find("英语");
//	cout << iter1->first << "," << iter1->second << endl;
//
//	iter1 = mm.find("体育");
//	cout << iter1->first << "," << iter1->second << endl;
//
//	return 0;
//}
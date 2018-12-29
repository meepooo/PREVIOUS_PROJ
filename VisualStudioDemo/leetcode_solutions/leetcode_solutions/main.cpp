#include "Solution.h"
#include "vectorDemo.h"
#include "queueDemo.h"
#include "stackDemo.h"
#include "listDemo.h"
#include "setDemo.h"
#include "mapDemo.h"

using namespace std;

//// 最长无重复字符串
//int main()
//{
//	string s = "abcabcbb";
//	cout << s << endl;
//	Solution solu;
//	solu.lengthOfLongestSubstring(s);
//
//	return 0;
//}

//// vectorDemo
//int main()
//{
//	vectorDemo v;
//	v.getVectorValue();
//	return 0;
//}

//// queueDemo
//int main()
//{
//	queueDemo q;
//	q.getQueue();
//	return 0;
//}

//// stackDemo
//int main()
//{
//	stackDemo s;
//	s.getStack();
//	return 0;
//}

//// listDemo
//int main()
//{
//	listDemo l;
//	l.getList();
//	return 0;
//}

//// setDemo
//int main()
//{
//	setDemo set1;
//	set1.getSet();
//	return 0;	
//}

//// mapdemo
//int main()
//{
//	mapDemo map1;
//	map1.getMap();
//	return 0;
//}

// hitBall
//int main()
//{
//	Solution s;
//	vector<pair<int, int>> vec = { {1,100}, {10,16},{2,8},{1,6},{7,12} };
//	int shoter = s.hitBall(vec);
//	cout << "一共需要" << shoter << "个射手" << endl;
//	return 0;
//}

//int main()
//{
//	Solution s;
//	vector<int> vec = { 5, 1, 5, 2, 5, 3, 5, 4	};
//	int num = s.repeatedNTimes(vec);
//	cout << num << endl;
//	return 0;
//}

int main()
{
	Solution s;
	vector<string> vec = { {"flower"},{"flow"},{"flight"}};
	string num = s.longestCommonPrefix(vec);
	cout << num << endl;
	return 0;
}

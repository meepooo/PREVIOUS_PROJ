#include "Solution.h"
#include "vectorDemo.h"
#include "queueDemo.h"
#include "stackDemo.h"
#include "listDemo.h"
#include "setDemo.h"
#include "mapDemo.h"
#include "BinaryTree.h"

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
//
//int main()
//{
//	Solution s;
//	vector<string> vec = { {"flower"},{"flow"},{"flight"}};
//	string num = s.longestCommonPrefix(vec);
//	cout << num << endl;
//	return 0;
//}

//int main()
//{
//	Solution s;
//	int x = -147483648;
//
//	cout << s.reverse(x) << endl;
//
//	return 0;
//}

//int main()
//{
//	Solution s;
//	string str = "-   234";
//	cout << s.myAtoi(str);
//	return 0;
//}

//int main()
//{
//	Solution s;
//	vector<int> vec;
//	vec = s.numsSameConsecDiff(9,1);
//
//	for (int e : vec)
//	{
//		cout << e << endl;
//	}
//
//	return 0;
//}

//int main()
//{
//	vector<int> vec1 = { 20, 50, 15, 2, 5, 3, 35 };
//	vector<int> vec2 = { 6,8,22,33,25,57,98 };
//	BinaryTree* root = new BinaryTree(vec1[0]);
//	BinaryTree::createTree(root,vec1.begin()+1,vec1.end());
//	cout << endl;
//	BinaryTree::createTree(root, vec2.begin(), vec2.end());
//
//	//BinaryTree::dispTree(root);
//
//	cout << "二叉树节点数：" << BinaryTree::getNodeNum(root) << endl;
//	cout << "二叉树深数：" << BinaryTree::getDepth(root) << endl;
//	cout << "二叉树第7层节点数：" << BinaryTree::getNodeNumKthLevel(root,7) << endl;
//	cout << "二叉树叶子节点数：" << BinaryTree::getNodeNumLeaf(root) << endl; 
//	cout << "二叉树是否是二分查找树：" << BinaryTree::isValidBST(root) << endl;
//	return 0;
//}

//int main()
//{
//	Solution s;
//	vector<int> vec = { 20, 50, 15, 2, 5, 3, 35 };
//	cout << s.minSubArrayLen(66,vec) << endl;
//	return 0;
//}

////973. 最接近原点的 K 个点
//struct less3{
//	bool operator() (const int& x, const int& y) const
//	{
//		return x*x<y*y;
//	}
//};
//
//template <class T> struct less2 : binary_function <T, T, bool> {
//	bool operator() (const T& x, const T& y) const
//	{
//		return x*x<y*y;
//	}
//};
//
//struct compareByValue {
//	bool operator()(const pair<int, string>& a, const pair<int, string>& b) const
//	{
//		return a.second < b.second;
//	}
//};
//
//int main()
//{
//	Solution s;
//	vector<vector<int>> vec;
//	vector<vector<int>> result;
//
//	vec.push_back({ 3,3 });
//	vec.push_back({ 1,4 });
//	vec.push_back({ 4,0 });
//	vec.push_back({ 1,2 });
//	vec.push_back({ 3,2 });
//
//	result = s.kClosest(vec, 2);
//
//	cout << "main:" << endl;
//	for (auto elem : result)
//	{
//		for (auto e : elem)
//		{
//			cout << e << "\t";
//		}
//		cout << endl;
//	}
//	cout << endl;
//
//	map<int, string, less3> map;
//	map[2] = "Bob";
//	map[3] = "alice";
//	map[0] = "olive";
//	map[1] = "tom";
//	map.insert(pair<int, string>(-100,"BOSS"));	
//	
//	for (auto& e : map)
//	{
//		cout << e.first << "," << e.second << "\t";
//	}
//	cout << endl;
//	
//	vector<pair<int, string>> vector(map.begin(), map.end());
//	sort(vector.begin(), vector.end(), compareByValue());
//	for (auto&e : vector)
//	{
//		cout << e.first << "," << e.second << "\t";
//	}
//	cout << endl;
//
//	return 0;
//}

int main()
{
	Solution s;
	vector<int> vec;
	vec.push_back(3);
	vec.push_back(7);
	vec.push_back(2);
	vec.push_back(4);
	cout << s.largestPerimeter(vec);
	return 0;
}
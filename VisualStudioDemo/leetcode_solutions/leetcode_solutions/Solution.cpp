#include "Solution.h"



Solution::Solution()
{
}


Solution::~Solution()
{
}

int Solution::lengthOfLongestSubstring(string s)
{	
	int result = 1;
	int strlen = s.length();
	
	if (strlen == 0)
		return 0;
	// 外层循环strlen次
	for (int i = 0; i < strlen; i++)
	{
		string sTmp;
		sTmp = "";
		// sTmp赋第一个值
		sTmp += s[i];
		int begin = i;
		// 内层循环strlen-i次
		for (int j = i+1; j < strlen; j++)
		{
			cout << sTmp << "\t" << s[j] << "\t" << endl;
			// 判断重复
			if (sTmp.find(s[j]) == -1)
			{
				sTmp += s[j];
			}
			else
			{
				// 更新result
				cout << "找到重复:" << s[j] << "，sTmp=" << sTmp << ",result=" << j - begin << endl;
				result = result > (j-begin) ? result:(j-begin) ;
				
				// 重置sTmp,begin,然后continue
				sTmp = "";
				sTmp = s[j];
				begin = j;
			}
			
			// 循环中止处理
			if (j == strlen - 1)
			{
				cout << "循环结束, sTmp=" << sTmp << ",reslut =" << strlen - begin << endl;
				result = result > (strlen - begin ) ? result : (strlen - begin );
				break;
			}
		}
	}

	cout << "程序运行结束，结果为：" << result <<endl ;
	return result;
}

vector<int> Solution::intersect(vector<int>& nums1, vector<int>& nums2) {
	vector<int>::iterator it1 = nums1.begin();
	vector<int>::iterator it2 = nums2.begin();

	vector<int> result;
	vector<int>::iterator it = result.begin();

	// 可以去掉set
	// set<int> set1(nums1.begin(),nums1.end());
	// set<int> set2(nums2.begin(),nums2.end());

	map<int, int> map1;
	map<int, int> map2;
	map<int, int> result_map;

	map<int, int>::iterator itm1 = map1.begin();
	map<int, int>::iterator itm2 = map2.begin();

	// for(auto s:set1)
	// {
	//     cout << s << endl;
	// }
	// for(auto s:set2)
	// {
	//     cout << s << endl;
	// }

	for (it1 = nums1.begin(); it1 != nums1.end(); it1++)
	{
		int cnt = count(nums1.begin(), nums1.end(), *it1);
		//cout << "map1 test:" << *it1 << "," << cnt << endl; 
		map1[*it1] = cnt;
	}

	for (it2 = nums2.begin(); it2 != nums2.end(); it2++)
	{
		int cnt = count(nums2.begin(), nums2.end(), *it2);
		//cout << "map2 test:" << *it2 << "," << cnt << endl; 
		map2[*it2] = cnt;
	}

	//         cout << "map1" << endl;
	//         for(auto m:map1)
	//         {
	//             cout << m.first << "," << m.second << endl;
	//         }

	//         cout << "map2" << endl;
	//         for(auto m:map2)
	//         {
	//             cout << m.first << "," << m.second << endl;
	//         }


	// 空的情况
	if (nums1.empty() == 1)
		return nums1;
	if (nums2.empty() == 1)
		return nums2;

	// 暴力法
	// 需增加去重复操作
	for (itm1 = map1.begin(); itm1 != map1.end(); itm1++)
	{
		for (itm2 = map2.begin(); itm2 != map2.end(); itm2++)
		{
			// 发现相等，则查找下一个it1
			if (itm1->first == itm2->first)
			{
				int cnt = itm1->second > itm2->second ? itm2->second : itm1->second;
				result_map[itm1->first] = cnt;
			}
		}
	}
	// cout << "result_map" << endl;
	for (auto m : result_map)
	{
		// cout << m.first << "," << m.second << endl;
		for (int i = 0; i<m.second; i++)
			result.push_back(m.first);
	}

	// result_map to vector
	return result;
}

vector<int> Solution::twoSum(vector<int>& nums, int target) {
	//傻瓜法，加起来就行了
	vector<int> vec;
	vector<int>::iterator it, i;
	it = i = nums.begin();

	if (nums.size()<2)
		return vec;

	for (it = nums.begin(); it != nums.end(); it++)
	{
		cout << *it << endl;
		for (i = nums.begin(); i != nums.end(); i++)
		{
			//用偏移判断重复问题
			int itb = it - nums.begin();
			int ib = i - nums.begin();

			if (*it + *i == target && (itb != ib))
			{
				vec.push_back(itb);
				vec.push_back(ib);
				goto result;
			}
		}
	}

result:
	return vec;
}

int Solution::hitBall(vector<pair<int, int>>& ball)
{
	int shoter = 1;
	int size = ball.size();

	if (size <= 1)
		return size;

	//1.排序
	sort(ball.begin(), ball.end());

	//典型的贪心算法
	//考虑加射手的情况
	//按气球边界循环并按条件改变边界
	int left = ball[0].first;
	int right = ball[0].second;
	for ( int i=1;i<size;i++)
	{
		//重合，则不加射手，更新边界为重合边界
		if (ball[i].first <= right)
		{
			left = ball[i].first;
			right = right>ball[i].second? ball[i].second :right;
		}
		//不重合，则加射手，更新边界为新气球边界
		else
		{
			shoter++;
			left = ball[i].first;
			right = ball[i].second;
		}
	}
	return shoter;
}

int Solution::repeatedNTimes(vector<int>& A) {

	int num = A.size();
	int result = -1;

	if (num<4 || num % 2 != 0)
		return -1;

	//暴力法，两次循环
	if (1 == 0)
	{
		for (int i = 0; i<num; i++)
		{
			for (int j = i + 1; j<num; j++)
			{
				if (A[i] == A[j])
				{
					result = A[i];
					goto end;
				}
			}
		}
	}
	//排序法，判断相邻元素相等
	else if (2 == 0)
	{
		sort(A.begin(), A.end());

		for (int i = 0; i<num - 1; i++)
		{
			if (A[i] == A[i + 1])
			{
				result = A[i];
				goto end;
			}
		}
	}
	// 利用集合set特性
	else if (3 == 0)
	{
		set<int> s;
		int s_size = 0;
		for (int i; i<num; i++)
		{
			s.insert(A[i]);
			s_size += 1;
			if (s.size() != s_size)
			{
				result = A[i];
				goto end;
			}
		}
	}
	//特性分析法
	else
	{
		if (A[0] == A[num - 1])
		{
			result = A[0];
			goto end;
		}
		for (int i = 1; i<num - 1; i++)
		{
			if (A[i - 1] == A[i])
			{
				result = A[i];
				goto end;
			}
			else if (A[i + 1] == A[i])
			{
				result = A[i];
				goto end;
			}
			else if (A[i - 1] == A[i + 1])
			{
				result = A[i - 1];
				goto end;
			}
		}
	}

end:
	return result;
}

string Solution::longestCommonPrefix(vector<string>& strs)
{
	int num = strs.size();

	if (num == 0)
		return "";
	else if (num == 1)
	{
		return strs[num - 1];
	}
	int len = strs[0].length();
	//求最短长度
	for (int i = 1; i<num; i++)
	{
		len = len<strs[i].length() ? len : strs[i].length();
	}

	//按位取前缀串
	string str = "";
	for (int j = 0; j<len; j++)
	{
		char c = strs[0].at(j);
		for (int i = 1; i<num; i++)
		{
			if (strs[i].at(j) != c)
				goto result;

			if (i == num - 1 && strs[i].at(j) == c)
				str = str + c;
		}
	}

result:
	return str;
}

int Solution::reverse(int x)
{
	int n;
	long long result = 0;//防止溢出

	if (x >= INT_MAX || x <= INT_MIN)
		return 0;

	//符号处理
	n = abs(x);

	if (n<10)
		return x;

	//用队列存储
	queue<int> q;
	while (1) {
		if (n<10) {
			q.push(n);
			break;
		}

		q.push(n % 10);
		n /= 10;
	}

	//组成数字
	while (!q.empty()) {
		result = (result * 10) + q.front();
		q.pop();
	}

	if (x<0)
		result = -result;

	//溢出判断
	if (result > INT_MAX || result < INT_MIN)
		return 0;

	return result;
}

int Solution::myAtoi(string str)
{
	long long result = 0;
	char c = 0;
	char symbol = 0;
	int lock = 0;

	//空值判定
	if (str.empty()) {
		return 0;
	}

	//char to int 转换 char-48
	for (int i = 0; i<str.length(); i++) {
		c = str.at(i);
		cout << c << "," << (int)c << "," << lock << endl;
		//空值跳过
		if (c == 32 && lock != 1) {
			continue;
		}
		//符号位
		else if ((c == 45 || c == 43) && lock != 1) {
			if (symbol == 0) {
				symbol = c;
				lock = 1;
				continue;
			}
		}

		//数字出现则锁定
		if (c >= 48 && c <= 57) {
			result = (result * 10) + c - 48;
			lock = 1;
		}
		//一旦出现非数字则返回result
		else {
			goto end;
		}

		cout << "result:" << result << endl;
		// 边界值判定
		if (symbol == '-' && -result <= INT_MIN)
			return INT_MIN;
		else if (symbol != '-' && result >= INT_MAX)
			return INT_MAX;
	}

end:
	cout << "symbol:" << symbol << endl;
	if (symbol == '-')
		result = -result;

	return (int)result;
}

struct TreeNode {
	int val;
	int level;
	TreeNode *p;
	TreeNode *left;
	TreeNode *right;
};

void dispTree(TreeNode* root, vector<int>* vec, int N, string str) {

	if (root == NULL)
		return;

	str = str + char(root->val + 48);

	if (root->level == N) {
		//cout << "result:" <<root->p->p->val << root->p->val << root->val << endl;
		//cout << "str:" << str << endl;
		vec->push_back(atoi(str.c_str()));
		return;
	}

	dispTree(root->left, vec, N, str);
	dispTree(root->right, vec, N, str);
}

void createTree(TreeNode* root, int N, int K) {
	//cout << "val:" << root->val << ",level:" << root->level << endl;

	// N is max level
	if (root->level == N)
		return;

	if (root->val - K >= 0) {
		TreeNode *left = new TreeNode();
		left->p = root;
		root->left = left;
		root->left->val = root->val - K;
		root->left->level = root->level + 1;
		//cout << "生成左节点:" << "val:" << left->val << ",level:" << left->level << endl;
		createTree(root->left, N, K);
	}

	if (root->val + K <= 9) {
		TreeNode *right = new TreeNode();
		right->p = root;
		root->right = right;
		root->right->val = root->val + K;
		root->right->level = root->level + 1;
		//cout << "生成右节点:" << "val:" << right->val << ",level:" << right->level << endl;
		createTree(root->right, N, K);
	}

	return;
}

vector<int> Solution::numsSameConsecDiff(int N, int K) {
	//1.拆分数字为数组
	//int a[N];

	vector<int> vec;
	if (N<1)
		return vec;
	else if (N == 1) {
		if (K <= 9) {
			for (int i = 0; i<10; i++)
				vec.push_back(i);
			return vec;
		}
		else
			return vec;
	}

	//所有可能的tree
	for (int i = 1; i <= 9; i++) {
		TreeNode *root = new TreeNode();

		root->val = i;
		root->level = 1;
		createTree(root, N, K);
		cout << "root->val:" << root->val << endl;
		//打印所有满足条件的tree
		if (root->val != NULL)
			dispTree(root, &vec, N, "");

		delete root;
	}

	cout << "vec:";
	if (K == 0) {
		set<int> s;
		for (int e : vec) {
			s.insert(e);
			cout << e << "\t";
		}
		vec.clear();
		for (int e : s) {
			vec.push_back(e);
		}
	}

	return vec;
}

bool minSubArrayLen_for(int s, vector<int>& nums,int cnt) {
	int sum = 0;
	for (int i = 0; i < nums.size() - cnt + 1; i++) {
		for (int j = i; j < i + cnt; j++) {
			sum += nums[i];
		}
		if (sum >= s) {
			return true;
		}
	}

	return false;
}

int Solution::minSubArrayLen(int s, vector<int>& nums) {
	//暴力法，效率低下
	if (1 == 0) {
		int result = INT_MAX;
		if (nums.size() == 0)
			return 0;

		int sum = 0;
		for (int i = 0; i < nums.size(); i++) {
			sum = 0;
			for (int j = i; j < nums.size(); j++) {
				sum += nums[j];
				if (sum >= s)
					result = result > (j - i + 1) ? (j - i + 1) : result;
			}
		}

		if (result == INT_MAX)
			result = 0;

		return result;
	}
	// 算法失败
	if (2 == 0) {
		//边界值	
		if (nums.size() == 0)
			return 0;

		int result = 0;
		for (int i : nums) {
			if (i >= s)
				return 1;
			result += i;
		}

		if (result == s)
			return nums.size();
		else if (result < s)
			return 0;
		//边界值结束

		result = INT_MAX;
		for (int i = 2; i < nums.size(); i++) {
			if (minSubArrayLen_for(s, nums, i))
				return i;
		}

		if (result == INT_MAX)
			result = 0;

		return result;
	}

}
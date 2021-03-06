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
		len = len < strs[i].length() ? len : strs[i].length();
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



void dispTree(PTreeNode* root, vector<int>* vec, int N, string str) {

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

void createTree(PTreeNode* root, int N, int K) {
	//cout << "val:" << root->val << ",level:" << root->level << endl;

	// N is max level
	if (root->level == N)
		return;

	if (root->val - K >= 0) {
		PTreeNode *left = new PTreeNode();
		left->p = root;
		root->left = left;
		root->left->val = root->val - K;
		root->left->level = root->level + 1;
		//cout << "生成左节点:" << "val:" << left->val << ",level:" << left->level << endl;
		createTree(root->left, N, K);
	}

	if (root->val + K <= 9) {
		PTreeNode *right = new PTreeNode();
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
		PTreeNode *root = new PTreeNode();

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

void swapmap(map<long, long>& m1, map<long ,long>& m2)
{
	map<long, long> m;
	m = m1;
	m1 = m2;
	m2 = m;
}

struct nodedata
{
	int value;
	vector<int> point;
};

struct nodedataCompare
{
	bool operator()(const nodedata& a, const nodedata& b)
	{
		return a.value < b.value;
	}
};

vector<vector<int>> Solution::kClosest(vector<vector<int>>& points, int K)
{
	//map容器，增序容器
	map<int, vector<int>, less<int>> point_map;
	vector<vector<int>> result;

	//边界值处理
	if (points.size() < K)
		return result;
	else if (points.size() == K)
		return points;

	//计算平方和
	int i = 0;
	for (auto& elem : points)
	{
		long j = pow(elem[0], 2) + pow(elem[1], 2);
		point_map[j] = points[i++];
	}
	
	i = 0;
	for (auto& elem : point_map)
	{
		if (i >= K)
			break;

		result.push_back(elem.second);
		i++;
	}

	return result;

	//链表容器
	if (1 == 0)
	{
		list<nodedata> list;
		vector<vector<int>> result;
		nodedata node;

//边界值处理
if (points.size() < K)
	return result;
else if (points.size() == K)
return points;

//计算平方和
int i = 0;
for (auto& elem : points)
{
	long j = pow(elem[0], 2) + pow(elem[1], 2);
	node.value = j;
	node.point = points[i];
	list.push_back(node);
	i++;
}

list.sort(nodedataCompare());

i = 0;
for (auto& elem : list)
{
	if (i >= K)
		break;

	result.push_back(elem.point);
	i++;
}

return result;
	}

	//数组容器
	if (2 == 0)
	{
		vector<vector<int>> result;

		//防止平方和溢出
		vector<vector<int>> sum;

		//边界值处理
		if (points.size() < K)
			return result;
		else if (points.size() == K)
			return points;

		//计算平方和
		int i = 0;
		for (auto& elem : points)
		{
			long j = pow(elem[0], 2) + pow(elem[1], 2);
			sum.push_back({ j, i++ });
		}

		sort(sum.begin(), sum.end());

		cout << "sort sum:";
		for (auto elem : sum)
		{
			cout << elem[0] << "," << elem[1] << "\t";
		}
		cout << endl;

		//返回前K个到result
		i = 0;
		while (i < K)
		{
			result.push_back(points[sum[i++][1]]);
		}

		return result;
	}
}

int Solution::largestPerimeter(vector<int>& A)
{
	int result = 0;
	//先排序
	sort(A.rbegin(), A.rend());

	//边界值处理
	if (A.size() < 3)
		return 0;

	cout << endl;
	//再用贪婪算法，动态规划
	//三角形两边
	auto left = A.begin();
	auto right = A.begin();
	for (int i = 0; i < A.size()-2; i++)	//三角形的底
	{
		left = A.begin();
		left += (i+1);
		right = left+1;

		//三角形的两条边，满足>0，并且两边和>A[i]
		while (left != A.end()-1 || right != A.end())
		{
			if (left == right)
			{
				right++;
				continue;
			}

			if (*left > 0 && *right > 0 && (*left + *right) > A[i])
			{
				int temp = *left + *right + A[i];
				result = (result > temp) ? result : temp;
			}

			left++;
		}
	}

	return result;
}

int Solution::subarraysDivByK(vector<int>& A, int K)
{
	//数组做容器
	if(1==0)
	{
		int result = 0;

		int N = A.size();
		int *P = new int[N + 1];
		P[0] = 0;
		for (int i = 0; i < N; ++i)
		{
			P[i + 1] = P[i] + A[i];
			cout << P[i + 1] << endl;
		}

		int* count = new int[K];
		for (int i = 0; i < K; i++)
		{
			count[i] = 0;
		}
		for (int i = 0; i < N + 1; i++)
			count[(P[i] % K + K) % K]++;

		for (int i = 0; i < K; i++)
		{
			cout << i << "," << count[i] << endl;
			result += count[i] * (count[i] - 1) / 2;
		}
		return result;
	}

	//使用vector和map做容器
	int result = 0;
	//边界值
	if (A.size() == 0)
		return 0;

	vector<int> sum;//数组存储从下标0到下标i的值之和
	sum.resize(A.size() + 1);
	sum[0] = 0;
	for (int i = 0; i < A.size(); i++)
	{
		sum[i + 1] = sum[i] + A[i];
	}

	cout << "vector:";
	for (auto& e : sum)
	{
		cout << e << "\t";
	}
	cout << endl;

	//vector<vector<int>> count(sum.size());//下标为对K求余的值，值为计数器
	map<int, int> count;
	for (int i = 0; i < sum.size(); i++)
	{
		count[(sum[i] % K + K) % K] ++;//int值为负的处理
	}

	cout << "count:";
	for (auto& e : count)
	{
		cout << e.first << "," << e.second << "\t";
	}
	cout << endl;

	//算法，count相同下标的计数器有n*(n-1)/2个子数组
	//相比于暴力法，少了很多数组相加的操作，而且优化了A大部分值一样的算法
	for (auto& e : count)
	{
		result += e.second * (e.second - 1) / 2;
	}

	////暴力法：循环实现，效率太低
	if (2 == 0)
	{
		int sum=0;
		for (int i = 0; i < A.size(); i++)
		{
			for (int j = i; j < A.size(); j++)
			{
				sum = 0;
				for (int k = i; k < j + 1; k++)
				{
					sum += A[k];
				}
				if (sum%K == 0)
					result++;
			}
		}
	}

	return result;
}

string Solution::strWithout3a3b(int A, int B)
{
	string result="";

	//区分A,B大小
	int getmax = max(A, B);
	int maxval = 0, minval = 0;
	char maxchar = 0;
	char minchar = 0;

	if (getmax == A)
	{
		maxval = A;
		minval = B;
		maxchar = 'a';
		minchar = 'b';
	}
	else
	{
		maxval = B;
		minval = A;
		maxchar = 'b';
		minchar = 'a';
	}
	
	//边界值处理
	if (minval == 0)
	{
		if (maxval == 0 || maxval>2)
			;
		else if (maxval == 1)
			result = "" + maxchar;
		else if (maxval == 2)
			result = "" + maxchar + maxchar;
		
		return result;
	}

	if (maxval >= (minval * 2))
	{
		int sum_char = maxval - (minval * 2);

		for (int i = 0; i < minval; i++)
		{
			result = result + maxchar + maxchar + minchar;
		}

		if (sum_char > 2)
			result = "";
		else if (sum_char == 1)
			result = result + maxchar;
		else if (sum_char == 2)
			result = result + maxchar + maxchar;

		return result;
	}

	/*算法：x 个 "ab"， y 个 "aab"
	A = x + 2y;
	B = x + y;
	y = A - B;
	x = 2B - A;
	*/
	int x = 2 * minval - maxval;
	int y = maxval - minval;

	for (int i = 0; i < x; i++)
		result = result + maxchar + minchar;

	for (int i = 0; i < y; i++)
		result = result + maxchar + maxchar + minchar;

	return result;
}

vector<int> Solution::sumEvenAfterQueries(vector<int>& A, vector<vector<int>>& queries)
{
	vector<int> result;
	int sum = 0;
	//边界值
	if (A.size() == 0 || queries.size() == 0)
	{
		return result;
	}

	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] % 2 == 0)
			sum += A[i];
	}

	//算法
	for (int i = 0; i < queries.size(); i++)
	{
		int index = queries[i][1];
		int temp = A[index];
		int changeVal = A[index] % 2 == 0 ? A[index] : 0;

		//更新A
		A[index] = A[index] + queries[i][0];

		//更新sum
		if (A[index] % 2 == 0)
			sum = sum - changeVal + A[index];
		else
			sum -= changeVal;

		result.push_back(sum);

		for (auto &e : A)
		{
			cout << e << ",";
		}
	}
	cout << endl;

	return result;
}

void searchTree(TreeNode* root, vector<int>& vec) 
{
	if (root == NULL)
		return;

	vec.push_back(root->val);	
	searchTree(root->left, vec);
	searchTree(root->right, vec);
}

string Solution::smallestFromLeaf(TreeNode * root)
{
	string result;
	for (int i = 0; i < 1000; i++)
		result += "z";

	//数组下标从1开始
	/*vector<int> vec;
	vec.push_back(0);*/

	vector<int> vec = { 0, 0, 1, 2, 3, 4, 3, 4 };
	//先序遍历存放到数组
	//searchTree(root, vec);

	for (auto &e : vec)
	{
		cout << e << ",";
	}
	cout << endl;

	//堆算法求解，不是满二叉树
	//子节点=父节点*2
	string temp;
	for (int i = vec.size(); i > 0; i--)
	{
		temp = "";
		for (int j = i; j > 1; j/=2)
		{			
			temp += vec[j];
		}
		temp += vec[1];
		result = (result < temp) ? result : temp;
	}

	return result;
}

vector<int> Solution::addToArrayForm(vector<int>& A, int K)
{
	//进位符
	int signal = 0;
	vector<int> result;
	vector<int> k;

	//边界值处理
	if (A.size() == 0)
		return result;
	if (K == 0)
		return A;

	//A和K反转
	std::reverse(A.begin(),A.end());
	
	int temp = K;
	while (temp >= 10)
	{
		k.push_back(temp % 10);
		temp = temp / 10;		
	}
	k.push_back(temp);
	
	//算法
	int mavValue = max(A.size(), k.size());
	temp = 0;
	for (int i = 0; i<mavValue; i++)
	{
		if (i >= A.size())
		{
			temp = k[i] + signal;
		}
		else if (i >= k.size())
		{
			temp = A[i] + signal;
		}
		else
		{
			temp = A[i] + k[i] + signal;
		}

		if (temp > 9)
		{
			temp %= 10;
			signal = 1;
		}
		else
		{
			signal = 0;
		}
		result.push_back(temp);
	}

	if (signal == 1)
		result.push_back(signal);

	std::reverse(result.begin(),result.end());

	return result;
}

template <typename T>
bool isSameStack(stack<T> s, stack<T> t)
{
	//长度相等
	if (s.size() != t.size())
		return false;

	//逐个弹出栈中元素比较
	while (!s.empty())
	{
		if (s.top() != t.top())
		{
			return false;
		}

		s.pop();
		t.pop();
	}
	return true;
}

bool Solution::backspaceCompare(string S, string T)
{
	//用栈的属性，字符串按字符入栈，遇#出栈，最后结果比较
	stack<char> s, t;

	//S入栈
	for (auto& e : S)
	{
		//cout << e << endl;
		if (e == '#')
		{
			if (!s.empty())
			{
				s.pop();
			}
			continue;
		}

		s.push(e);
	}

	//T入栈
	for (auto& e : T)
	{
		//cout << e << endl;
		if (e == '#')
		{
			if (!t.empty())
			{
				t.pop();
			}
			continue;
		}

		t.push(e);
	}

	//s与t比较
	return isSameStack(s, t);
}

int Solution::longestMountain(vector<int>& A)
{
	int result = 0;

	if (A.size()<3)
	{
		return result;
	}
	//思路一：
	//初始化设定数组开头是山顶，后面实现找山顶与计算山脉长度length，爬山长度up，下山长度down
	//三种情况，1. A[i] == A[i-1] 则结果存入result，length清0，up清0，down清0
	//三种情况，2. A[i] > A[i-1]，提高 up++
	//三种情况，3. A[i] < A[i-1]，下降 则down++
	//考虑山顶与山底的情况
	
	//思路二：
	//新建一个数组，连续上山-1，下山1，平地0累计计入数组B
	//计算B[i]-B[i-1]的值最大
	vector<int> B;
	int len =2;
	int oflag = -2;
	int nflag = -2;

	//初始化原上山、下山标志
	if (A[1] == A[0])
	{
		oflag = 0;
	}
	else if (A[1] > A[0])
	{
		oflag = -1;
	}
	else
	{
		oflag = 1;
	}

	//得出数组B
	for (int i=2;i<A.size();i++)
	{
		//平地
		if (A[i] == A[i - 1])
		{
			nflag = 0;
			if (oflag != nflag)
			{
				B.push_back(len * oflag);
				oflag = 0;
				len = 1;
			}
		}
		//上山
		else if(A[i] > A[i - 1]) 
		{
			nflag = -1;
			if (oflag != nflag)
			{
				B.push_back(len * oflag);
				oflag = -1;
				len = 1;
			}
		}
		//下山
		else
		{
			nflag = 1;
			if (oflag != nflag)
			{
				B.push_back(len * oflag);
				oflag = 1;
				len = 1;
			}
		}

		len++;
	}
	B.push_back(len * oflag);

	for (auto& e : B)
	{
		cout << e << "\t";
	}
	cout << endl;
	//对数组B相邻元素求最大差
	for (int i = 1; i < B.size(); i++)
	{
		if (B[i] == 0 || B[i-1]==0)
			continue;

		len = B[i] - B[i - 1] -1;
		result = result > len ? result : len;
	}

	return result;
}

bool searchAndRemoveList(list<int>& listHand, int val)
{
	auto it = listHand.begin();
	for(;it!=listHand.end();it++)
	{
		if (*it == val)
		{
			listHand.erase(it);
			//listHand.pop_front();
			return true;
		}
	}

	return false;
}

bool Solution::isNStraightHand(vector<int>& hand, int W)
{
	bool result = false;

	//边界值
	if (hand.size() == 0)
		return false;

	if (W == 1)
		return true;

	//hand.size是W的整数倍
	if (hand.size() % W != 0)
		return false;

	//牌分组算法
	//先排序，存入list应该比较高效
	list<int> listHand;

	sort(hand.begin(), hand.end());
	for (auto& e : hand)
	{
		listHand.push_back(e);
	}

	int lastVal = 0;
	int len = 0;

	while (!listHand.empty())
	{
		for (auto &e : listHand)
			cout << e << "\t";
		cout << endl;

		//首位初始化
		if (len == 0)
		{
			lastVal = *listHand.begin();
			len++;
			listHand.pop_front();
			continue;
		}

		if (searchAndRemoveList(listHand, lastVal + 1) == false)
			return false;

		len++;
		lastVal++;

		if (len == W)
		{
			len = 0;
		}
	}

	return true;
}

void searchTreeNode(TreeNode * root,int val, int& deep, TreeNode * parent)
{
	//int d=0;
	//TreeNode * p=root;

	//if (root == nullptr)
	//{
	//	return;
	//}
	//else if (root->val == val)
	//{
	//	deep = d;
	//	parent = p;
	//	return;
	//}
	//else
	//{
	//	parent = root;

	//	searchTreeNode(root->left, val, deep,  p);
	//	searchTreeNode(root->right, val, deep, p);
	//	d++;
	//}
	deep = 100;
	parent = root;
}

bool Solution::isCousins(TreeNode * root, int x, int y)
{
	//递归
	int deepX = 0;
	int deepY = 0;
	TreeNode * parentX = root;
	TreeNode * parentY = root;

	//递归函数
	searchTreeNode(root, x, deepX, parentX);
	searchTreeNode(root, x, deepY, parentY);

	cout << deepX << "," << deepY << endl;
	cout << parentX->val << endl;
	cout << parentX->val << endl;

	if (deepX == deepY && parentX != parentY)
	{
		return true;
	}

	return false;
}

int Solution::findJudge(int N, vector<vector<int>>& trust)
{
	int result = -1;
	int len = trust.size();
	set<int> A;

	//边界值判定
	if (N == 1)
		return 1;

	//遍历把每个人都当法官
	for (int i = 1; i <= N; i++)
	{
		A.clear();
		//遍历trust数组
		for (int j = 0; j<len; j++)
		{
			//法官不相信任何人
			if (trust[j][0] == i)
			{
				result = -1;
				break;
			}

			//每个人相信法官，去重插入set
			if (trust[j][1] == i)
				A.insert(trust[j][0]);

			//满足N-1个人相信法官
			if (A.size() == N - 1)
				result = i;
		}
		if (result != -1)
			return result;

	}

	return result;
}
int Solution::numRookCaptures(vector<vector<char>>& board)
{
	//R只有四个方向四个方向去找
	int x = -1, y = -1;
	int result = 0;

	//find R
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j<8; j++)
			if (board[i][j] == 'R')
			{
				x = i;
				y = j;
			}

	}

	if (x == -1 || y == -1)
		return 0;

	//左
	for (int i = y - 1; i >= 0; i--)
	{
		if (board[x][i] == 'B')
		{
			break;
		}

		if (board[x][i] == 'p')
		{
			result++;
			break;
		}
	}

	//右
	for (int i = y + 1; i < 8; i++)
	{
		if (board[x][i] == 'B')
		{
			break;
		}

		if (board[x][i] == 'p')
		{
			result++;
			break;
		}
	}

	//上
	for (int i = x - 1; i >= 0; i--)
	{
		if (board[i][y] == 'B')
		{
			break;
		}

		if (board[i][y] == 'p')
		{
			result++;
			break;
		}
	}

	//右
	for (int i = x + 1; i < 8; i++)
	{
		if (board[i][y] == 'B')
		{
			break;
		}

		if (board[i][y] == 'p')
		{
			result++;
			break;
		}
	}

	return result;
}

/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
TreeNode * Solution::insertIntoMaxTree(TreeNode * root, int val)
{
	//新增父节点
	TreeNode dummy(INT_MAX);
	dummy.right = root;

	//前置阶段
	TreeNode *pre = &dummy;

	//新插入节点
	TreeNode *x = new TreeNode(val);

	//遍历右节点
	for (TreeNode *cur = root; cur != NULL; cur = cur->right) {

		// val大于右节点的值，则插入Node，但是不改变原树指向
		if (val > cur->val) {
			x->left = cur;
			break;
		}
		// val小于节点的值，则记录位置
		else pre = cur;
	}

	//循环遍历结束，x指向应该指向的节点
	//x的前置节点未指向，前置节点已经赋值为pre
	pre->right = x;
	return dummy.right;
}

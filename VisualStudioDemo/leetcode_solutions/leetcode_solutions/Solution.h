#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <queue>

using namespace std;

class Solution
{
public:
	Solution();
	~Solution();
	
	//���ظ��ַ�����Ӵ�
	int lengthOfLongestSubstring(string s);

	//�����������飬��дһ���������������ǵĽ�����
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2);

	//������֮��
	vector<int> Solution::twoSum(vector<int>& nums, int target);

	//����������
	int hitBall(vector<pair<int,int>>& ball);

	// 961. �ظ� N �ε�Ԫ��
	int repeatedNTimes(vector<int>& A);

	//�����ǰ׺
	string longestCommonPrefix(vector<string>& strs);

	//������ת
	int reverse(int x);

	//8. �ַ���ת������ (atoi)
	int myAtoi(string str);
};


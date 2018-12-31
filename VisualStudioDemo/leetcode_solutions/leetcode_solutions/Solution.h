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
	
	//无重复字符的最长子串
	int lengthOfLongestSubstring(string s);

	//给定两个数组，编写一个函数来计算它们的交集。
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2);

	//求两数之和
	vector<int> Solution::twoSum(vector<int>& nums, int target);

	//打气球问题
	int hitBall(vector<pair<int,int>>& ball);

	// 961. 重复 N 次的元素
	int repeatedNTimes(vector<int>& A);

	//最长公共前缀
	string longestCommonPrefix(vector<string>& strs);

	//整数反转
	int reverse(int x);

	//8. 字符串转换整数 (atoi)
	int myAtoi(string str);
};


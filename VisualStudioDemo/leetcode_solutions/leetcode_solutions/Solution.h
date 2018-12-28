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

	int hitBall(vector<pair<int,int>>& ball);
};


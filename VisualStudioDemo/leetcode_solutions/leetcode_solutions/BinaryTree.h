#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

//typedef struct node {
//	int data;
//	struct node *left;
//	struct node *right;
//	struct 
//	node(int x) :data(x), left(NULL), right(NULL) {};
//} BTNode;

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();
	BinaryTree(int val);
	/*
		数组建立二叉树
	*/
	static void createTree(BinaryTree* root, vector<int>::iterator it, vector<int>::iterator end);

	// 打印二叉树
	static void dispTree(BinaryTree* root);

	// 取节点数
	static int getNodeNum(BinaryTree* root);

	// 取最大深度
	static int getDepth(BinaryTree* root);

	// 取K层节点个数
	static int getNodeNumKthLevel(BinaryTree* root, int k);

	// 求叶子节点个数
	static int getNodeNumLeaf(BinaryTree* root);

	//求二叉树的镜像
	static BinaryTree* mirrorRec(BinaryTree* root);

	//判断是否为二分查找树BST
	static bool isValidBST(BinaryTree* root);

	int val; // 值
	int dep; // 深度
	BinaryTree* left;
	BinaryTree* right;
	BinaryTree* parents;
};

class BinarySearchTree :BinaryTree {
public:
	BinarySearchTree();
	~BinarySearchTree();
	BinarySearchTree(int data);

	static BinarySearchTree* createBSTree(int data);

	static void insertBinarySearchTree(BinarySearchTree* root, int data);
};


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
		���齨��������
	*/
	static void createTree(BinaryTree* root, vector<int>::iterator it, vector<int>::iterator end);

	// ��ӡ������
	static void dispTree(BinaryTree* root);

	// ȡ�ڵ���
	static int getNodeNum(BinaryTree* root);

	// ȡ������
	static int getDepth(BinaryTree* root);

	// ȡK��ڵ����
	static int getNodeNumKthLevel(BinaryTree* root, int k);

	// ��Ҷ�ӽڵ����
	static int getNodeNumLeaf(BinaryTree* root);

	//��������ľ���
	static BinaryTree* mirrorRec(BinaryTree* root);

	//�ж��Ƿ�Ϊ���ֲ�����BST
	static bool isValidBST(BinaryTree* root);

	int val; // ֵ
	int dep; // ���
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


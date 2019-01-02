#include "BinaryTree.h"



BinaryTree::BinaryTree()
{

}


BinaryTree::~BinaryTree()
{
}

BinaryTree::BinaryTree(int val)
{
	this->val = val;
	this->dep = 1;
	this->parents = this;
	this->left = NULL;
	this->right = NULL;
}

void BinaryTree::createTree(BinaryTree* root, vector<int>::iterator it, vector<int>::iterator end)
{
	//�˳�������dep���3
	if (it == end)
		return;

	//������
	if (root->val >= *it)
	{
		BinaryTree *left = new BinaryTree(*it);
		root->left = left;
		left->parents = root;
		left->dep = root->dep + 1;
		cout << "����������:" << left->val << "," << left->dep << endl;
		BinaryTree::createTree(left, it + 1,end);
	}
	//������
	else
	{
		BinaryTree *right = new BinaryTree(*it);
		root->right = right;
		right->parents = root;
		right->dep = root->dep + 1;
		cout << "����������:" << right->val << "," << right->dep << endl;
		BinaryTree::createTree(right, it + 1,end);
	}	
}

void BinaryTree::dispTree(BinaryTree* root)
{
	if (root == NULL)
		return;

	//�������
	cout << "�ڵ�:" << root->val << ",���:" << root->dep << endl;
	dispTree(root->left);
	dispTree(root->right);

	if (1 == 0)
	{
		//�������		
		dispTree(root->left);
		cout << "�ڵ�:" << root->val << ",���:" << root->dep << endl;
		dispTree(root->right);

		//�������		
		dispTree(root->left);
		dispTree(root->right);
		cout << "�ڵ�:" << root->val << ",���:" << root->dep << endl;
	}
}

int BinaryTree::getNodeNum(BinaryTree * root)
{
	if (root == NULL)
		return 0;

	return getNodeNum(root->left)+ getNodeNum(root->right)+1;
}

int BinaryTree::getDepth(BinaryTree * root)
{
	if (root == NULL)
		return 0;

	return max(getDepth(root->left), getDepth(root->right)) + 1;
	/*ʹ��algorithm�е�max����
	return (getDepth(root->left)>getDepth(root->right)? getDepth(root->left): getDepth(root->right))+1;*/
}

int BinaryTree::getNodeNumKthLevel(BinaryTree * root,int k)
{
	if (root == NULL || k < 1)
		return 0;

	//cout << "k:" << k << ",left:" << ",root->val:" << root->val << ",root->dep:" << root->dep << endl;
	//cout << "k:" << k << ",right:" << ",root->val:" << root->val << ",root->dep" << root->dep << endl;

	if (k == 1)
		return 1;

	return getNodeNumKthLevel(root->left, k-1) + getNodeNumKthLevel(root->right, k-1);
}

int BinaryTree::getNodeNumLeaf(BinaryTree * root)
{
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL)
		return 1;

	return getNodeNumLeaf(root->left)+ getNodeNumLeaf(root->right);
}

bool BinaryTree::isValidBST(BinaryTree * root)
{
	if (root == NULL)
		return true;

	// �ж����� left < root <  right ������ֻ���ж���������������Ĺ���
	/*if (root->left != NULL && root->left->val > root->val) {
		return false;
	}

	if (root->right != NULL && root->right->val < root->val) {
		return false;
	}

	return isValidBST(root->left) && isValidBST(root->right);*/

	// ����Ҫ�������
	bool left = isValidBST(root->left);
	if (!left) {
		return false;
	}
	if (root->val > root->parents->val) {
		return false;
	}

	bool right = isValidBST(root->right);
	if (!right) {
		return false;
	}
	if (root->val < root->parents->val) {
		return false;
	}

	return true;
}

BinarySearchTree::BinarySearchTree()
{
}

BinarySearchTree::~BinarySearchTree()
{
}

BinarySearchTree::BinarySearchTree(int data)
{
	val = data;
	dep = 1;
	left = NULL;
	right = NULL;
	parents = this;
}

BinarySearchTree * BinarySearchTree::createBSTree(int data)
{
	BinarySearchTree* root = new BinarySearchTree(data);

	return root;
}

void BinarySearchTree::insertBinarySearchTree(BinarySearchTree* root, int data)
{
	if (root == NULL)
		return;

	if (data < root->val)
	{
		BinarySearchTree* left = new BinarySearchTree(data);
		root->left = left;
		left->parents = root;
		left->dep = root->dep + 1;
	}
	else if (data > root->val)
	{
		BinarySearchTree* right = new BinarySearchTree(data);
		root->right = right;
		right->parents = root;
		right->dep = root->dep + 1;
	}

	return ;
}

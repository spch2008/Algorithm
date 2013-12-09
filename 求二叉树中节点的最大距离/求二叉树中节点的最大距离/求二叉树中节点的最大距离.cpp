// 求二叉树中节点的最大距离.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <cstdlib>
using namespace std;

struct node
{
	node() : left(NULL), right(NULL), data(0) {}
	node *left;
	node *right;
	int data;
};

struct data : private node  //私有继承，不允许使用node的数据
{
	data(int dep = 0, int dis = 0){ depth = dep; distance = dis;}
	int depth;
	int distance;
	node *r;       //max root
};


data getMaxDis(node *root)
{
	if(root == NULL)
		return data(-1, 0);  // return -1 because the leaf's height is zero

	data lh = getMaxDis(root->left);
	data rh = getMaxDis(root->right);

	data result;
	result.depth = max(lh.depth, rh.depth) + 1;
	result.distance = max ( max(lh.distance, rh.distance), lh.depth + rh.depth + 2);  //distance is the value we want
	
	//get the max root
	if(result.distance == lh.depth + rh.depth + 2)
		result.r = root;

	return result;
}


void link(node* root, int left, int right)
{

	if(left == 0)
		root->left = NULL;
	else
	root->left = new node; 

	if(right == 0)
		root->right = NULL;
	else
		root->right = new node;

}

//构建编程之美图3-13右图 的树
void init(node*& root)
{
	root = new node;

	link(root, 0, 1);

	node* tmp = root->right;
	link(tmp, 1, 1);

	node *left = tmp->left; 
	link(left, 1, 0);

	left = left->left;
	link(left, 1, 0);

	node *right = tmp->right;
	link(right, 1, 1);

	left = right->left;
	link(left, 0 ,1);

}

int main()
{
	node *root;
	init(root);

	cout << getMaxDis(root).distance << endl;

	system("pause");
	return 0;
}


// how to get the max root
/*
   左边的子树高度+右边子树高度 == distance的结点
*/


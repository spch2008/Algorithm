// 测试.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>
#include <set>

using namespace std;


struct node
{
	node *left;
	node *right;
	char value;
};


void rebuild(char *postOrder, char *inOrder, int treeLen, node **root)
{
	if(inOrder == NULL || postOrder == NULL)
		return;

	char *oldPostOrder = postOrder;
	for(int i = 0; i < treeLen-1; i++)
		postOrder++;

	node *tmp = new node;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->value = *postOrder;
	*root = tmp;

	if(treeLen == 1)
		return;

	char *inRootPos = inOrder;
	char rootVal    = *postOrder;
	while(*inRootPos != rootVal)
		inRootPos++;

	int treeLeftLen  = inRootPos - inOrder;
	int treeRightLen = treeLen - treeLeftLen - 1;



	if(treeRightLen > 0)
		rebuild(oldPostOrder + treeLeftLen, inRootPos+1, treeRightLen, &((*root)->right) );


	if(treeLeftLen > 0)
		rebuild(oldPostOrder, inOrder, treeLeftLen, &((*root)->left) );

}



/*
//重建过程，关键在于新中序的查找
void rebuild(char* preOrder, char *inOrder, int treeLen, node **root)
{
	if(preOrder == NULL || inOrder == NULL)
		return;


	node *tmp = new node;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->value = *preOrder;
    *root = tmp;

	if(treeLen == 1)
		return;


	//find left tree from inOrder
	char *inRootPos = inOrder;
	char rootVal  = *preOrder;
	while( rootVal != *inRootPos)
		inRootPos++;

	int leftTreeLen  = inRootPos - inOrder;
	int rightTreeLen = treeLen - leftTreeLen - 1; 

	if(leftTreeLen > 0)
		rebuild(preOrder+1, inOrder, leftTreeLen, &((*root)->left) );

	if(rightTreeLen > 0)
		rebuild(preOrder + leftTreeLen + 1, inRootPos + 1, rightTreeLen, &((*root)->right) );
}
*/
void preVisit(node *root)
{
	if( root != NULL)
	{
		cout << root->value;
		preVisit(root->left);
		preVisit(root->right);
	}
}

void inVisit(node *root)
{
	if( root != NULL)
	{
		inVisit(root->left);
		cout << root->value;
		inVisit(root->right);
	}
}

int main()
{
	char *preOrder = "dbefca";
	char *inOrder  = "dbaecf";

	node *root = NULL;
	rebuild(preOrder, inOrder, strlen(preOrder), &root);
	
	preVisit(root);
	cout << endl;
	inVisit(root);
	cout << endl;

	system("pause");
	return 0;
}


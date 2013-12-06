// ·Ö²ã±éÀú¶þ²æÊ÷.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>

using namespace std;


struct node
{
	node *left;
	node *right;
	char value;
};

void visitAtLevel(node *root, int level)
{
	if(root == NULL)
		return;
	if(level == 0)
		cout << root->value << " ";
	else
	{
		visitAtLevel(root->left, level-1);
		visitAtLevel(root->right, level-1);
	}

}

inline int max(int a, int b)
{
	return a > b ? a : b;
}
int level(node *root)
{
	if(root == NULL)
		return 0;
	return max(level(root->left), level(root->right)) + 1;
}

void levelVisitRecur(node *root)
{
	int l = level(root);
	for(int i = 0; i < l; i++)
	{
		visitAtLevel(root, i);
		cout << endl;
	}
}

void levelVisitNonRecur(node *root)
{
	int l = level(root);
	vector<node*> v;

	v.push_back(root);
	int cur = 0;
	int last = v.size();

	while(cur < v.size())
	{
		last = v.size();
		while(cur < last)
		{
			node *tmp = v[cur];
			if(tmp->left != NULL)
				v.push_back(tmp->left);
			if(tmp->right != NULL)
				v.push_back(tmp->right);

			cout << tmp->value << " ";
			cur++;
		}
		cout << endl;
	}
	cout << endl;
}


int main(int argc, char* argv[])
{
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
struct node
{
	int num;
	node* left;
	node* right;
};
node* makeempty(node* tree)
{
	if (tree != NULL)
	{
		makeempty(tree->left);
		makeempty(tree->right);
		free(tree);
	}
	return NULL;
}
node* find(int num, node* tree)
{
	if (tree == NULL)
		return NULL;
	if (num>tree->num)
	{
		find(num, tree->right);
	}
	else if (num<tree->num)
	{
		find(num, tree->left);
	}
	return tree;
}
node* findmin(node* tree)
{
	if (tree->left != NULL)
		findmin(tree->left);
	return tree;
}
node* findmax(node* tree)
{
	if (tree->right != NULL)
		findmax(tree->right);
	return tree;
}
node* insert(int num, node* tree)
{
	if (tree == NULL)
	{
		tree = (node*)malloc(sizeof(node));
		tree->num = num;
		tree->left = NULL;
		tree->right = NULL;
	}
	else
	{
		if (tree->num == num)
			return tree;
		else if (tree->num>num)
			tree->left=insert(num, tree->left);
		else
			tree->right=insert(num, tree->right);
	}
	return tree;
}
node* deleteone(int num, node* tree)
{
	node* temp;
	if (tree == NULL)
		return NULL;
	else
	{
		if (num>tree->num)
			deleteone(num, tree->right);
		else if (num<tree->num)
			deleteone(num, tree->left);
		else
		{
			if (tree->left&&tree->right)
			{
				temp = findmin(tree->right);
				tree->num = temp->num;
				tree->right = deleteone(temp->num, tree->right);
			}
			else
			{
				if (tree->left == NULL)
				{
					temp = tree;
					tree = tree->right;
					free(temp);
				}
				else
				{
					temp = tree;
					tree = tree->left;
					free(temp);
				}
			}
		}
	}
	return tree;
}

void midOrder(node* tree)
{
	if (tree == NULL) return;
	midOrder(tree->left);
	printf("%d\n",tree->num);
	midOrder(tree->right);
}
int main()
{
	node* tree;
	tree = NULL;
	for (int i = 0; i<3; i++)
	{
		int a;
		scanf("%d", &a);
		tree=insert(a, tree);
	}
	midOrder(tree);
	return 0;
}

#include <stdio.h>
#include <math.h>
struct avltree
{
	int num;
	avltree* left;
	avltree* right;
	int height;
};
int height(avltree* tree)
{
	if(tree==NULL)
		return -1;
	else
		return tree->height;
}
avltree* singlerotatewithleft(avltree* k1)
{
	avltree* temp;
	temp=k1->left;
	k1->left=temp->right;
	temp->right=k1;
	k1->height=max(height(k1->left),height(k1->right)+1);
	temp->height=max(height(temp->left),height(temp->right)+1);
	return temp;
}
avltree* singlerotatewithright(avltree* k1)
{
	avltree* temp;
	temp=k1->right;
	k1->right=temp->left;
	temp->left=k1;
	k1->height=max(height(k1->left),height(k1->right)+1);
	temp->height=max(height(temp->left),height(temp->right)+1);
	return temp;
}
avltree* doublerotatewithleft(avltree* tree)
{
	tree->left=singlerotatewithright(tree->left);
	return singlerotatewithleft(tree);
}
avltree* doublerotatewithright(avltree* tree)
{
	tree->right=singlerotatewithleft(tree->left);
	return singlerotatewithright(tree);
}
avltree* insert(int num,avltree* tree)
{
	if (tree == NULL)
	{
		tree = (node*)malloc(sizeof(node));
		tree->num = num;
		tree->left = NULL;
		tree->right = NULL;
		tree->height=0;
	}
	else
	{
		if (tree->num == num)
			return tree;
		else if (tree->num>num)
		{
			tree->left=insert(num, tree->left);
			if(abs(height(tree->left)-height(tree->right))==2)
			{
				if(num<tree->left->num)
					singlerotatewithleft(tree);
				else
					doublerotatewithleft(tree);
			}
		}
		else
		{
			tree->right=insert(num, tree->right);
			if(abs(height(tree->left)-height(tree->right))==2)
			{
				if(num>tree->right->num)
					singlerotatewithright(tree);
				else
					doublerotatewithright(tree);
			}
		}
		tree->height=max(height(tree->left),height(tree->right))+1;
	}
	return tree;
}

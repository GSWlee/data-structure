#include <iostream>
using namespace std;
class TreeNode
{
	public:
		int element;
		TreeNode* left;
		TreeNode* right;
};
class Searchtree
{
	private:
		TreeNode* tree;
	public:
		Searchtree()
		{
			tree=nullptr;
		}
		bool isempty()
		{
			return tree==nullptr?true:false;
		}
		TreeNode* find(int num, node* tree)
		{
			if (isempty())
				return nullptr;
			TreeNode* temp;
			if (num>tree->element)
			{
				temp=find(num, tree->right);
			}
			else if (num<tree->element)
			{
				temp=find(num, tree->left);
			}
			return temp;
		}
		TreeNode* findmin(TreeNode* tree)
		{
			TreeNode* temp;
			if (tree->left != nullptr)
				temp=findmin(tree->left);
			return temp;
		}
		TreeNode* findmax(TreeNode* tree)
		{
			TreeNode* temp;
			if (tree->right != nullptr)
				temp=findmax(tree->right);
			return temp;
		}
		TreeNode* insert(int num, TreeNode* tree)
		{
			if (tree == nullptr)
			{
				tree = new TreeNode;
				tree->element = num;
				tree->left = nullptr;
				tree->right = nullptr;
			}
			else
			{
				if (tree->element == num)
					return tree;
				else if (tree->element>num)
					tree->left=insert(num, tree->left);
				else
					tree->right=insert(num, tree->right);
			}
			return tree;
		}
		TreeNode* deleteone(int num, TreeNode* tree)
		{
			TreeNode* temp;
			if (tree == nullptr)
				return nullptr;
			else
			{
				if (num>tree->element)
					deleteone(num, tree->right);
				else if (num<tree->num)
					deleteone(num, tree->left);
				else
				{
					if (tree->left&&tree->right)
					{
						temp = findmin(tree->right);
						tree->element = temp->element;
						tree->right = deleteone(temp->element, tree->right);
					}
					else
					{
						if (tree->left == nullptr)
						{
							temp = tree;
							tree = tree->right;
							delete temp;
						}
						else
						{
							temp = tree;
							tree = tree->left;
							delete temp;
						}
					}
				}
			}
			return tree;
		}
		void midOrder(TreeNode* tree)
		{
			if (tree == nullptr)
				return;
			midOrder(tree->left);
			cout<<tree->element<<endl;
			midOrder(tree->right);
		}
};

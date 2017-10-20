/*
*Author: GSWlee@ccnu
*Date: 2017-10-19
*Descriotion: RedBlackSearchTree
*/

enum Color { RED,BLACK};


/*-------------------------------------------------------*/
/**
*	class RBTreeNode
*	@brief 对于红黑树结点的声明
*/

template <class T>
class RBTreeNode {
	public:
		Color color_;
		T element_;
		RBTreeNode<T>* right_;
		RBTreeNode<T>* left_;
		RBTreeNode<T>* parent_;
		RBTreeNode(Color color,T element,RBTreeNode<T>* p,RBTreeNode<T>*l,RBTreeNode<T>*r);
		bool IsRed();
		void SetColor(Color color);
		void SetParent(RBTreeNode<T>* p);
}


/*-------------------------------------------------------*/
/**
*	class RedBlackSearchTree
*	@brief 对于红黑树的声明
*/

template <class T>
class RBTree {
	public:
		RBTree();
		~RBTree();
		void Delete(RBTreeNode<T>* root);
		void FixColor(RBTreeNode<T>* node);
		RBTreeNode<T>* SearchKey(T key,RBTreeNode<T>* root=root_);
		RBTreeNode<T>* MaxNode(RBTreeNode<T>* root=root_);
		RBTreeNode<T>* MinNode(RBTreeNode<T>* root=root_);
		RBTreeNode<T>* PreNode(RBTreeNode<T>* root);
		RBTreeNode<T>* NextNode(RBTreeNode<T>* root);
		RBTreeNode<T>* LeftRotate(RBTreeNode<T>* node);
		RBTreeNode<T>* RightRotate(RBTreeNode<T>* node);
		RBTreeNode<T>* Insert(T key,RBTreeNode<T>* root,RBTreeNode<T>* parent);
		void Insert(T key);//@bug
		void Remove(RBTreeNode<T>* node);//@bug
		void Remove(T key);
	private:
		RBTreeNode<T>* root_;
}

template <class T>
RBTreeNode<T>::RBTreeNode(Color color,T element,RBTreeNode<T>* p,RBTreeNode<T>*l,RBTreeNode<T>*r) {
	color_=color;
	element_=element;
	right_=r;
	left_=l;
	parent_=p;
}

template <class T>
bool RBTreeNode<T>::IsRed() {return color_==RED;}

template <class T>
void RBTreeNode<T>::SetColor(Color color) {color_=color;}

template <class T>
void RBTreeNode<T>::SetParent(RBTreeNode<T>* p) {parent_=p;}

template <class T>
RBTree<T>::RBTree() { root_=nullptr;}

/**
*	@brief 解决两子结点都为红结点的情况
*/

template <class T>
void RBTree<T>::FixColor(RBTreeNode<T>* node) {
	node->right_->color_=BLACK;
	node->right_->color_=BLACK;
	node->color_=RED;
}

/**
*	@brief 利用红黑树完成对于key的查找
*	@return 指向key值所在的结点的指针，如果没有找到返回值为nullptr
*/

template <class T>
RBTreeNode<T>* RBTree<T>::SearchKey(T key,RBTreeNode<T>* root=root_) {
	if(root==nullptr||root->element_=key)
		return root;
	if (root->element_>key) return SearchKey( key, root->right_);
	else return SearchKey(key,root->left_);
}

template <class T>
RBTreeNode<T>* RBTree<T>::MaxNode(RBTreeNode<T>* root=root) {
	RBTreeNode<T>* temp;

	temp=root;
	while(temp->right_!=nullptr) {temp=temp->right_;}

	return temp;
}

template <class T>
RBTreeNode<T>* RBTree<T>::MinNode(RBTreeNode<T>* root=root_) {
	RBTreeNode<T>* temp;

	temp=root;
	while(temp->left_!=nullptr) {temp=temp->left_;}

	return temp;
}

/**
*	@brief 查找node的前驱元素，即比node大的最小元
*	@return 指向node前驱元素的结点的指针
*/

template <class T>
RBTreeNode<T>* RBTree<T>::PreNode(RBTreeNode<T>* node) {
	return MinNode(node->parent_);
}

/**
*	@brief 查找node的后继元素，即比node小的最大元
*	@return 指向node后继元素的结点的指针
*/

template <class T>
RBTreeNode<T>* RBTree<T>::NextNode(RBTreeNode<T>* root) {
	return MaxNode(root->right_);
}

/**
*	@brief 将node结点左旋
*/

template <class T>
RBTreeNode<T>* RBTree<T>::LeftRotate(RBTreeNode<T>* node) {
	RBTreeNode<T>* temp=node->right_;

	node->right_=temp->left_;
	if (temp->left_!=nullptr) temp->left->parent_=node;
	temp->parent_=node->parent_;
	temp->left_=node;
	node->parent_=temp;

	return temp;
}

/**
*	@brief 将node结点右旋
*/

template <class T>
RBTreeNode<T>* RBTree<T>::RightRotate(RBTreeNode<T>* node) {
	RBTreeNode<T>* temp=node->left_;

	node->left_=temp->right_;
	if (temp->right_!=nullptr) temp->right_->parent_=node;
	temp->parent_=node->parent_;
	temp->right_=node;
	node->parent_=temp;

	return temp;
}


/**
*	@brief 在红黑树中；插入元素，并保持红黑树的姿态
*/

template <class T>
void RBTree<T>::Insert(T key) {
	root_=Insert(key,root_,nullptr);
	root_->color_=BLACK;							//保持根节点恒为黑结点
}

template <class T>
RBTreeNode<T>* RBTree<T>::Insert(T key,RBTreeNode<T>* node,RBTreeNode<T>* parent) {
	if(node==nullptr) return new RBTreeNode(RED,key,parent,nullptr.nullptr);

	if (node->element_>key) node->right_=Insert(key,node->right_,node);
	else if (node->element_<key) node->left_=Insert(key,node->left_,root);

	//插入后对于红黑树的修正
	if (IsRed(node->right_)&&!IsRed(node->left_)) node=LeftRotate(node);	    //存在红节点为右节点时
	if (IsRed(node->left_)&&IsRed(node->left_->left_)) node=RightRotate(node);  //存在两个红节点相连时
	if (IsRed(node->right_)&&IsRed(node->right_)) FixColor(node);				//存在两个子节点都为红节点时

	return node;
}


/**
*	@brief 删除红黑树中键值为key的元素
*/

template <class T>
void Remove(T key) {
	RBTreeNode<T>* node=SearchKey(key);

	if(nodeQ=nullptr)
		Remove(node);
}

/**
*	@brief 删除node节点
*/

template <class T>//@bug
void Remove(RBTreeNode<T>* node) {
	RBTreeNode<T>* child,*parent;
	Color color;

	if(node->left_&&node->right_) {
		RBTreeNode<T>* replace=MinNode(node);
		if (node->parent_) {
			if (node->parent_->left_==node) node->parent_->left_=replace;
			else node->parent_->right_=replace;
		}
		else root_=replace;
		child=replace->right_;
		parent=replace->parent_;
		color=replace->color_;
		if(parent==node) parent=replace;
		else {
			if(child) 	child->parent_=parent;
			parent->left_=child;
			replace->right_=node->right_;
			node->right_->parent_=replace;
		}
		replace->parent_=node->parent_;
		replace->color_=node->color_;
		replace->left_=node->left_;
	}
}
/**
*	@brief 删除root与root的所有子树
*/

template <class T>
void RBTree<T>::Delete(RBTreeNode<T>* root) {
	if(root==nullptr) return;
	else {
		RBTreeNode<T>* left_root=root->left_;
		RBTreeNode<T>* right_root=root->right_;
		delete root;
		Delete(left_root);
		Delete(right_root);
	}
}

template <class T>
RBTree<T>::~RBTree() { Delete(root_);}

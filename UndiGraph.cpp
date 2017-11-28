/*
*Author GSWlee@ccnu
*Date 2017-10-25
*Descriotion: UndiGraph
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

/*-----------------------------------------------------*/
/**
*	class GraphNode
*	@brief 对无向图中结点的声明
*/

template <class T>
class GraphNode {
public:
	T name_;
	vector<T> LinkNode_;
	GraphNode(T name);
	bool IsCircle();
	void DeleteLinkNode(T name);
	void AddLinkNode(T name);
};

/*-----------------------------------------------------*/
/**
*	class UndiGraph
*	@brief 对于无向图的声明
*/

template <class T>
class UndiGraph {
public:
	string name_;
	vector<GraphNode<T>> Node_;
	UndiGraph(string name);
	int SumNode();
	int SumLink();
	int NodeLink(T name);
	void AddNode(T name);
	void AddLink(T name1, T name2);
	void DeleteLink(T name1, T name2);
	void DeleteNode(T name);
	int FindNode(T name);
	int DFSNodeLinkNode(T name);
	int BFSNodeLinkNode(T name);
	vector<int> DFSMarkNode(T name, vector<int> arr);
	vector<int> BFSMarkNode(T name, vector<int> arr);
};

template <class T>
GraphNode<T>::GraphNode(T name) { name_ = name; }


/**
*	@brief 添加一个边
*	@name 新建边另一节点的名字
*/

template <class T>
void GraphNode<T>::AddLinkNode(T name) {
	if (LinkNode_.size() == 0) {
		LinkNode_.push_back(name);
		return;
	}
	int i = 0;
	for (; i<LinkNode_.size(); i++) {
		if (LinkNode_[i] == name) break;
	}

	if (i >= LinkNode_.size()) LinkNode_.push_back(name);
}


/**
*	@brief 删除一个边
*	@name 删除的边的另外一个节点
*/

template <class T>
void GraphNode<T>::DeleteLinkNode(T name) {
	int i = 0;
	for (; i<LinkNode_.size(); i++) {
		if (LinkNode_[i] == name) break;
	}
	if (i >= LinkNode_.size()) return;
	if (LinkNode_[i] == name) LinkNode_.erase(i);
}

/**
*	@brief 判断是否存在自环
*/

template <class T>
bool GraphNode<T>::IsCircle() {
	int i = 0;
	for (; i<LinkNode_.size(); i++) {
		if (LinkNode_[i] == name_) break;
	}

	return i < LinkNode_.size();
}

template <class T>
UndiGraph<T>::UndiGraph(string name) { name_ = name; }


/**
*	@brief 在图中添加一个节点
*/

template <class T>
void UndiGraph<T>::AddNode(T name) {
	GraphNode<T> temp(name);
	Node_.push_back(temp);
}


/**
*	@brief 在图中添加一个边
*/

template <class T>
void UndiGraph<T>::AddLink(T name1, T name2) {
	int i = 0;
	int start = -1, last = -1;
	while (i<Node_.size()) {
		if (Node_[i].name_ == name1) start = i;
		if (Node_[i].name_ == name2) last = i;
		i++;
	}
	if (start != -1 && last != -1) {
		Node_[start].AddLinkNode(name2);
		Node_[last].AddLinkNode(name1);
	}
}


/**
*	@brief 删除边
*/

template <class T>
void UndiGraph<T>::DeleteLink(T name1, T name2) {
	int i = 0;
	int start = -1, last = -1;
	while (i<Node_.size()) {
		if (Node_[i].name_ == name1) start = i;
		if (Node_[i].name_ == name2) last = i;
		i++;
	}
	if (start != -1 && last != -1) {
		Node_[start].DeleteLinkNode(name2);
		Node_[last].DeleteLinkNode(name1);
	}
}


/**
*	@brief 删除结点
*/

template <class T>
void UndiGraph<T>::DeleteNode(T name) {
	int i = 0;
	while (i<Node_.size() && Node_[i].name_ != name) i++;
	if (Node_[i].name_ != name) return;
	Node_.erase(i);
	i = 0;
	while (i<Node_.size()) {
		Node_[i].DeleteLinkNode(name);
		i++;
	}
}

template <class T>
int UndiGraph<T>::SumNode() { return Node_.size(); }

/**
*	@brief 返回结点的度数
*/

template <class T>
int UndiGraph<T>::NodeLink(T name) {
	int i = 0;
	while (i<Node_.size()) {
		if (Node_[i].name_ == name) break;
		i++;
	}
	if (Node_[i].name_ == name) i = Node_[i].LinkNode_.size();
	return i;
}


/**
*	@brief 返回图的总边数
*/

template <class T>
int UndiGraph<T>::SumLink() {
	int sum = 0;
	for (int i = 0; i < Node_.size(); i++) {
		sum += Node_[i].LinkNode_.size();
		if (Node_[i].IsCircle()) sum++;
	}
	return sum / 2;
}

/**
*	 @brief 返回目标节点的迭代器
*/

template <class T>
int UndiGraph<T>::FindNode(T name) {
	int i = 0;
	for (; i<Node_.size(); i++) {
		if (Node_[i].name_ == name) return i;
	}
	return -1;
}

/**
*	@brief 在深度优先搜素中对顶点进行标记
*	@return 返回标记了点的数组
*/

template <class T>
vector<int> UndiGraph<T>::DFSMarkNode(T name, vector<int> arr) {
	int i = FindNode(name), temp;
	arr[i] = 1;
	cout << Node_[i].name_;											//按照深度优先的次序进行输出
	const int sum = Node_[i].LinkNode_.size();
	for (int j = 0; j<sum; j++) {
		temp = FindNode(Node_[i].LinkNode_[j]);
		if (arr[temp] == 0) arr=DFSMarkNode(Node_[i].LinkNode_[j], arr);
	}
	return arr;
}


/**
*	@brief 找出node的所有连通节点
*	@return 返回node连通结点的个数
*	@tips 基于深度优先搜索
*/

template <class T>
int UndiGraph<T>::DFSNodeLinkNode(T name) {
	int sum = 0;
	const int n = Node_.size();
	vector<int> node(n, 0);
	node=DFSMarkNode(name, node);
	for (int j = 0; j<n; j++) {
		if (node[j] == 1) {
			sum++;
			//cout << Node_[j].name_ << " ";					//按照一般顺序进行输出
		}
	}
	return sum;
}



/**
*	@brief 找出于node节点相连通的节点的最短路径
*	@return 返回node连通结点的个数
*	@tips 基于广度优先搜索
*/

template <class T>
int UndiGraph<T>::BFSNodeLinkNode(T name) {
	int sum = 0;
	int temp=FindNode(name);
	vector<vector<T>> path;
	queue<int> arr;
	arr.push(temp);
	while(arr.size()>0) {
		temp=arr.front();
		path[temp].push_back(Node_[temp].name_);
		for(int i=0;i<Node_[temp].LinkNode_.size();i++) {
			int q=FindNode(Node_[temp].LinkNode_[i]);
			if(arr.count(q)||path[q].size()) continue;
			arr.push(q);
			path[q].assign(path[temp].begin(),path[i].end());
		}
		arr.pop();
	}
	for (int j = 0; j<Node_.size(); j++) {
		if (path[j].size()!=0) {
			sum++;
			for(int m=0;m<path[j].size();m++)
				cout<<path[j][m]<<" ";
		}
	}
	return sum;
}

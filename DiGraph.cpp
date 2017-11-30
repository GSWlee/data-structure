/*
*Author GSWlee@ccnu
*Date 2017-11-28
*Descriotion: DiGraph
*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

/*-----------------------------------------------
*
*	class GraphNode
*	@brief 对有向图节点的声明
*/

template <class T>
class GraphNode {
public:
	T name_;
	vector<T> LinkTo_;
	vector<T> BeLinked_;
	GraphNode(T name);
	bool IsCircle();
	void DeleteLinkNode(T start, T end);
	void DeleteLinkNode(T name);
	void AddLinkNode(T strat, T end);
};

/*-----------------------------------------------
*
*	class DiGraph
*	@brief 对于有向图的声明
*/

template <class T>
class DiGraph {
public:
	string name_;
	vector<GraphNode<T>> Node_;
	DiGraph(string name);
	int SumNode();
	int SumLink();
	int NodeLink(T name, int i = 0);
	void AddNode(T name);
	void AddLink(T start, T end);
	void DeleteLink(T start, T end);
	void DeleteNode(T name);
	int FindNode(T name);
	vector<int> MarkNode(T name, vector<int> arr);
	int MarkNode(T name, vector<int> mark, vector<int>* node);
	vector<int> MarkNode(T name, vector<int> mark, vector<int>* node, vector<int>* sort);
	bool IsLinked(T start, T end);
	bool IsCircle();
	vector<int> TopoSort();;

};

template <class T>
GraphNode<T>::GraphNode(T name) { name_ = name; }


/**
*	@brief 添加一个边
*	@start end 新建边的起点和终点
*/

template <class T>
void GraphNode<T>::AddLinkNode(T start, T end) {
	if (start == name_) {
		for (int i = 0; i<LinkTo_.size(); i++) {
			if (LinkTo_[i] == end)
				return;
		}
		LinkTo_.push_back(end);
	}
	if (end == name_) {
		for (int i = 0; i<BeLinked_.size(); i++) {
			if (BeLinked_[i] == end)
				return;
		}
		BeLinked_.push_back(end);
	}
}


/**
*	@brief 删除一个边
*	@start end 删除边的起点和终点
*/

template <class T>
void GraphNode<T>::DeleteLinkNode(T start, T end) {
	int i = 0;
	if (start == name_) {
		for (; i<LinkTo_.size(); i++) {
			if (LinkTo_[i] == end) break;
		}
		if (i >= LinkTo_.size()) return;
		if (LinkTo_[i] == end) LinkTo_.erase(i);
	}
	i = 0;
	if (end == name_) {
		for (; i<BeLinked_.size(); i++) {
			if (BeLinked_[i] == end) break;
		}
		if (i >= BeLinked_.size()) return;
		if (BeLinked_[i] == end) BeLinked_.erase(i);
	}
}

template <class T>
void GraphNode<T>::DeleteLinkNode(T name) {
	int i = 0;
	for (; i<LinkTo_.size(); i++) {
		if (LinkTo_[i] == end) break;
	}
	if (i >= LinkTo_.size()) return;
	if (LinkTo_[i] == end) LinkTo_.erase(i);
	for (i = 0;; i<BeLinked_.size(); i++) {
		if (BeLinked_[i] == end) break;
	}
	if (i >= BeLinked_.size()) return;
	if (BeLinked_[i] == end) BeLinked_.erase(i);
}


/**
*	@brief 判断是否存在自环
*/

template <class T>
bool GraphNode<T>::IsCircle() {
	int i = 0;
	for (; i<LinkTo_.size(); i++) {
		if (LinkTo_[i] == name_) break;
	}

	return i < LinkTo_.size();
}

template <class T>
DiGraph<T>::DiGraph(string name) { name_ = name; }

/**
*	@brief 在图中添加一个节点
*/

template <class T>
void DiGraph<T>::AddNode(T name) {
	GraphNode<T> temp(name);
	Node_.push_back(temp);
}

/**
*	@brief 在图中添加一个边
*/

template <class T>
void DiGraph<T>::AddLink(T start, T end) {
	int i = 0;
	int first = FindNode(start), last = FindNode(end);
	if (first != -1 && last != -1) {
		Node_[first].AddLinkNode(start, end);
		Node_[last].AddLinkNode(start, end);
	}
}

/**
*	@brief 删除边
*/

template <class T>
void DiGraph<T>::DeleteLink(T start, T end) {
	int i = 0;
	int first = -1, last = -1;
	while (i<Node_.size()) {
		if (Node_[i].name_ == start) first = i;
		if (Node_[i].name_ == end) last = i;
		i++;
	}
	if (start != -1 && last != -1) {
		Node_[first].DeleteLinkNode(start, end);
		Node_[last].DeleteLinkNode(start, end);
	}
}

/**
*	@brief 删除结点
*/

template <class T>
void DiGraph<T>::DeleteNode(T name) {
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

/**
*	@brief 返回结点的度数
*	@i i==0 入度加出度，i==1 入度，i==2 出度
*/

template <class T>
int DiGraph<T>::NodeLink(T name, int i = 0) {
	int j = 0;
	while (j<Node_.size()) {
		if (Node_[j].name_ == name) break;
		j++;
	}
	if (Node_[j].name_ == name) {
		if (i == 0)
			j = Node_[j].LinkTo_.size() + Node_[j].BeLinked_.size();
		else if (i == 1)
			j = Node_[j].BeLinked_.size();
		else
			j = Node_[j].LinkTo_.size();
	}
	return j;
}

/**
*	@brief 返回图的总边数
*/

template <class T>
int DiGraph<T>::SumLink() {
	int sum = 0;
	for (int i = 0; i < Node_.size(); i++) {
		sum += Node_[i].LinkTo_.size();
	}
	return sum;
}



/**
*	 @brief 返回目标节点的位置
*/

template <class T>
int DiGraph<T>::FindNode(T name) {
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
vector<int> DiGraph<T>::MarkNode(T name, vector<int> arr) {
	int i = FindNode(name), temp;
	arr[i] = 1;
	//cout << Node_[i].name_;											//按照深度优先的次序进行输出
	const int sum = Node_[i].LinkTo_.size();
	for (int j = 0; j<sum; j++) {
		temp = FindNode(Node_[i].LinkTo_[j]);
		if (arr[temp] == 0) arr = MarkNode(Node_[i].LinkTo_[j], arr);
	}
	return arr;
}


/**
*	@brief 判断start到end是否可达
*	@tip 基于深度优先
*/

template <class T>
bool  DiGraph<T>::IsLinked(T start, T end) {
	const int n = Node_.size();
	vector<int> node(n, 0);
	node = MarkNode(start, node);
	int t = FindNode(end);
	return node[t];
}

/**
*	@brief 判断是否为无环有向图
*/

template <class T>
bool DiGraph<T>::IsCircle() {
	const int n = Node_.size();
	int flag = 0;;
	vector<int> node(n, 0), mark(n, 0);
	for (int i = 0; i<node.size(); i++) {
		if (!node[i]) flag = MarkNode(Node_[i].name_, mark, &node);
	}
	if (flag)
		return true;
	return false;
}

template <class T>
int  DiGraph<T>::MarkNode(T name, vector<int> mark, vector<int>* node) {
	int i = FindNode(name), temp;
	int flag = 0;
	mark[i] = 1;
	const int sum = Node_[i].LinkTo_.size();
	for (int j = 0; j<sum; j++) {
		temp = FindNode(Node_[i].LinkTo_[j]);
		(*node)[temp] = 1;
		if (mark[temp] == 1) flag = 1;
		else flag = MarkNode(Node_[i].LinkTo_[j], mark, node);
		if (flag) break;
	}
	return flag;
}


/**
*	@brief 实现对于图中节点的拓扑排序
*/

template <class T>
vector<int>  DiGraph<T>::TopoSort() {
	vector<int> sort;
	const int n = Node_.size();
	vector<int> node(n, 0), mark(n, 0);
	for (int i = 0; i<node.size(); i++) {
		if (!node[i]) mark = MarkNode(Node_[i].name_, mark, &node, &sort);
	}
	for (int i = 0; i < sort.size(); i++) {
		cout << Node_[sort[i]].name_ << endl;
	}
	return sort;
}

template<class T>
vector<int> DiGraph<T>::MarkNode(T name, vector<int> mark, vector<int>* node, vector<int>* sort) {
	int i = FindNode(name), temp;
	mark[i] = 1;
	(*node)[i] = 1;
	//cout << Node_[i].name_<<" ";											//按照深度优先的次序进行输出
	const int sum = Node_[i].LinkTo_.size();
	for (int j = 0; j<sum; j++) {
		temp = FindNode(Node_[i].LinkTo_[j]);
		if (mark[temp] == 0) mark = MarkNode(Node_[i].LinkTo_[j], mark, node, sort);
	}
	sort->insert(sort->begin(), i);
	return mark;
}

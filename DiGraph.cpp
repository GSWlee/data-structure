/*
*Author GSWlee@ccnu
*Date 2017-11-28
*Descriotion: DiGraph
*/

#include <iostream>
#include <string>
#include <vector>
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
		void DeleteLinkNode(string start,string end);
		void DeleteLinkNode(string name);
		void AddLinkNode(string strat,string end);
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
		int NodeLink(T name,int i=0);
		void AddNode(T name);
		void AddLink(T start,T end);
		void DeleteLink(T start,T end);
		void DeleteNode(T name);
		int FindNode(T name);
};

template <class T>
GraphNode<T>::GraphNode(T name) { name_ = name; }


/**
*	@brief 添加一个边
*	@start end 新建边的起点和终点
*/

template <class T>
void GraphNode<T>::AddLinkNode(T start,T end) {
	if(start==name_) {
		for(int i=0;i<LinkTo_.size();i++) {
			if(LinkTo_[i]==end)
				return;
		}
		LinkTo_.push_back(end);
	}
	if(end==name_) {
		for(int i=0;i<BeLinked_.size();i++) {
			if(BeLinked_[i]==end)
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
void GraphNode<T>::DeleteLinkNode(T start,T end) {
	int i=0;
	if(start==name_) {
		for(;i<LinkTo_.size();i++) {
			if(LinkTo_[i]==end) break;
		}
		if (i>=LinkTo_.size()) return;
		if (LinkTo_[i]==end) LinkTo_.erase(i);
	}
	i=0;
	if(end==name_) {
		for(;i<BeLinked_.size();i++) {
			if(BeLinked_[i]==end) break;
		}
		if (i>=BeLinked_.size()) return;
		if (BeLinked_[i]==end) BeLinked_.erase(i);
	}
}

template <class T>
void GraphNode<T>::DeleteLinkNode(T name) {
	int i=0;
	for(;i<LinkTo_.size();i++) {
		if(LinkTo_[i]==end) break;
	}
	if (i>=LinkTo_.size()) return;
	if (LinkTo_[i]==end) LinkTo_.erase(i);
	for(i=0;;i<BeLinked_.size();i++) {
		if(BeLinked_[i]==end) break;
	}
	if (i>=BeLinked_.size()) return;
	if (BeLinked_[i]==end) BeLinked_.erase(i);
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
	int first = -1, last = -1;
	while (i<Node_.size()) {
		if (Node_[i].name_ == start) first = i;
		if (Node_[i].name_ == end) last = i;
		i++;
	}
	if (start != -1 && last != -1) {
		Node_[first].AddLinkNode(start,end);
		Node_[last].AddLinkNode(start,end);
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
		Node_[first].DeleteLinkNode(start,end);
		Node_[last].DeleteLinkNode(start,end);
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
int DiGraph<T>::NodeLink(T name,int i=0) {
	int j = 0;
	while (j<Node_.size()) {
		if (Node_[j].name_ == name) break;
		j++;
	}
	if (Node_[j].name_ == name) {
		if(i==0)
			j=Node_[j].LinkTo_.size()+Node_[j].BeLinked_.size();
		else if(i==1)
			j=Node_[j].BeLinked_.size();
		else
			j=Node_[j].LinkTo_.size();
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
*	 @brief 返回目标节点的迭代器
*/

template <class T>
int DiGraph<T>::FindNode(T name) {
	int i = 0;
	for (; i<Node_.size(); i++) {
		if (Node_[i].name_ == name) return i;
	}
	return -1;
}

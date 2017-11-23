/*
*Author GSWlee@ccnu
*Date 2017-10-25
*Descriotion: UndiGraph
*/

#include <iostream>
#include <string>
#include <vector>
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

	if (i >=LinkNode_.size()) LinkNode_.push_back(name);
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
	if (Node_[i].name_ == name) i= Node_[i].LinkNode_.size();
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
	return sum/2;
}
int main() {
	UndiGraph<string> city("city");
	string temp;
	cin >> temp;
	while (temp != "quit") {
		city.AddNode(temp);
		cin >> temp;
	}
	string start, end;

	cin >> start >> end;
	while (start != "quit"&&end != "quit") {

		city.AddLink(start, end);

		cin >> start >> end;

	}


	for (int i = 0; i < city.Node_.size(); i++) {
		cout << city.Node_[i].name_ << endl;
		for (int j = 0; j < city.Node_[i].LinkNode_.size(); j++) {
			cout << city.Node_[i].LinkNode_[j] << " ";

		}
		cout << "\n";
		string ipo;
		ipo = city.Node_[i].name_;
		cout << city.NodeLink(ipo) << endl;
	}
	cout << city.SumLink() << endl;
	cout << city.SumNode() << endl;
	return 0;
}

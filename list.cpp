#include <iostream>
using namespace std;
template <class T>
class ListNode
{
	public:
		T  element;
		ListNode<T>* next;
};
template <class T>
class List
{
	public:
		ListNode<T>* header;
		int length=0;
		List();
		bool isempty();
		bool isend(ListNode<T>* m);
		ListNode<T>* find(T target);
		ListNode<T>* findper(T target);
		void add(T target);
		void add(T target, T pos);
		void show();
		void deleteelement(T target);
		ListNode<T>* back();
		~List();
};
template <class T>
List<T>::List()
{
	header = nullptr;
}
template <class T>
bool List<T>::isempty()
{
	return header==nullptr?true:false;
}
template <class T>
bool List<T>::isend(ListNode<T>* m)
{
	if (m->next== nullptr)
		return true;
		return false;
}
template <class T>
ListNode<T>* List<T>::find(T target)
{
	ListNode<T>* position;
	position = header;
	while (position->element != target && !isend(position))
		position = position->next;
	if (position->next == nullptr&&position->element != target)
		cout << "Not find." << endl;
	return position;
}
template <class T>
ListNode<T>* List<T>::findper(T target)
{
	ListNode<T>* position;
	position = header;
	while (position->next->element != target && !isend(position->next))
		position = position->next;
	if (position->next->next == nullptr&&position->next->element != target)
		cout << "Not find." << endl;
	return position;
}
template <class T>
void List<T>::add(T target)
{
	ListNode<T>* temp;
	temp = new ListNode<T>;
	temp->element = target;
	temp->next = header;
	header=temp;
	length++;
}
template <class T>
void List<T>::add(T target, T pos)
{
	ListNode<T>* temp, *position;
	position = find(pos);
	if (position->next == nullptr&&position->element!= pos)
		cout << "Cann't add." << endl;
	else
	{
		temp = new ListNode<T>;
		temp->element = target;
		temp->next = position->next;
		position->next = temp;
		length++;
	}
}
template <class T>
void List<T>::show()
{
	ListNode<T>* position;
	position = header;
	while (position->next != nullptr)
	{
		cout << position->element << ' ';
		position = position->next;
	}
	cout <<position->element<<endl;
}
template <class T>
void List<T>::deleteelement(T target)
{
	ListNode<T>* temp, *position;
	position = findper(target);
	if (position->next->next == nullptr&&position->next->element != target)
		cout << "Cann't delete." << endl;
	else
	{
		temp = position->next;
		position->next = position->next->next;
		delete temp;
	}
}
template <class T>
ListNode<T>* List<T>:: back()
{
	return header;
}
template <class T>
List<T>::~List()
{
	ListNode<T>* position, *temp;
	position = header->next;
	header->next = nullptr;
	while (position->next != nullptr)
	{
		temp = position;
		position = position->next;
		delete temp;
	}
}

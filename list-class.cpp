#include <iostream>
using namespace std;
class ListNode
{
public:
	int  element;
	ListNode* next;
};
class List
{
private:
	ListNode* header;
public:
	List()
	{
		header = nullptr;
	}
	bool isempty()
	{
		return header==nullptr?true:false;
	}
	bool isend(ListNode* m)
	{
		if (m->next== nullptr)
			return true;
		return false;
	}
	ListNode* find(int target)
	{
		ListNode* position;
		position = header;
		while (position->element != target && !isend(position))
			position = position->next;
		if (position->next == nullptr&&position->element != target)
			cout << "Not find." << endl;
		return position;
	}
	ListNode* findper(int target)
	{
		ListNode* position;
		position = header;
		while (position->next->element != target && !isend(position->next))
			position = position->next;
		if (position->next->next == nullptr&&position->next->element != target)
			cout << "Not find." << endl;
		return position;
	}
	void add(int target)
	{
		header = new ListNode;
		header->element = target;
		header->next = nullptr;
	}
	void add(int target, int pos)
	{
		ListNode* temp, *position;
		position = find(pos);
		if (position->next == nullptr&&position->element!= pos)
			cout << "Cann't add." << endl;
		else
		{
			temp = new ListNode;
			temp->element = target;
			temp->next = position->next;
			position->next = temp;
		}
	}
	void show()
	{
		ListNode* position;
		position = header;
		while (position->next != nullptr)
		{
			cout << position->element << ' ';
			position = position->next;
		}
		cout <<position->element<<endl;
	}
	void deleteelement(int target)
	{
		ListNode* temp, *position;
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
	~List()
	{
		ListNode* position, *temp;
		position = header->next;
		header->next = nullptr;
		while (position->next != nullptr)
		{
			temp = position;
			position = position->next;
			delete temp;
		}
	}
};
 

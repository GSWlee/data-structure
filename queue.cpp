#include <iostream>
using namespace std;
template <class T>
class Queue {
public:
	Queue(int max);
	bool IsEmpty();
	bool IsLess(int i, int j);
	bool IsFull();
	int Size();
	int Now();
	void Swap(int i, int j);
	void Swim(int k);
	void Sink(int k);
	void Insert(T ele);
	void DeleteMax();
	void Show();
	T Top();
	void Sort();
	~Queue();
private:
	int max_;
	int now_;
	T* element_;
};
template <class T>
Queue<T>::Queue(int max) {
	max_ = max;
	now_ = 0;
	element_ = new T[max_ + 1];
}
template <class T>
bool Queue<T>::IsEmpty() {
	return now == 0 ? true : false;
}
template <class T>
bool Queue<T>::IsLess(int i, int j) {
	return element_[i] <= element_[j] ? true : false;
}
template <class T>
bool Queue<T>::IsFull() {
	return now == max_ ? true : false;
}
template <class T>
int Queue<T>::Size() {
	return max_;
}
template <class T>
int Queue<T>::Now() {
	return now_;
}
template <class T>
void Queue<T>::Swap(int i, int j) {
	T temp = element_[i];
	element_[i] = element_[j];
	element_[j] = temp;
}
template <class T>
void Queue<T>::Swim(int k) {
	while (k>1 && IsLess(k / 2, k)) {
		Swap(k / 2, k);
		k = k / 2;
	}
}
template <class T>
void Queue<T>::Sink(int k) {
	while (2 * k <= now_) {
		int j = 2 * k;
		if (j<now_&&IsLess(j, j + 1)) j++;
		if (!IsLess(k, j)) break;
		Swap(k, j);
		k = j;
	}
}
template <class T>
void Queue<T>::Insert(T element) {
	if (++now_>max_) {
		cout << "is full.";
		now_--;
		return;
	}
	element_[now_] = element;
	Swim(now_);
}
template <class T>
void Queue<T>::DeleteMax() {
	Swap(1, now_--);
	element_[now_ + 1] = nullptr;
	Sink(1);
}
template <class T>
void Queue<T>::Show() {
	for (int i = 1; i <= now_; i++)
		cout << element_[i] << " ";
}
template <class T>
T Queue<T>::Top() {
	return element_[1];
}
template <class T>
void Queue<T>::Sort() {
	int N = now_;
	while (now_ > 1) {
		Swap(1, now_--);
		Sink(1);
	}
	now_ = N;
}
template <class T>
Queue<T>::~Queue() {
	delete[] element_;
}

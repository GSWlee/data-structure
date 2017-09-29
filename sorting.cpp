template <class T>
bool ifless(T a, T b)								//判断最小值
{
	return a<b ? true : false;
}
template <class T>
void Swap(T&a, T&b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}
template <class T>
T* selectsort(T* a, int length)					//选择排序
{
	for (int i = 0; i<length; i++)
	{
		int min = i;
		for (int j = i + 1; j<length; j++)
		{
			if (ifless(a[j], a[min]))
				min = j;
		}
		Swap(a[i], a[min]);
	}
	return a;
}
template <class T>
T* insertsort(T* a, int length)					//插入排序
{
	for (int i = 1; i<length; i++)
	{
		for (int j = i; j>0 && ifless(a[j], a[j - 1]); j--)
			Swap(a[j], a[j - 1]);
	}
	return a;
}
template <class T>
T* hillsort(T* a, int length)						//hill排序
{
	int h = 1;
	while (h<length / 3)
		h = 3 * h + 1;
	while (h >= 1)
	{
		for (int i = h; i<length; i++)
			for (int j = i; j >= h&&ifless(a[j], a[j - h]); j -= h)
				Swap(a[j], a[j - h]);
		h = h / 3;
	}
	return a;
}
template <class T>								   //归并排序，由于c++和java差异的问题造成的内存开销巨大问题正在解决
void merge(T* a, int s, int t, int mid,int lo,int hi)
{
	T* aue = new int[hi - lo+1];
	int i = s, j = mid + 1;
	for (int k = s; k<=t; k++)
		aue[k] = a[k];
	for (int k = s; k<=t; k++)
	{
		if (i>mid)   					a[k] = aue[j++];
		else if (j > t)   				a[k] = aue[i++];
		else if (ifless(aue[i], aue[j]))  a[k] = aue[i++];
		else							a[k] = aue[j++];
	}
}
template <class T>
void mergesort(T* a, int s, int t,int lo,int hi)
{
	if (t <= s)           return;
	int mid = (s + t) / 2;
	mergesort(a, s, mid,lo,hi);
	mergesort(a, mid + 1, t,lo,hi);
	merge(a, s, t, mid, lo,hi);
}

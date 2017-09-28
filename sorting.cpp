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

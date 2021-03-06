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
T findmin(T a,T b)
{
	return a<b?a:b;
}
template <class T>
void selectsort(T* a, int length)					//选择排序
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
}
template <class T>
void insertsort(T* a, int length)					//插入排序
{
	for (int i = 1; i<length; i++)
	{
		for (int j = i; j>0 && ifless(a[j], a[j - 1]); j--)
			Swap(a[j], a[j - 1]);
	}
}
template <class T>
void hillsort(T* a, int length)						//hill排序
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
}
template <class T>								   //归并排序
void merge(T* a, int s, int t, int mid,int length)
{
	T* aue = new int[length];
	int i = s, j = mid + 1;
	for (int k = s; k<=t; k++)
		aue[k] = a[k];
	for (int k = s; k<=t; k++)
	{
		if (i>mid)   					  a[k] = aue[j++];
		else if (j > t)   				  a[k] = aue[i++];
		else if (ifless(aue[i], aue[j]))  a[k] = aue[i++];
		else							  a[k] = aue[j++];
	}
}
template <class T>								 //自顶而下的归并
void mergesort(T* a, int s, int t,int length)
{
	if(t<=s) return ;
	/*if ((t-s)<15)								//改进避免因为特别小的数组调用递归
	{											//增加复杂度，15只是随便设的，具体
		selectsort(a,t-s+1);					//具体数值跟系统有关一般5到15都可以
		return ;
	}*/
	int mid = (s + t) / 2;
	mergesort(a, s, mid,length);
	mergesort(a, mid + 1, t,length);
	if(a[mid]<=a[mid+1])     return ;
	merge(a, s, t, mid, lo,hi);
}
template <class T>								 //自底而上的归并
void merge(T*a, T*aue, int s, int mid, int t)
{
	int i = s, j = mid + 1;
	for (int k = s; k <= t; k++)
		aue[k] = a[k];
	for (int k = s; k <= t; k++)
	{
		if (i>mid)   					  a[k] = aue[j++];
		else if (j > t)   				  a[k] = aue[i++];
		else if (ifless(aue[i], aue[j]))  a[k] = aue[i++];
		else							  a[k] = aue[j++];
	}
}
template <class T>
void mergesort(T*a, int length)
{
	T* aue = new T[length];
	for (int size = 1; size<length; size += size)
		for (int lo = 0; lo<length - size; lo += size+size)
			merge(a, aue, lo, lo + size - 1, findmin(lo + size + size - 1, length- 1));
}
template <class T>								//快速排序（普通版）
int partiton(T*a,int lo,int hi)
{
	int i=lo,j=hi+1;
	T v=a[lo];
	while(true)
	{
		while(ifless(a[++i],v)) if(i==(hi)) break;
		while(ifless(v,a[--j])) if(j==lo) break;
		if(i>=j)break;
		Swap(a[i],a[j]);
	}
	Swap(a[lo],a[j]);
	return j;
}
template <class T>
void quicksort(T* a,int lo,int hi)
{
	if(lo>=hi) return ;
	int j=partiton(a,lo,hi);
	quicksort(a,lo,j-1);
	quicksort(a,j+1,hi);
}
template <class T>								//Dijkstra的三切分快排：解决重复元素
void quicksort_3way(T*a,int lo,int hi)			//过多的数据排序问题。不过在重复元素
{												//比较少时，使用了比普通快排更多的
	if(lo>=hi)		return;						//交换并不理想
	int i=lo,j=lo+1,k=hi;
	T v=a[lo];
	while(j<=k)
	{
		if(a[j]<v)        Swap(a[i++],a[j++]);
		else if(a[j]>v)   Swap(a[j],a[k--]);
		else 			  j++;
	}
	quicksort_3way(a,lo,i-1);
	quicksort_3way(a,j+1,hi);
}

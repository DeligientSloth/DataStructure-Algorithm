// QuickSort.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
template<class T>
int Partition(vector<T>& a, int left, int right)
{
	T pivot = a[left];//选择一个主元
	int i = left, j = right;//left，right在下一次递归中可能会用到，用i和j代替变化
	while (i<j)
	{
		while (i < j&&a[j]>=pivot)
			--j;//找到第一个小于pivot的数,因为j是先变化的，所以后面与pivot与i进行交换
		while (i < j&&a[i] <= pivot)
			++i;//找到第一个大于pivot的数
		//交换他们
		if (i < j)//要是此时i>j就没有意义了，i管小于pivot的部分，j管大于pivot的部分
		{
			T t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	//i与主元交换，为什么不是j，因为此时j位置的元素大小肯定比pivot大
	a[left] = a[i];
	a[i] = pivot;//主元的位置
	return i;
}
template<class T>
void QuickSort(vector<T>& a, int left, int right)
{
	if (left >= right) return;
	/*划分操作*/
	int i = Partition(a, left, right);
	QuickSort(a, left, i - 1);
	QuickSort(a, i + 1, right);

	stack<int> s;
	s.push(left);
	s.push(right);
	int l, r;//左右元素
	while (!s.empty())
	{
		r = s.top();
		l = s.top();
		s.pop();
		s.pop();
		if (l >= r)  continue;//相当于递归函数里面的退出，因为这里面的while循环相当于一次递归
		int i = Partition(a, l, r);
		s.push(i + 1);
		s.push(r);
		s.push(left);
		s.push(i - 1);
	}
}
template<class T>
void QuickSort_NonRecursive(vector<T>& a, int left, int right)
{
	if (left >= right) return;
	/*划分操作*/
	int i = Partition(a, left, right);
	QuickSort(a, left, i - 1);
	QuickSort(a, i + 1, right);
}
template<class T>
void swap(vector<T>& a, int x, int y)
{
	T temp = a[x];
	a[x] = a[y];
	a[y] = temp;
}
template<class T>
void ThreeMidPoint(vector<T>& a, int left, int right)
{
	int mid = (left + right) >> 1;
	cout << mid << endl;
	if (a[left] > a[mid]) swap(a,left,mid);
	if (a[left] > a[right])  swap(a, left, right);
	if (a[mid] > a[right]) swap(a, mid, right);
	swap(a, mid, right - 1);
}
template<class T>
void QuickSort_ThreeMidPoint(vector<T>& a, int left, int right)
{
	cout << left << " " << right << endl;
	if (left>=right) return;
	if (right-left==1)
	{
		if (a[left] > a[right]) swap(a, left, right);
		return;
	}
	if (right-left==2)
	{
		if (a[left] > a[left+1]) swap(a, left, left+1);
		if (a[left] > a[right])  swap(a, left, right);
		if (a[left+1] > a[right]) swap(a, left+1, right);
		return;
	}

	ThreeMidPoint(a, left, right);
	T pivot = a[right - 1];//主元

	int l = left + 1, r = right - 2;
	while (l < r)
	{
		while (l<r&&a[l] <= pivot) l++;
		while (l<r&&a[r] >= pivot) r--;
		if (l < r) swap(a, l, r);
	}
	if(l<right)
	   swap(a, l, right - 1);
	printVector(a);
	QuickSort_ThreeMidPoint(a, left, l - 1);
	QuickSort_ThreeMidPoint(a, l + 1, right);
}
template<class T>
void printVector(vector<T> a) {
	for (vector<T>::iterator iter = a.begin(); iter != a.end(); ++iter)
		cout << *iter <<" ";
	cout << endl;
}
int main()
{
	vector<int> a = { 6,1,2,7,9,3,4,5,10,8 };
	//Partition(a, 0, a.size()-1);
	//printVector(a);
	//QuickSort(a,0,a.size()-1);
	//printVector(a);
	//vector<int> a = { 4,3,2,1 };
	//QuickSort(a, 0, a.size() - 1);
	//QuickSort_NonRecursive(a, 0, a.size() - 1);
	//ThreeMidPoint(a, 0, a.size() - 1);
	QuickSort_ThreeMidPoint(a, 0, a.size() - 1);
	printVector(a);
    return 0;
}


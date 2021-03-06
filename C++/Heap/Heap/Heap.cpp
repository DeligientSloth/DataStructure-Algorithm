// Heap.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

template<class T>
struct Less
{
	const bool operator()(T& left, T& right) const
	{
		return left < right;
	}
};
template<class T>
struct Greater
{
	const bool operator()(T& left, T& right) const
	{
		return left > right;
	}
};

template<class T>
void swap(vector<T>& a,int x, int y)
{
	T t;
	t=a[x]; a[x] = a[y]; a[y] = t;
}

/*从s开始向下调整*/
/*对从s->m的vector进行调整*/
template<class T=int,class T_compare>
void HeadAdjust(vector<T>& a,int begin,int end,T_compare com=Less<T>())
{
	int largest=begin;
	//for (int j = 2 *begin; j <= a[0];)
	while(2*begin<=end)
	{
		largest =begin;//默认最大为根节点
		int left = 2 *begin;//左孩子
		if (com(a[begin],a[left]))//比较左孩子
			largest = left;
		if (left + 1 <= end && com(a[largest],a[left + 1])) largest = left + 1;//比较右孩子
		//最小的节点编号不是自己
		if (largest !=begin) {
			swap(a, largest,begin);
			begin = largest;//交换过后，可能不满足最大堆
		}
		else break;//没有发生交换
	}
}
template<class T = int>
void HeadAdjustRecursion(vector<T>& a, int begin,int end)
{
	int left = 2 *begin;
	int right = 2 *begin + 1;
	int largest =begin;
	if (left >= end) return;
	if (a[largest] < a[left]) largest = left;
	if (right <= end && a[right] > a[largest]) largest = right;
	if (largest ==begin) return;
	swap(a, largest,begin);
	HeadAdjustRecursion(a, largest,m);
}

template<class T,class T_compare>
void makeHeap(vector<T>& a,T_compare com)
{
	a[0] = a.size() - 1;
	for (int i = a[0] / 2; i >= 1; i--)
		HeadAdjust<T,T_compare>(a,i,a[0], com);
}
template<class T>
void makeHeapRecursion(vector<T>& a)
{
	a[0] = a.size() - 1;
	for (int i = a[0] / 2; i >= 1; i--)
		HeadAdjustRecursion(a, i,a[0]);
}
/*对从m->s的元素进行调整*/
template<class T,class T_compare>
void HeadAdjustionUp(vector<T>& a, int begin,int end,T_compare com)
{
	/*if (end == begin) return;
	int parent = end/2;
	if (a[parent] >= a[end]) return;//不需要调整
	swap(a, end, parent);
	HeadAdjustionUp(a,begin ,parent);*/

	while (begin != end)
	{
		int parent = end / 2;
		if (!com(a[parent],a[end])) break;
		swap(a, end, parent);
		end = parent;
	}
}
template<class T,class T_compare>
void push_Heap(vector<T>& a,T_compare com)
{
	a[0] = a.size() - 1;
	HeadAdjustionUp(a, 1,a[0],com);
}
template<class T,class T_compare>
void pop_Heap(vector<T>& a,int begin,int end,T_compare com)
{
	swap(a, begin,end);//第一个元素和最后一个元素交换
	//对1到a[0]-1范围内的数据进行调整
	HeadAdjust(a, begin, end-1, com);
	//a.pop_back();//弹出最后一个元素，原来第一个元素
	//a[0]--;
}
template<class T,class T_compare>
void Heap_Sort(vector<T> &a, T_compare com)
{
	int begin = 1, end = a.size()-1;
	for(int begin = 1, end = a.size() - 1;end>begin;end--)
	     pop_Heap(a, begin, end, com);
}
template<class T>
void PrintVector(vector<T> v,int s)
{
	for (size_t i = s; i < v.size(); i++) cout << v[i] << " ";
	cout << endl;
}
int main()
{
	vector<int> a = { 0,50,10,90,30,70,40,80,60,20 };
	a[0] = a.size()-1;
	makeHeap<int, Less<int>>(a, Less<int>());
	cout << "**********自己makeheap函数作用的结果********"<< endl;
	PrintVector(a,1);
	cout << "**********************************************" << endl;

	a.push_back(100);
	push_Heap(a,Less<int>());
	cout << "**********自己pushheap函数作用的结果********" << endl;
	PrintVector(a,1);
	cout << "**********************************************" << endl;

	pop_Heap(a,1,a.size()-1, Less<int>());
	a.pop_back();
	cout << "**********自己popheap函数作用的结果********" << endl;
	PrintVector(a,1);
	cout << "**********************************************" << endl;

	Heap_Sort(a, Less<int>());
	cout << "**********堆排序结果********" << endl;
	PrintVector(a, 1);
	cout << "**********************************************" << endl;

	vector<int> b = { 50,10,90,30,70,40,80,60,20 };
	make_heap(b.begin(), b.end());
	cout << "**********标准makeheap函数作用的结果********" << endl;
	PrintVector(b,0);
	cout << "**********************************************" << endl;

	b.push_back(100);
	push_heap(b.begin(), b.end());
	cout << "**********标准pushheap函数作用的结果********" << endl;
	PrintVector(b,0);
	cout << "**********************************************" << endl;

    return 0;
}


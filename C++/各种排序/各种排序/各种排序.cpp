// 各种排序.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
using namespace std;


void showVector(const vector<int> & vec) {
	for (int item : vec) cout << item << " ";
	cout << endl;
}
/*
quciksort: 平均最好都是logn ，最坏是n^2
第一个快速排序
写两种划分方法
1、两边向中间靠 
   (<=)--待划分到两边--(>=)
   两个指针分别向两边靠拢，直到待划分集合为空集或者只有一个元素，无法划分，此时带划分元素小于等于pivot
   前提是必须是pivot所在的反方向指针先移动
*/

int partition1(vector<int>& arr, int low, int high) {
	if (low == high) return low;
	int pivot = arr[low];
	while (low < high) {//low,high分别指向待划分集合的两头
		while (low < high&&arr[high] >= pivot) high--;
		arr[low] = arr[high];//arr[low]处的pivot被替换掉了，数组中没有pivot
		while (low < high&&arr[low] <= pivot) low++;
		arr[high] = arr[low];//每次都是两个部分的头元素交换
	}
	arr[low] = pivot;
	return low;
}
int partition2(vector<int>& arr, int low, int high) {
	if (low == high) return low;
	int i = low, j = high,pivot=arr[low];
	while (i<j) {
		while (i < j&&arr[j] >= pivot) j--;
		while (i < j&&arr[i] <= pivot) i++;
		if (i < j) swap(arr[i], arr[j]);
	}
	arr[low] = arr[i];
	arr[i] = pivot;
	return i;
}
/*
快速排序划分3：<=,>,待划分集合
需要指针i，j，i指向已经划分好的小于等于集合，j指向待划分集合，i和j之间是大于集合
j指针移动，如果元素大于主元，j指针后移就可以扩大大于集合
如果小于等于主元，就将j指针元素与>集合首元素交换，这样，大于集合不变，小于集合加一个！
*/
int partition3(vector<int>& arr, int low, int high) {
	if (low == high) return low;
	int pivot = arr[high];//选择最后一个作为主元
	int i = low - 1, j = low;//i和j分别指向<=末尾元素和待划分集合首元素
	for (j = low; j <= high - 1; j++) {
		if (arr[j] <= pivot) swap(arr[++i], arr[j]);//包含了++i==j的情况，此时>集合为空集
	}
	arr[high] = arr[i + 1], arr[i + 1] = pivot;
	return i + 1;
}
vector<int> QuickSort(vector<int>& arr, int low, int high) {
	if (low >= high) return arr;
	int p = partition3(arr, low, high);
	QuickSort(arr, low, p - 1);
	QuickSort(arr, p + 1, high);
	return arr;
}
/*
插入排序
*/
/*
归并排序
*/

/*
堆排序
*/
#define lchild(x) 1+(x<<1)
#define rchild(x) 2+(x<<1)
#define parent(x) (x-1)>>1

void HeapAdjustDown(vector<int>& heap,int start,int end) {//向下调整
	if (start >= end) return;
	//除了start，都满足堆的特性
	int nchild,temp=heap[start],k;
	for (k = start; (nchild=lchild(k)) <= end;) {
		if (nchild + 1 <= end&&heap[nchild + 1] > heap[nchild]) nchild++;
		if (heap[nchild] > temp) {
			heap[k] = heap[nchild];
			//heap[nchild] = temp;
			k = nchild;
		}
		else break;
	}
	heap[k] = temp;//两个循环退出条件。1、k为叶子节点。2、k的最大孩子比k小，退出时k没变，还是那个父亲，temp直接接入
}
void HeapAdjustUp(vector<int>& heap,const int& start,const int& end) {//向上调整
	//除了end以外都满足堆得特性
	int nParent,temp=heap[end],k;
	for (k = end; (nParent=parent(k))>= start; ) {
		if (temp > heap[nParent]) {
			//swap(heap[k], heap[nParent]);
			heap[k] = heap[nParent];
			k = nParent;
		}
		else break;
	}
	heap[k] = temp;
}
void makeHeap(vector<int>& heap,int start,int end) {//从下到上，从右到左调整
	//parnet(end)是最后一个非叶子节点
	for (int k = parent(end);k>=start;k--) {
		HeapAdjustDown(heap, k, end);
	}
}
void pushHeap(vector<int>& heap, int data) {
	heap.push_back(data);
	HeapAdjustUp(heap, 0, heap.size() - 1);
}
void popHeap(vector<int>& heap, int start, int end) {
	swap(heap[start], heap[end]);
	HeapAdjustDown(heap, start, end - 1);
}
void HeapSort(vector<int>& heap,int start,int end) {
	for (int k = end; k >start; k--) {
		//swap(heap[start], heap[k]);
		//HeapAdjustDown(heap, start, k-1);
		popHeap(heap, start, k);
	}
}


/*
Bubble sort冒泡排序
*/

void BubbleSort1(vector<int>& vec) {
	int len = vec.size();
	bool flag = true;
	for (int k = 0; k <=len-2&&flag; k++) {
		flag = false;
		for (int i = len - 2; i >= k; i--) {
			if (vec[i + 1] < vec[i]) {
				swap(vec[i + 1], vec[i]); flag = true;
			}
		}
	}
}
void BubbleSort2(vector<int>& vec) {
	int len = vec.size();
	bool flag = true;
	for (int k = len-2; k >= 0&&flag; k--) {
		flag = false;
		for (int i = 0; i <= k; i++) {
			if (vec[i] > vec[i + 1]) {
				flag = true;
				swap(vec[i + 1], vec[i]);
			}
		}
	}
}
/*
shell 希尔排序 递减增量法
*/


int main()
{
	/*vector<int> arr = {5,1,9,3,7,4,8,6,2};
	//cout << partition3(arr, 0, arr.size() - 1) << endl;
	QuickSort(arr,0, arr.size()-1);
	showVector(arr);*/
	//int m;
	//cout << lchild(1) << " " << rchild(1)<<" "<<(parent(3))<<" "<<((m=100)>99)<<endl;
	/*vector<int> vec = { 5,1,9,3,7,4,8,6,2 };
	BubbleSort1(vec);
	showVector(vec);*/
	vector<int> heap = { 50,10,90,30,70,40,80,60,20 };
	makeHeap(heap,0,heap.size()-1);
	showVector(heap);
	HeapSort(heap, 0, heap.size() - 1);
	//pushHeap(heap, 76);
	showVector(heap);
    return 0;
}


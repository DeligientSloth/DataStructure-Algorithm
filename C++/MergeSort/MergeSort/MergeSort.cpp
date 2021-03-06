// MergeSort.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
/*
两个有序的子序列(相当于输入序列)
left->mid
mid+1->right
*/
template<class T>
void Merge(T *arr, int left, int right, int mid)
{
	T *temp = new T[right - left + 1];
	size_t i = left, j = mid + 1, k = 0;
	while (i <= mid&&j <= right)
		temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
	while (i <= mid) temp[k++] = arr[i++];
	while (j <= right) temp[k++] = arr[j++];
	//copy temp to arr
	for (k = 0, i = left; i <= right; i++,k++) arr[i] = temp[k];
	delete[] temp;
}
template<class T>
void MergeSort(T *arr,int left,int right)
{
	if (left < right)
	{
		int mid = (left + right)/2;
		cout<<"begin to left function: "<< left << " " << mid <<endl;
		MergeSort(arr, left, mid);
		cout << "begin to right function: " << mid+1 << " " << right << endl;
		MergeSort(arr, mid+1, right);//!!!!!
		cout << "begin to merge: " << left << " " << mid << " " << right<<endl;
		Merge(arr, left,right,mid);
	}
}
//将长度为s的子序列合并
template<class T>
void Merge_Pass(T *arr, int s, int len)
{
	int i = 0;
	int last = len - 2 * s + 1;
	while (i < last)
	{
		Merge(arr, i, i + 2 * s - 1, i + s - 1);
		i += 2 * s;
	}
	if (i < len - s + 1)
	{
		cout << "合并" << i << "->" << len << "之间的数" << endl;
		Merge(arr, i, len, i + s - 1);
	}
	//剩下一个网格没有排序
	//Merge(arr, i, len, (i + len) >> 1);
}
template<class T>
void Merge_Sort_Recurse(int *arr, int len)
{
	int s = 1;
	while (s <= len)
	{
		Merge_Pass(arr, s, len);
		s = s * 2;
	}
}
int main()
{
	int A[7] = { 1,9,8,3,5,6 };
	//Merge<int>(A, 0,5,2);
	//MergeSort<int>(A, 0, 5);
	Merge_Sort_Recurse<int> (A, 5);
	for (size_t i = 0; i < 6; i++) cout << A[i] << " ";
	cout << endl;
    return 0;
}

template<class T>
void Merge1(T *arr, int left, int mid, int right)
{
	T *leftArr = new T[mid - left + 1];
	T *rightArr = new T[right - mid];//相当于temp
	size_t i, j, k = 0;
	//cout << "haha" << endl;
	for (i = left; i <= mid; ++i) leftArr[i] = arr[i];
	for (j = mid + 1; j <= right; ++j) rightArr[j] = arr[j];
	//cout << "haha" << endl;
	i = left;
	j = mid + 1;
	while (i <= mid&&j <= right)
	{
		if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
		else arr[k++] = rightArr[j++];
	}
	//cout << "haha" << endl;
	for (; i <= mid; ++i) arr[k++] = leftArr[i];
	for (; j <= right; ++j) arr[k++] = rightArr[j];
	//delete [] leftArr;
	//delete [] rightArr;
}

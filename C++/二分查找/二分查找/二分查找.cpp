// 二分查找.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<iostream>
#include<vector>
using namespace std;
/*
1、二分查找变种一：查找大于target的最小数
如果 num[mid]>target：mid-1可能小于target，所以查找范围只能缩小为：low->mid;
如果num[mid]==target：mid+1应该大于等于target，反正最后结果肯定不是mid，查找范围：mid+1->high
如果num[mid]<target: 查找范围变为：[mid+1,high]
当只有最后一个数的时候，会陷入死循环，所以当low==high退出循环
*/
int minIndexGreatTarget(vector<int>& nums, int target) {
	int low = 0, high = nums.size() - 1;
	while (low<high) {//只有一个元素则退出循环
		int mid = low + ((high - low) >> 1);
		if (nums[mid] > target) high = mid;
		else low = mid + 1;
	}
	return nums[high] > target ? high : -1;
}
/*
2、二分查找之：查找小于target的最大数
num[mid]>target: num[mid-1]必定小于或者等于target，正是我们要找的范围，反正num[mid]肯定不和要求，high=mid-1
num[mid]==target:num[mid-1]必定小于或者等于target，正是我们要找的范围，反正num[mid]肯定不和要求，high=mid-1
num[mid]<target:num[mid+1]可能大于等于target，不要乱动，low=mid;
如果只有两个元素进入循环，可能导致死循环，此时low==mid，减少长度肯能为0
*/
int maxIndexLessTarget(vector<int>& nums, int target) {
	int low = 0, high = nums.size() - 1;
	while (low<high-1) {//有两个元素，退出循环
		int mid = low + ((high-low) >> 1);
		if (nums[mid] < target) low = mid;
		else high = mid - 1;
	}
	if (nums[high] < target) return high;
	if (nums[low] < target) return low;
	return -1;
}
int main()
{
	vector<int> arr = { 1,3,3 };
	//cout << minIndexGreatTarget(arr, 2)<<endl;
	cout << maxIndexLessTarget(arr, 0) << endl;
    return 0;
}


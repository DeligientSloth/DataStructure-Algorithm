// 桶排序.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	vector<int> vec = { 10,5,7,19,3 };
	int Max = *max_element(vec.begin(),vec.end());
	int Min = *min_element(vec.begin(), vec.end());
	double delta = double(Max - Min) / (vec.size() - 1);
	for (size_t i = 0; i < vec.size(); i++)
	{
		int index = (vec[i] - Min) / delta;
		cout << index << endl;
	}
    return 0;
}


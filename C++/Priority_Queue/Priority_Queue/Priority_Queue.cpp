// Priority_Queue.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<algorithm>
#include<vector>
#include<iostream>
#include<queue>
using namespace std;

template<class T=void>
struct greater
{
	const bool operator()(const T& left, const T& right) const
	{
		return left > right;
	}
};
template<class T = void>
struct Less
{
	const bool operator()(const T& left, const T& right) const
	{
		return left < right;
	}
};
template<class T=int,class T_comare=greater<T>>
class Priority_Queue
{
private:
	vector<T> data;
public:
	Priority_Queue(vector<T> v) :data(v) { make_heap(data.begin(), data.end(), T_comare()); }
	void insert(const T& t){
		data.push_back(t);
		push_heap(data.begin(), data.end(),T_comare());
	}
	void pop() {
		pop_heap(data.begin(), data.end(), T_comare());
		data.pop_back();
	}
	const T& top() const { return data.front(); }
	bool empty() { return data.empty(); }
};
int funn(int a,int b) {
	return a + b;
}
void fun(const int& a,const int& b,int (*fun1)(int,int))
{
	cout << (*fun1)(a, b) << endl;
}
int main()
{
	vector<int> v{ 6, 1, 2, 5, 3, 4 };
	Priority_Queue<> Q(v);
	/*Q.insert(3);
	Q.insert(5);
	Q.insert(2);
	Q.insert(4);*/
	while (!Q.empty()) {
		cout << Q.top() << endl;
		Q.pop();
	}
	return 0;
}


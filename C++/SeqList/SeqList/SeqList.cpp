// SeqList.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

template<class T>
class ablist
{
protected:
	length;
public:
	int getLength() { return length; }
	virtual T Get(int index);
	virtual bool Set(T x, int index) = 0;
	virtual void setEmpty() = 0;
	virtual bool Insert(T value, int index) = 0;
	virtual T remove(int index) = 0;
	virtual T removeValue(T value) = 0;
};
template<class T>
class SeqList :public ablist<T>
{

};
int main()
{
    return 0;
}


// KMP.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
using namespace std;

vector<int> get_next(char* p) {//p表示模式串
	int len = strlen(p);
	vector<int> next(len,-1);//-1的位置是通配符，next[0]必须为-1
	int i=0, j=-1;//i表示“主串”指针，也是后缀指针，j表示模式串指针，也是前缀指针，其实前缀，后缀都是模式串一部分
	/*
	0的后缀为通配字符单元-1，前缀指向它自己
	这个过程可以看做循环求出每一个前缀字符的next值的过程，不断用j指向的后缀字符跟他匹配
	next[i]=j，j可以理解为j-1前面的字符都是跟后缀匹配的：T[0->j-1]=T[i-j->i-1]
	如果T[i]==T[j]，则next[i+1]=j+1，或者j==-1是通配，这个时候也会有这种效果
	*/
	while (i < len-1) {//循环求出第i+1个指针的next数值，通过比较i与前缀通配情况求得
		if (j == -1 || p[i] == p[j]) next[++i] = ++j;//求出下一个主串指针的next[i+1]=j+1
		else j = next[j];//j值回溯，直到求出i+1的next值
	}
	return next;
}
/*
 KMP第二天，已知next[i]求next[i+1]:
    next[i+1]=next[i]+1 if p[i]==p[next[i]] else next[i+1]=next[next[....next[i]....]] until 出现匹配
	画个图就看出来了
	总就有一个字符与p[i]匹配，得到next[i+1]=k，但这个替换的k必须与p[i+1]不相等
	因为这是由于p[i+1]不行才让他的替补登场，如果替补跟他一样弱小，那还得了
	一样弱小就让让替补的替补登场，别鸡蛋碰石头
*/
vector<int> get_nextval(char*p) {
	int len = strlen(p);
	vector<int> nextval(len, -1);//next[0]=-1;
	int i = 0, j = -1;//i指向后缀中待匹配元素，j指向前缀中带比较元素，0->j-1==i-j->i-1，反正i和j后面的元素匹配的
	while (i < len - 1) {//已知next[i]求next[i+1]注意循环结束条件
		if (j == -1 || p[i] == p[j]) {
			++i; ++j;
			nextval[i] = p[i] != p[j] ? j : nextval[j];//i处元素与替补的j处元素不相等
		}
		else
			j = nextval[j];
	}
	return nextval;
}
int KMP(char* S, char* T,vector<int> next) {//S表示主串，T表示模式串
	int len_s = strlen(S), len_t = strlen(T);
	int i = 0, j = 0;
	while (i < len_s&&j < len_t) {
		if (j == -1 || S[i] == T[j]) {//j=-1通配，比较下一个
			++i; ++j;//比较下一个字符
		}
		else j = next[j];//i不动
	}
	if (j == len_t) cout << "匹配成功" << endl;
	return i-j;
}
vector<int> findAllSubString(char* S, char* T) {
	vector<int> next = get_next(T),ret;
	int i = 0, j = 0,len_s=strlen(S),len_t=strlen(T);
	while (i < len_s) {
		if (j == -1 || S[i] == T[j]) {
			++i; ++j;
			if (j == len_t) {
				ret.push_back(i - j);
				j = 0;
			}
		}
		else j = next[j];
	}
	return ret;
}
int main()
{
	/*char* p = "df";
	vector<int> next = get_next(p);
	for (int item : next) cout << item << " ";
	cout << endl;
	char* s = "abcgoogghdf";
	cout << KMP(s, p, next) << endl;
	char *ss = "aaaa";
	vector<int> allsub = findAllSubString(ss, "a");
	for (int item : allsub) cout << item << " ";
	cout << endl;*/
	char*p = "00001";
	vector<int> nextval = get_nextval(p);
	for (int item : nextval) cout << item << " ";
    return 0;
}


// 0-1Knapsack.cpp: 定义控制台应用程序的入口点。
//0-1背包实战
/*
假设山洞里共有a,b,c,d ,e这5件宝物（不是5种宝物），它们的重量分别是2,2,6,5,4，
它们的价值分别是6,3,5,4,6，现在给你个承重为10的背包, 怎么装背包，可以才能带走最多的财富。
*/
#include "stdafx.h"
#include<iostream>
#define Max(x,y) x>=y? x:y
using namespace std;
const int N = 5;
const int W = 10;//背包容量
//int w[N + 1] = {0,2,2,6,5,4 };
//int v[N + 1] = {0,6,3,5,4,6 };
int w[N + 1] = {0,3,5,1,9,7};
int v[N + 1] = {0,11,28,6,49,35};
int f[N + 1][W + 1];//最大价值的二维数组，返回f[N][W]
int dp[W+1];
int x[N + 1] = {0};

int KnapSack()
{
	for (int j = 1; j <= W; j++) f[0][j] = 0;//没有物品可供选择的时候，背包价值为0
	for (int i = 1; i <= N; i++) {
		f[i][0] = 0;//背包容量为0的时候，价值为0
		for (int j = 1; j <= W; j++) {
			if (w[i] > j) f[i][j] = f[i - 1][j];//放不下
			else f[i][j] = Max(f[i - 1][j - w[i]] + v[i], f[i - 1][j]);
		}
	}
	return f[N][W];
}
int KnapSack_Input()
{
	int w, v;
	for (int i = 1; i <= N; i++) {
		f[i][0] = 0;//背包容量为0的时候
		cin >> w >> v;
		for (int j = 1; j <= W; j++) {
			f[i][j] = (i == 1)? 0:f[i - 1][j];//决策边界考虑
			if (j >= w) f[i][j]=Max(f[i-1][j - w] + v,f[i][j]);
		}
	}
	return f[N][W];
}
/*使用滚动数组实现*/
int KnapSack_oneDimension()
{
	memset(dp, 0, sizeof(dp));//阶段0，初始化为0
	for (int i = 1; i <= N; i++) {
		for (int j = W; j >= 1; j--)//逆序，保证dp[i-1][j-w[i]先于dp[i][j-w[i]]被计算
		{
			if (j >= w[i]) dp[j] = Max(dp[j], dp[j - w[i]] + v[i]);
			cout << dp[j] << " ";
		}
		cout << endl;
	}
	return dp[W];
}
//重量逆序的对比程序
int KnapSack_1()
{
	for (int j = 1; j <= W; j++) f[0][j] = 0;//没有物品可供选择的时候，背包价值为0
	for (int i = 1; i <= N; i++) {
		f[i][0] = 0;//背包容量为0的时候，价值为0
		for (int j = W; j >= 1; j--) {
			if (w[i] > j) f[i][j] = f[i - 1][j];//放不下
			else f[i][j] = Max(f[i - 1][j - w[i]] + v[i], f[i - 1][j]);
			cout << f[i][j] << " ";
		}
		cout << endl;
	}
	return f[N][W];
}
void printSolution()
{
	int j = W;
	for (int i = N; i >= 1; i--) {
		if (f[i][j] > f[i - 1][j]) {
			x[i] = 1;
			j -= w[i];
		}
	}
	for (int i = 1; i <= N; i++) cout << x[i] << " ";
}
int main()
{
	cout << KnapSack_oneDimension() << endl;
	cout << "**************************************" << endl;
	cout << KnapSack_1() << endl;
    return 0;
}


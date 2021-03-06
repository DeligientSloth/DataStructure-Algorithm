// Dijkstra.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#define inf 65535
#define maxVertexes 100
using namespace std;
class Graph
{
public:
	int numVertexes;
	int matrix[maxVertexes][maxVertexes]={inf};//邻接表
	int pathMatrix[maxVertexes] = {0};
	int previous[maxVertexes] = {0};
	Graph(int numVertexes) :numVertexes(numVertexes) {
		for (int i = 0; i < numVertexes; i++)
			for (int j = 0; j < numVertexes; j++)
			     matrix[i][j] = i==j? 0:inf;
	}
	void insert(int v, int w, int cost)
	{
		matrix[v][w] = cost;
		matrix[w][v] = cost;
	}
	void Shortest_Path_Dijkstra(int s);
};
void Graph::Shortest_Path_Dijkstra(int s)
{
	//初始化
	bool visit[maxVertexes] = {false};
	for (int v = 0; v < numVertexes; ++v)
	{
		pathMatrix[v] = matrix[s][v];
		previous[v] = s;
		visit[v] = false;
	}
	//对于源点s
	pathMatrix[s] = 0;
	visit[s] = true;//已经在集合内

	//求出s到其他点的路径最小值
	for (int v = 0; v < numVertexes; ++v)
	{
		if (v == s) continue;
		//求出未访问的点到s距离最小的点
		int min = inf;
		int minIndex;
		for(int w=0;w<numVertexes;++w)
			if (visit[w] == false && min > pathMatrix[w])
			{
				minIndex = w;
				min = pathMatrix[w];
			}
		visit[minIndex] = true;
		//minIndex强势加入，距离需要修改了
		for(int w=0; w<numVertexes;++w)
			if (visit[w] == false && pathMatrix[w] > pathMatrix[minIndex] + matrix[minIndex][w])
			{
				pathMatrix[w] = pathMatrix[minIndex] + matrix[minIndex][w];
				previous[w] = minIndex;
			}
		for (int i = 0; i < numVertexes; i++)
			cout << pathMatrix[i] << " ";
		cout << endl;
	}
	
}
int main()
{
	Graph graph(9);
	graph.insert(0, 1, 1);
	graph.insert(0, 2, 5);

	graph.insert(1, 3, 7);
	graph.insert(1, 4, 5);
	graph.insert(1, 2, 3);

	graph.insert(2,4,1);
	graph.insert(2,5,7);

	graph.insert(3, 6, 3);
	graph.insert(3, 4, 2);

	graph.insert(4, 6,6);
	graph.insert(4, 7, 9);

	graph.insert(5,4,3);
	graph.insert(5,7,5);

	graph.insert(6, 7, 2);
	graph.insert(6, 8, 7);

	graph.insert(7,8,4);

	/*for (int i = 0; i < graph.numVertexes; i++)
	{
		for (int j = 0; j < graph.numVertexes; j++)
			cout << graph.matrix[i][j]<<" ";
		cout << endl;
	}*/
	graph.Shortest_Path_Dijkstra(0);
	for (int i = 0; i < graph.numVertexes; i++)
		cout << graph.pathMatrix[i] << " ";
	cout << endl;
	/*for (int i = 0; i < graph.numVertexes; i++)
		cout << graph.previous[i] << " ";
	cout << endl;*/
    return 0;
}


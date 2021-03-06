// AdjGraph.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<queue>
#define inf 65535
using namespace std;

const int MaxSize = 100;
//定义边表节点
struct ArcNode
{
	int adjVex;//存储该顶点对应的下标
	int weight;//边表节点对应的权值
	ArcNode* next;//链域，指向下一个邻接点
};
//定义顶点表节点
template<class T>
struct VertexNode
{
	T vertex;//数据域
	ArcNode* firstedge;//边表头指针
	VertexNode(T vertex, ArcNode* firstedge) { this->vertex = vertex; this->firstedge = firstedge; }
};

struct Edge
{
	int start;
	int end;
	int weight;
};
template<class  T>
class AdjGraph
{
public:
	AdjGraph(T a[],int numvertexes);
	~AdjGraph() { cout << "析构函数被执行" << endl; };
	void DFS(int v);//深度优先遍历，从v开始
	void BFS(int v);
	void Insert(int vertex, int arcnode,int weight);//插入边表
	void Show();
	void MiniSpanTree_Prim();
	int Dist(int v1,int v2);
	void prinEdge();
private:
	//VertexNode<int> adjList[MaxSize];//存放顶点表的数组
	vector<VertexNode<T>> adjList;
	vector<Edge> edges;
	int numVertexes, numEdges=0;//定义顶点数以及边数
	bool visited[MaxSize];
	queue<int> Q;//针对下标进入队列
	int mincost[MaxSize] = {inf};
	int adjvex[MaxSize] = {0};
};

template<class T>
AdjGraph<T>::AdjGraph(T a[], int numvertexes)
{
	numVertexes = numvertexes;
	//VertexNode<T>* p = new VertexNode<T>();
	int num = sizeof(a) / sizeof(T);
	cout << num << endl;
	for (int i = 0; i < numVertexes; i++) {
		VertexNode<T>* p = new VertexNode<T>(a[i], NULL);
		visited[i] = false;
		//p->vertex = a[i];
		//p->firstedge = NULL;
		//adjList[i].vertex = a[i];
		//adjList[i].firstedge = NULL;
		adjList.push_back(*p);
	}
	memset(mincost, 0, numVertexes * sizeof(int));
	memset(adjvex, 0, numVertexes * sizeof(int));
}

template<class T>
void AdjGraph<T>::Insert(int vertex, int arcnode,int weight)
{
	ArcNode* node1 = new ArcNode();
	node1->adjVex = arcnode;
	node1->weight = weight;
	if (adjList[vertex].firstedge == NULL) adjList[vertex].firstedge = node1;
	else {
		ArcNode* p = adjList[vertex].firstedge;
		while (p->next != NULL) p = p->next;
		p->next = node1;
	}

	ArcNode* node2 = new ArcNode();
	node2->adjVex = vertex;
	node2 ->weight= weight;
	if (adjList[arcnode].firstedge == NULL) adjList[arcnode].firstedge = node2;
	else {
		ArcNode* p = adjList[arcnode].firstedge;
		while (p->next != NULL) p = p->next;
		p->next = node2;
	}
	edges.push_back(Edge{ vertex, arcnode, weight });
	numEdges++;
}
template<class T>
int AdjGraph<T>::Dist(int v1,int v2)
{
	ArcNode* p = adjList[v1].firstedge;
	int dist=inf;
	while(p!=NULL){ 
		int j = p->adjVex; 
		if (j == v2) { dist = p->weight; break; }
		p = p->next;
	}
	return dist;
}

template<class T>
void AdjGraph<T>::DFS(int v)
{
	//for (int i = 0; i < numVertexes; i++) visited[i] = false;
	cout << adjList[v].vertex<<" ";
	visited[v] = true;
	ArcNode* p = adjList[v].firstedge;
	while (p) {
		int j = p->adjVex;
		if (visited[j] == false) DFS(j);
		p = p->next;
	}
}
template<class T>
void AdjGraph<T>::BFS(int v)
{
	for (int i = 0; i < numVertexes; i++) visited[i] = false;
	cout << adjList[v].vertex<<" ";
	visited[v] = true;
	Q.push(v);//下标进入队列
	while (!Q.empty()) {
		int q = Q.front();
		Q.pop();
		ArcNode*p = adjList[q].firstedge;
		while (p) {
			int j = p->adjVex;
			if (visited[j] == false) {
				cout << adjList[j].vertex << " ";
				visited[j] = true;
				Q.push(j);
			}
			p = p->next;
		}
	}
	cout << endl;
}
template<class T>
void AdjGraph<T>::prinEdge()
{
	vector<Edge>::iterator iter;
	for (iter = edges.begin(); iter != edges.end(); iter++)
		cout << (*iter).start << "->"<<(*iter).end << "(" << (*iter).weight << ")" << endl;
}
template<class T>
void AdjGraph<T>::Show()
{
	cout << "邻接表为：" << endl;
	for (int i = 0; i < numVertexes; i++)
	{
		cout << adjList[i].vertex;
		ArcNode* p = adjList[i].firstedge;
		while (p != NULL)
		{
			cout << "->(" <<p->weight<<")"<<"->"<< p->adjVex;
			p = p->next;
		}
		cout << endl;
	}
}
/*
分为两个阶段：1、初始化。2、找到最小的cost，3、更新cost数组*/
template<class T>
void AdjGraph<T>::MiniSpanTree_Prim()
{
	for (size_t i = 0; i != numVertexes; i++) mincost[i] = inf;
	memset(adjvex, 0, numVertexes * sizeof(int));
	//for (size_t idx = 0; idx != numVertexes; idx++) cout << mincost[idx] << "  " << adjvex[idx] << endl;
	adjvex[0] = 0;//表示与0的距离为0
	/*初始化，此时U内只有一个节点0，mincost是所有点与0之间距离，adjvex表示下标为i的点与0之间为近邻关系*/
	ArcNode* p = adjList[0].firstedge;
	if (p== NULL) { cout << "This is not a real Graph!" << endl; return; }
	while (p != NULL) { 
		int j = p->adjVex;
		mincost[j] = p->weight;
		adjvex[j] = 0; 
		p = p->next; }

	/*遍历所有的点*/
	for (size_t i = 1; i != numVertexes; i++)
	{
		int Min=inf;
		int k = -1;//k就是一个下标，是最小的cost对应的下标
		/*找出当前cost最小的点*/
		for(size_t j=1;j!=numVertexes;j++)
			if (mincost[j] != 0 && mincost[j] < Min) { Min = mincost[j]; k = j; }
		cout << adjvex[k] << " " << k << endl;//k=1 at first

		mincost[k] = 0;//表示已经完成任务，k加入
		/*由于k的加入，权值表要发生变化*/
		for(size_t j=1;j!=numVertexes;j++)//除源点以外的其他点
			if (mincost[j] != 0 && mincost[j] > Dist(k, j)) {
				mincost[j] = Dist(k, j);
				adjvex[j] = k;
			}
	}
}
int main()
{
	//int a[5] = {0,1,2,3,4};
	//AdjGraph<int> myGraph(a, 5);
	//myGraph.Insert(0, 1,10);
	//myGraph.Insert(0, 3,20);
	//myGraph.Insert(1, 0);
	//myGraph.Insert(1, 2,30);
	//myGraph.Insert(1, 4,40);
	//myGraph.Insert(2, 1);
	//myGraph.Insert(2, 3,50);
	//myGraph.Insert(2, 4,60);
	//myGraph.Insert(3, 0);
	//myGraph.Insert(3, 2);
	//myGraph.Insert(4, 2);
	//myGraph.Insert(4, 1);
	int a[] = { 0,1,2,3,4,5,6,7,8 };
	AdjGraph<int> myGraph(a, 9);
	myGraph.Insert(0, 1, 10);
	myGraph.Insert(0, 5, 11);

	myGraph.Insert(1, 2, 18);
	myGraph.Insert(1, 8, 12);
	myGraph.Insert(1, 6, 16);

	myGraph.Insert(5, 6, 17);
	myGraph.Insert(5, 4, 26);

	myGraph.Insert(2, 3, 22);
	myGraph.Insert(2, 8, 8);

	myGraph.Insert(8, 3, 21);

	myGraph.Insert(6, 3, 24);
	myGraph.Insert(6, 7, 19);

	myGraph.Insert(7, 3, 16);
	myGraph.Insert(7, 4, 7);

	myGraph.Insert(3, 4, 20);
	myGraph.Show();
	cout << "************深度优先遍历*********************" << endl;
	myGraph.DFS(1);
	cout << endl<<"*********************************************" << endl;
	cout << "************广度优先遍历*********************" << endl;
	myGraph.BFS(0);
	cout << "*********************************************" << endl;
	myGraph.MiniSpanTree_Prim();
	myGraph.prinEdge();
    return 0;
}


// Kruskal.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
using namespace std;
//并查集
void makeSet(vector<int> & father, vector<int> & height)
{
	for (int i = 0; i < father.size(); i++)
	{
		father[i] = i;
		height[i] = 0;
	}
}
int Find(vector<int> & father, int v)
{
	return father[v] == v ? v : father[v]=Find(father,father[v]);
	/*while (father[v] != v)
		v = father[v];
	return v;*/
}
void unionSet(vector<int> & father, vector<int> & height,int x,int y)
{
	x = Find(father,x);
	y = Find(father,y);
	if (x == y) return;
	if (height[x] > height[y])
		father[y] = x;
	else if (height[x] < height[y])
		father[x] = y;
	else {
		height[y]++;
		father[x] = y;
	}
}
//kruskal主要针对边展开的，因此在这里用边的数据结构
struct edge
{
	int begin;
	int end;
	int weight;
	//constructor
	edge(int begin = 0, int end = 0, int weight = 0) :begin(begin), end(end), weight(weight) {}
	bool operator<(const edge & e) {
		return weight < e.weight ? true : false;
	}
	//利用this指针进行赋值运算符重载
	edge & operator=(const edge & e) {
		this->begin = e.begin;
		this->end = e.end;
		this->weight = e.weight;
		return *this;
	}
};
class Graph
{
protected:
	void Sort(int left, int right)
	{
		if (left >= right) return;//递归返回条件
		int i = left, j = right;
		edge pivot = Edges[left];//主元
		while (i != j)
		{
			while (j != i&&Edges[j].weight >= pivot.weight) j--;
			while (i != j&&Edges[i].weight <= pivot.weight) i++;
			if (i != j) {
				edge temp = Edges[i];
				Edges[i] = Edges[j];
				Edges[j] = temp;
			}
		}
		//交换pivot与i
		Edges[left] = Edges[i];
		Edges[i] = pivot;
		Sort(left, i - 1);
		Sort(i + 1, right);
	}
public:
	vector<edge> Edges;
	int numEdges;
	int numVertexes;
	Graph() { numEdges = 0; numVertexes = 0; }

	void InsertEdge(int begin, int end, int weight) { 
		if (begin == end) return;
		numEdges++;
		Edges.push_back(edge(begin, end, weight));
	}
	void sortGraph() { Sort(0, numEdges - 1); }
	void showGraph()
	{
		for (size_t i = 0; i < Edges.size(); ++i)
			cout << Edges[i].begin << " " << Edges[i].end << " " << Edges[i].weight << endl;
	}

	void MiniSpanTree_Kruskal();
};
void Graph::MiniSpanTree_Kruskal()
{
	vector<int> father(numVertexes, 0);
	vector<int> height(numVertexes, 0);//高度
	makeSet(father,height);
	//排序
	this->sortGraph();
	for (int i = 0; i < numEdges; i++)
	{
		int father_x = Find(father, Edges[i].begin);
		int father_y = Find(father, Edges[i].end);
		if (father_x != father_y)
		{
			//father[father_y] = father_x;
			unionSet(father, height, Edges[i].begin, Edges[i].end);
			cout << Edges[i].begin << " " << Edges[i].end << " " << Edges[i].weight << endl;
		}
	}
}
void InitGraph(Graph & myGraph,int numVertexs=0)
{
	myGraph.numVertexes = numVertexs;
	myGraph.InsertEdge(0, 1, 10);
	myGraph.InsertEdge(0, 5, 11);
	myGraph.InsertEdge(1, 2, 18);
	myGraph.InsertEdge(1, 8, 12);
	myGraph.InsertEdge(1, 6, 16);
	myGraph.InsertEdge(5, 6, 17);
	myGraph.InsertEdge(5, 4, 26);
	myGraph.InsertEdge(2, 3, 22);
	myGraph.InsertEdge(2, 8, 8);
	myGraph.InsertEdge(8, 3, 21);
	myGraph.InsertEdge(6, 3, 24);
	myGraph.InsertEdge(6, 7, 19);
	myGraph.InsertEdge(7, 3, 16);
	myGraph.InsertEdge(7, 4, 7);
}

int main()
{
	Graph myGraph;
	InitGraph(myGraph,9);
	//sort(myGraph.Edges.begin(), myGraph.Edges.end());
	cout << "************排序之后的边**********************" << endl;
	myGraph.sortGraph();
	myGraph.showGraph();
	cout << "************最小生成树**********************" << endl;
	myGraph.MiniSpanTree_Kruskal();
	return 0;
}


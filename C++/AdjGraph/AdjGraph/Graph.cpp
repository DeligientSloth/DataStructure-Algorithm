#include<iostream>
#include<vector>
#include<queue>
using namespace std;
/*图的数据结构，用二维vector表示邻接表*/

class AdjGraph
{
private:
	vector<vector<size_t>> adjList;
	size_t numedges, numvertexes;
public:
	AdjGraph(size_t num) :adjList(num), numvertexes(num), numedges(0) {}//构造函数列表
	void vertexInGraph(size_t v){}
	void addEdge(size_t a, size_t b);
	void removeEdge(size_t a, size_t b);
	void addVertex(size_t v);
	void removeVertex(size_t v);
	void printGraph();
};

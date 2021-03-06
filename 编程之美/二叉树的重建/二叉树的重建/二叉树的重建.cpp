// 二叉树的重建.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<assert.h>
#include<vector>
using namespace std;

//自己实现strcpy
char* strcpy_(char* strDest, char* strSrc)
{
	assert(strDest != NULL&&strSrc != NULL);
	char* adress = strDest;
	while ((*(strDest++) = *(strSrc++)) != '\0');
	return adress;
}

//节点声明
template <class T>
struct Node
{
	T value;
	Node *rchild, *lchild;
	Node(T value):value(value),rchild(NULL),lchild(NULL){}
};

bool isValid(char *pPreOrder, char *pInOrder, int nTreeLen)
{
	if (nTreeLen == 0) return true;
	int index = 0;
	while (index < nTreeLen&&pInOrder[index] != pPreOrder[0]) index++;
	if (index == nTreeLen) return false;
	bool leftValid = isValid(pPreOrder + 1, pInOrder, index);
	bool rightValid = isValid(pPreOrder + index + 1, pInOrder + index + 1, nTreeLen - index - 1);
	if ( leftValid== false || rightValid== false)
		return false;
}
template<class T>
void Rebuild(char *pPreOrder, char *pInOrder, int nTreeLen, Node<T>** pRoot)
{
	//参数检查
	/*if (pPreOrder == NULL || *pInOrder == NULL) {
		cout << "到头了" << endl; return;
	}
	if (nTreeLen <= 0) { *pRoot = NULL; return; }*/
	

    //参数都合法，开始构造根节点
	//Node<T>* node = new Node<T>;
	//node->value = pPreOrder[0];//前序遍历第一个节点
	//node->lchild = NULL;
	//node->rchild = NULL;

	//在中序遍历中，找到前序遍历的第一个节点，pPreOrder[0];
	int index = 0;
	while (index < nTreeLen&&pInOrder[index] != pPreOrder[0]) index++;
	if (index == nTreeLen) return;//找不到字符串，判断是否合法
	
	(*pRoot) = (*pRoot) == NULL?  new Node<T>(pPreOrder[0]):(*pRoot);
	//(*pRoot)->value = pPreOrder[0];
	//(*pRoot)->lchild = NULL;
	//(*pRoot)->rchild = NULL;
	
	if (nTreeLen == 1) return;//只有一个节点，直接返回，提高效率，不影响逻辑

	if(index>0)
	  Rebuild(pPreOrder + 1, pInOrder, index, &((*pRoot)->lchild));
	if(nTreeLen-index-1>0)
	  Rebuild(pPreOrder + index + 1, pInOrder + index + 1, nTreeLen - index - 1, &((*pRoot)->rchild));
}
template<class T>
Node<T>* rebuildTree(char *pPreOrder, char *pInOrder, int nTreeLen)
{
	if (nTreeLen == 0) return NULL;

	int index = 0;
	while (index < nTreeLen&&pInOrder[index] != pPreOrder[0]) index++;
	if (index == nTreeLen) return NULL;//找不到字符串，判断是否合法

	Node<T>* node = new Node<T>(pPreOrder[0]);
	
	node->lchild = index > 0 ? rebuildTree<T>(pPreOrder + 1, pInOrder, index) : NULL;
	node->rchild = nTreeLen > index + 1 ? rebuildTree<T>(pPreOrder + index + 1, pInOrder + index + 1, nTreeLen - index - 1) : NULL;
	return node;//堆上变量，需要自己释放
}
template<class T>
void preOrderTraverse(Node<T> *root)
{
	if (root == NULL) return;
	preOrderTraverse(root->lchild);
	preOrderTraverse(root->rchild);
	cout << root->value << " ";
}
template<class T>
void destoryTree(Node<T> *root)
{
	if (root == NULL) return;
	destoryTree(root->lchild);
	destoryTree(root->rchild);
	delete root;
}
class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		if (sequence.empty()) return true;
		int index = 0, len = sequence.size();
		bool isBstLeft = true, isBstRight = true;
		while (sequence[index]<sequence[len - 1]) index++;//index:右子树第一个节点
		while (index <= len - 2)//检查右子树
		{
			if (sequence[index]<sequence[len - 1]) return false;
			index++;
		}

		//0->index-1: 右子树，index->size()-2：左子树
		if (index != 0)
			isBstLeft = VerifySquenceOfBST(vector<int>(&sequence[0], &sequence[index]));
		if (index<len - 1)
			isBstRight = VerifySquenceOfBST(vector<int>(&sequence[index], &sequence[len]));
		if (isBstLeft == false || isBstRight == false) return false;
	}
};
int main()
{
	/*char* pPreOrder = "abdcef";
	char* pInOrder = "dbaecf";
	cout << "有效性：" << isValid(pPreOrder, pInOrder, strlen(pPreOrder))<<endl;
	//Node<char>* pRoot=NULL;
	Node<char>* pRoot = rebuildTree<char>(pPreOrder, pInOrder, strlen(pPreOrder));
	//Rebuild<char>(pPreOrder, pInOrder, strlen(pPreOrder), &pRoot);
	preOrderTraverse(pRoot);
	cout << endl;

	char* pPreOrder2 = "abcd";
	char* pInOrder2= "abcd";
	cout << "有效性：" << isValid(pPreOrder2, pInOrder2, strlen(pPreOrder2)) << endl;
	Node<char>* pRoot2 = NULL;
	Rebuild<char>(pPreOrder2, pInOrder2, strlen(pPreOrder2), &pRoot2);
	preOrderTraverse(pRoot2);

	char* pPreOrder3 = "abdcfe";
	char* pInOrder3 = "dbaecf";
	cout << "有效性：" << isValid(pPreOrder3, pInOrder3, strlen(pPreOrder3)) << endl;

	destoryTree<char>(pRoot);
	destoryTree<char>(pRoot2);*/
	vector<int> a = { 1,2,3,4 };

	Solution my;
	my.VerifySquenceOfBST(a);
    return 0;
}


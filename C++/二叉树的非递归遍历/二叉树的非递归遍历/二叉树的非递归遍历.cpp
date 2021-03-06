// 二叉树的非递归遍历.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
template<class T>
struct BiTNode
{
	T key;
	BiTNode<T> *lchild, *rchild;
	BiTNode(T key):key(key),lchild(NULL),rchild(NULL){}
};
template<class T>
BiTNode<T>* createBiTree(vector<T>& dataVec,int& begin)
{
	//T key;
	//cin >> key;
	if (begin >= dataVec.size()) return NULL;
	if (dataVec[begin] == '#') return NULL;
	BiTNode<T> *root = new BiTNode<T>(dataVec[begin]);
	root->lchild = createBiTree<T>(dataVec,++begin);//每次创建子树都用下一个节点创建
	root->rchild = createBiTree<T>(dataVec,++begin);
	return root;
}
template<class T>
void PreOrderTraverse(BiTNode<T>* root)
{
	if (root == NULL) return;
	cout << root->key << endl;
	PreOrderTraverse(root->lchild);
	PreOrderTraverse(root->rchild);
}
/*
1、非递归遍历二叉树之前序遍历
   ①考虑其中一个过程：都是沿着左子树路径向下遍历访问，并将右子树进站，返回的时候依次访问右子树
   ②返回时候对右子树的访问需要按照过程①的方式访问
2、非递归遍历二叉树之中序遍历
   ①沿着左子树下行，依次进站

*/
/*前序遍历：有两个函数*/
template<class T>
void visitAlongLeftBranch(BiTNode<T>*root,stack<BiTNode<T>*>& S)
{
	while (root!=NULL){
		cout << root->key << endl;
		S.push(root->rchild);
		root = root->lchild;
	}
}
template<class T>
void preOrderTraverse_NR(BiTNode<T>*root)
{
	if (root == NULL) return;
	stack<BiTNode<T>*> S;
	while (true) {
		visitAlongLeftBranch(root, S);
		if (S.empty()) return;
		root = S.top(); S.pop();
	}
}
/*中序遍历，有两个函数*/
template<class T>
void goAlongLeftBranch(BiTNode<T>*root, stack<BiTNode<T>*>& S)
{
	while (root != NULL) {
		S.push(root); root = root->lchild;
	}
}
template<class T>
void InOrderTraverse_NR(BiTNode<T>*root)
{
	if (root == NULL) return;
	stack<BiTNode<T>*> S;
	while (true) {
		goAlongLeftBranch(root, S);
		if (S.empty()) return;
		root = S.top(); cout << root->key << endl;
		S.pop();
		root = root->rchild;//转向右子树
	}
}
//debug指针变量内存使用
template<class T>
void createBiTree(BiTNode<T>** proot,T vec[],int len,int& cur) {
	//T key;
	//cin >> key;
	if (cur >= len) return;
	*proot = (vec[cur] == '#') ? NULL : new BiTNode<T>(vec[cur]);
	if ((*proot) != NULL) {
		createBiTree<T>(&((*proot)->lchild),vec,len,++cur);
		createBiTree<T>(&((*proot)->rchild),vec,len,++cur);
	}
}
int main()
{
	//vector<char> dataVec = { '1','2','4','#','#','5','#','#','3','6','#','#' };
	int begin = 0;
	//BiTNode<char>* root = createBiTree<char>(dataVec,begin);
	//PreOrderTraverse<char>(root);
	char dataVec[7] = { '1','2','#','#','3','#','#' };
	BiTNode<char>* root = NULL;
	createBiTree<char>(&root,dataVec,7,begin);
	preOrderTraverse_NR<char>(root);
	cout << "********************" << endl;
	InOrderTraverse_NR(root);
    return 0;
}


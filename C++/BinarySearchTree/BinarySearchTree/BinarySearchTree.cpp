// BinarySearchTree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

template<class T>
class BiTNode
{
public:
	//数据成员
	T key;
	BiTNode *lchild, *rchild,*parent;
	//构造函数
	BiTNode() { lchild = NULL; rchild = NULL; }
	BiTNode(T Key) { lchild = NULL; rchild = NULL; parent = NULL; this->key = Key; }
	~BiTNode() { }
};
template<class T>
class BiTree
{
public:
	BiTNode<T> *root;//相当于链表头结点，存放根节点的地址
	//成员函数
	BiTree() { root = NULL; }
	BiTree(T a[]) {
		for (size_t i = 0; i < 11; ++i) InsertBiTree(a[i]);
	}
	void DeleteRoot(BiTNode<T> *Root) {
		if (Root == NULL) return;
		DeleteRoot(Root->lchild);
		DeleteRoot(Root->rchild);
		cout << "析构：" << Root->key << endl;
		delete Root;
	}
	~BiTree(){
		//cout << "haha" << endl;
		DeleteRoot(root);
	}
	inline BiTNode<T>* searchBiTree(T key, BiTNode<T>* node,BiTNode<T>* &previous);
	bool InsertBiTree(T key);
	bool deleteNode(T key);//需要改变节点的指向
	void PreOrderTraverse(BiTNode<T> *Root) {
		if (Root == NULL) return;
		cout << Root->key << " ";
		PreOrderTraverse(Root->lchild);
		PreOrderTraverse(Root->rchild);
	}
	void InOrderTraverse(BiTNode<T> *Root) {
		if (Root == NULL) return;
		InOrderTraverse(Root->lchild);
		cout << Root->key << " ";
		InOrderTraverse(Root->rchild);
	}
};
template<class T>
bool BiTree<T>::deleteNode(T Key)
{
	BiTNode<T> *cur = root;
	while (cur != NULL&&cur->key != Key)
		cur = Key > cur->key ? cur->rchild : cur->lchild;
	if (cur == NULL)
		return false;
	if (cur->lchild == NULL)
	{
		if (cur->parent->lchild == cur)
			cur->parent->lchild = cur->rchild;
		else
			cur->parent->rchild = cur->rchild;
		delete cur;
	}
	else if (cur->rchild == NULL)
	{
		if (cur->parent->lchild == cur)
			cur->parent->lchild = cur->lchild;
		else
			cur->parent->rchild = cur->lchild;
		delete cur;
	}
	else
	{
		BiTNode<T> *node = cur->lchild;//转左
		while (node->rchild != NULL) node = node->rchild;//向右找到尽头

		//node节点 与 cur节点之间的替换
		cur->key = node->key;

		if (node->parent->lchild == node)
			node->parent->lchild = node->lchild;
		else
			node->parent->rchild = node->lchild;
		delete node;
	}
}
//求出以root为根的树中，key是否存在
template<class T>
inline BiTNode<T>* BiTree<T>::searchBiTree(T Key,BiTNode<T> *node,BiTNode<T>* &previous)
{
	while (node != NULL&&Key != node->key)
	{
		previous=node; node = Key > node->key ? node->rchild : node->lchild;//转入右子树或者左子树
	}
	return node;
}
template<class T>
bool BiTree<T>::InsertBiTree(T Key)
{
	if (root == NULL) {
		root = new BiTNode<T>(Key); return true;
	}
	//BiTNode<T> *parent=NULL,*node = root;//根节点的parent为空
	/*while (node!=NULL&&Key != node->key)
	{
		parent = node;
		node = Key > node->key ? node->rchild : node->lchild;//转入右子树或者左子树
	}*/
	BiTNode<T> *previous = NULL;
	BiTNode<T> *node = searchBiTree(Key, this->root,previous);
	if (node == NULL)//查找失败
	{
		BiTNode<T> *s = new BiTNode<T>(Key);
		s->parent = previous;
		if (Key > previous->key) previous->rchild = s;
		else previous->lchild = s;
		return true;
	}
	return false;
}
int main()
{
	int a[11] = { 62,88,58,47,35,73,51,99,37,93,50 };
	BiTree<int> myTree(a);
	//for (size_t i = 0; i < 10; ++i) myTree.InsertBiTree(a[i]);
	myTree.InOrderTraverse(myTree.root);
	BiTNode<int> *previous;
	if (myTree.searchBiTree(93, myTree.root,previous)) {
		cout << "存在！" << endl;
		cout << "爸爸节点是：" << previous->key<< endl;
	}
	else cout << "不存在！" << endl;
	myTree.deleteNode(58);
	myTree.InOrderTraverse(myTree.root);
    return 0;
}


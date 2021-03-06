// RB-Tree.cpp: 定义控制台应用程序的入口点。
//先来实现一颗红黑树的简单插入，删除好复杂，不想学不想实现了
/*
所有节点都是红色或者黑色
根节点为黑色
所有的 NULL 叶子节点都是黑色
如果该节点是红色的，那么该节点的子节点一定都是黑色
所有的 NULL 节点到根节点的路径上的黑色节点数量一定是相同的
红黑树还有一个很重要的特性是每次更新操作的旋转次数为O(1)，使其特别适合用来实现持久化的搜索树。
*/

#include "stdafx.h"
#include<iostream>
using namespace std;

//红黑树节点的实现
#define RED 0
#define BLACK 1
template<class T>
class RBTreeNode {
public:
	T key;
	RBTreeNode<T> *right, *left,*parent;
	int color;
	RBTreeNode(T key,int color):key(key),color(color),right(NULL),left(NULL),parent(NULL){}
};
template<class T>
class RBTree {
public:
	RBTree() { root = NULL; size = 0; }
	int size;//树的规模
	RBTreeNode<T>* root;//树根节点指针
	//一些树的公有方法
	RBTreeNode<T>* Insert(T key);
	RBTreeNode<T>* search(T key);
	void PreOrder() { PreOrder(root); cout << endl; }
	void InOrder() { InOrder(root); cout << endl; }
	void PostOrder() { PostOrder(root); cout << endl; }
protected:
	RBTreeNode<T>* search(RBTreeNode<T>* proot,T key,RBTreeNode<T>*& prev);//在树根proot向下查找key
	//左旋和右旋算法
	RBTreeNode<T>* LeftRotation(RBTreeNode<T>* x);
	RBTreeNode<T>* RightRotation(RBTreeNode<T>* y);
	//双红冲突调整
	void RBInsertFixUp(RBTreeNode<T>* z);//z为新插入的节点
	//前序，中序，后序遍历
#define ParentKey(x) (x->parent? x->parent->key:0 )
	void PreOrder(RBTreeNode<T>* proot) {
		if (proot != NULL) {
			cout << proot->key <<"("<<ParentKey(proot) <<","<< (proot->color ? "black" : "red") << ")" <<" ";
			PreOrder(proot->left);
			PreOrder(proot->right);
		}
	}
	void InOrder(RBTreeNode<T>* proot) {
		if (proot != NULL) {
			InOrder(proot->left);
			cout << proot->key << "(" << ParentKey(proot) << "," << (proot->color ? "black" : "red") << ")" << " ";
			InOrder(proot->right);
		}
	}
	void PostOrder(RBTreeNode<T>* proot) {
		if (proot != NULL) {
			PostOrder(proot->left);
			PostOrder(proot->right);
			cout << proot->key << "(" << ParentKey(proot) << "," << (proot->color? "black" : "red")<< ")" << " ";
		}
	}
};
template<class T>
RBTreeNode<T>* RBTree<T>::LeftRotation(RBTreeNode<T>* x) {
	if (x == NULL) return NULL;
	//将以x为根节点的子树进行左旋操作
	RBTreeNode<T>* y = x->right;//记下x的右孩子
	if (y == NULL) return x;//x和y存在是左旋右旋的前提
	//重接y的left
	x->right = y->left;
	if (y->left != NULL) y->left->parent = x;
	//将子树重接到原来的树中
	if (x->parent == NULL) root = y;
	else if (x->parent->left == x) x->parent->left = y;
	else x->parent->right = y;
	y->parent = x->parent;
	//重接x
	y->left = x;
	x->parent = y;
	//将子树重接到原来的树中，这一步放到重接x的前面，因为重接x后，x的parent就变为y了
	return y;//返回新的树根
}
template<class T>
RBTreeNode<T>* RBTree<T>::RightRotation(RBTreeNode<T>* y) {
	if (y == NULL) return NULL;
	RBTreeNode<T>* x = y->left;
	if (x == NULL) return x;
	
	y->left = x->right;
	if (x->right) x->right->parent = y;

	if (y->parent == NULL) root = x;
	else if (y->parent->left == y) y->parent->left = x;
	else y->parent->right = x;
	x->parent = y->parent;

	x->right = y;
	y->parent = x;
	return x;
}
template<class T>
RBTreeNode<T>* RBTree<T>::search(RBTreeNode<T>* proot, T key, RBTreeNode<T>*& prev) {
	if (proot == NULL) return NULL;
	while (proot) {
		prev = proot;
		proot = key < proot->key ? proot->left : proot->right;//包含了等于的情况
		/*if (key < proot->key) proot = proot->left;
		else if (key > proot->key) proot = proot->right;
		else return proot;*/
	}
	return proot;
}
template<class T>
RBTreeNode<T>* RBTree<T>::Insert(T key) {
	RBTreeNode<T>* prev = NULL;
	//if(search(root, key, prev)) return false;//插入节点已经存在
	search(root, key, prev);
	//根据prev插入
	RBTreeNode<T>* p = new RBTreeNode<T>(key, RED);//新建一个红色节点
	if (prev == NULL) root = p;
	else if (key < prev->key) prev->left = p;
	else prev->right = p;
	p->parent = prev;
	size++;
	//此处需要调整
	RBInsertFixUp(p);//p处插入，从p开始调整
	return p;
}
template<class T>
void RBTree<T>::RBInsertFixUp(RBTreeNode<T>* z) {
	//主要分成两种对称的情况，分成三大类
	while (z->parent&&z->parent->color == RED) {//z->parent==NUll的时候，z为根节点，直接染黑
		if (z->parent == z->parent->parent->left) {
			//父亲为红色，那么祖父肯定存在？
			RBTreeNode<T>* y = z->parent->parent->right;
			if (y&&y->color == RED) {
				//不存在时为哨兵，看做黑节点一样
				z->parent->color = BLACK;//父亲变为黑色
				z->parent->parent->color = RED;//祖父变为红色
				y->color = BLACK;
				z = z->parent->parent;//双红冲突转移到了祖父那，坑祖父啊！
				continue;//后面不用管了
			}
			else if (z == z->parent->right) {
				z = z->parent;//为了与LL的情况统一
				LeftRotation(z);
			}
			z->parent->color = BLACK;
			z->parent->parent->color = RED;
			RightRotation(z->parent->parent);
		}
		else {//z的父亲为右孩子
			RBTreeNode<T>* y = z->parent->parent->left;
			if (y&&y->color == RED) {
				z->parent->color = BLACK;//父亲变为黑色
				z->parent->parent->color = RED;//祖父变为红色
				y->color = BLACK;//叔叔变为黑色，即祖父的黑色转移到两个分支
				z = z->parent->parent;//双红冲突转移到了祖父那，坑祖父啊！
				continue;//后面不用管了
			}
			else if (z == z->parent->left) {
				z = z->parent;
				RightRotation(z);
			}
			z->parent->color = BLACK;
			z->parent->parent->color = RED;
			LeftRotation(z->parent->parent);
		}
	}
	root->color = BLACK;//一直将双红冲突向上转移，到了根节点z->parent==NULL退出，根节点的颜色设置为红色
}
int main()
{
	int a[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80 };
	RBTree<int>* rbtree = new RBTree<int>;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++) rbtree->Insert(a[i]);
	/*rbtree->Insert(3);
	rbtree->Insert(2);
	rbtree->Insert(2);
	rbtree->Insert(1);
	rbtree->RightRotation(rbtree->root->left);
	/*rbtree->Insert(1);
	rbtree->Insert(2);
	rbtree->Insert(2);
	rbtree->Insert(3);
	rbtree->LeftRotation(rbtree->root->right);*/
	rbtree->PreOrder();
	rbtree->InOrder();
	rbtree->PostOrder();
    return 0;
}


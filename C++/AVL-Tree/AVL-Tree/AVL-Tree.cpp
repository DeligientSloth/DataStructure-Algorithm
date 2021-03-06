// AVL-Tree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//same as avl.cpp
template<class T>
class AVLTreeNode
{
public:
	T key;
	int height;//高度，待会求BF
	AVLTreeNode<T> *rchild, *lchild, *parent;
	AVLTreeNode(T value, AVLTreeNode<T> *lchild, AVLTreeNode<T> *rchild, AVLTreeNode<T> *parent) :
		key(value), lchild(lchild), rchild(rchild), parent(parent), height(0) {}
};
template<class T>
class AVLTree
{
private:
	//AVLTreeNode<T>* _root;
public:
	AVLTreeNode<T>* _root;
	size_t _size;
	AVLTree() :_root(NULL), _size(0) {};
	//~AVLTree();
	//int Height() { return root->height; }//获取高度
	void preOrderTraverse() { cout << "前序遍历序列：" << " "; preOrderTraverse(_root); cout << endl; }
	void InOrderTraverse() { cout << "中序遍历序列：" << " "; InOrderTraverse(_root); cout << endl; }
	void postOrderTraverse() { cout << "后序遍历序列：" << " "; postOrderTraverse(_root); cout << endl; }

	bool insert(T key) { return insert(key, _root) != NULL; }
	//bool remove(T key) { return remove(key, root); }
protected:
	void preOrderTraverse(AVLTreeNode<T>* proot);
	void InOrderTraverse(AVLTreeNode<T>* proot);
	void postOrderTraverse(AVLTreeNode<T>* proot);
	//插入和删除的接口
	AVLTreeNode<T>* insert(T key, AVLTreeNode<T>* proot);//返回插入后节点的位置
	//bool remove(T key, AVLTreeNode<T>* proot);
	//旋转需要的
	AVLTreeNode<T>* LeftLeftRotation(AVLTreeNode<T>* proot);
	AVLTreeNode<T>* LeftRightRotation(AVLTreeNode<T>* proot);
	AVLTreeNode<T>* RightRightRotation(AVLTreeNode<T>* proot);
	AVLTreeNode<T>* RightLeftRotation(AVLTreeNode<T>* proot);
	//查找直接前驱和后级
	AVLTreeNode<T>* getPrevNode(AVLTreeNode<T>* proot) {
		while (proot->lchild)proot = proot->lchild;
		return proot;
	}
	AVLTreeNode<T>* getSuccNode(AVLTreeNode<T>* proot) {
		while (proot->rchild)proot = proot->rchild;
		return proot;
	}
	//和高度有关的函数
	int Height(AVLTreeNode<T>* proot) { return proot == NULL ? 0 : proot->height; }
	void updateHeight(AVLTreeNode<T>* proot) {
		if (proot) proot->height = 1 + max(Height(proot->lchild), Height(proot->rchild));
	}
	void updateHeightAbove(AVLTreeNode<T>* proot) {
		while (proot) {
			updateHeight(proot); proot = proot->parent;
		}
	}
	//AVLTreeNode<T>*& search(AVLTreeNode<T>*& proot, T key, AVLTreeNode<T>*& prev);can be removed
};
template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(T key, AVLTreeNode<T>* proot) {
	AVLTreeNode<T>* prev = NULL;
	while (proot) {
		prev = proot;
		proot = (key < proot->key) ? proot->lchild : proot->rchild;
	}
	AVLTreeNode<T>* node = new AVLTreeNode<T>(key, NULL, NULL, prev);
	if (prev == NULL) _root = node;
	else if (key < prev->key) prev->lchild = node;
	else prev->rchild = node;
	_size++;
	//updateHeightAbove(node);
	//需要向上调节平衡，并且更新高度
	for (AVLTreeNode<T>* p = node; p; p = p->parent) {
		if (Height(p->lchild) - Height(p->rchild) >= 2) {
			if (Height(p->lchild->lchild) >= Height(p->lchild->rchild))
				LeftLeftRotation(p);
			else LeftRightRotation(p);
			break;//祖先高度不会有变化
		}
		else if (Height(p->rchild) - Height(p->lchild) >= 2) {
			if (Height(p->rchild->rchild) >= Height(p->rchild->lchild))
				RightRightRotation(p);
			else RightLeftRotation(p);
			break;
		}
		else
			updateHeight(p);//正常情况下更新高度
	}
	return node;
}
int main()
{
	AVLTree<int>* avltree = new AVLTree<int>;
	vector<int> a = { 3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9 };
	for (int num : a) avltree->insert(num);
	avltree->preOrderTraverse();
	avltree->InOrderTraverse();
	avltree->postOrderTraverse();
	//avltree->RightRightRotation(avltree->_root);
    return 0;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::LeftLeftRotation(AVLTreeNode<T>* proot) {
	if (proot == NULL) return NULL;
	AVLTreeNode<T>* y = proot->lchild;
	if (y == NULL) return proot;//不需要调整

	proot->lchild = y->rchild;
	if (y->rchild) y->rchild->parent = proot;

	//重接外围的树，将proot->parent定位到新得到的树根y
	if (proot->parent == NULL) _root = y;
	else if (proot == proot->parent->lchild) proot->parent->lchild = y;
	else proot->parent->rchild = y;
	y->parent = proot->parent;

	y->rchild = proot;
	proot->parent = y;

	updateHeight(proot);
	updateHeight(y);
	return y;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::LeftRightRotation(AVLTreeNode<T>* proot) {
	RightRightRotation(proot->lchild);
	return LeftLeftRotation(proot);
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::RightRightRotation(AVLTreeNode<T>* proot) {
	if (proot == NULL) return NULL;
	AVLTreeNode<T>* y = proot->rchild;
	if (y == NULL) return proot;//不需要调整
	proot->rchild = y->lchild;
	if (y->lchild) y->lchild->parent = proot;
	//重接外围的树，将proot->parent定位到新得到的树根y
	if (proot->parent == NULL) _root = y;
	else if (proot == proot->parent->lchild) proot->parent->lchild = y;
	else proot->parent->rchild = y;
	y->parent = proot->parent;

	y->lchild = proot;
	proot->parent = y;
	updateHeight(proot);
	updateHeight(y);
	return y;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::RightLeftRotation(AVLTreeNode<T>* proot) {
	LeftLeftRotation(proot->rchild);
	return RightRightRotation(proot);
}


#define ParentKey(p) (p->parent==NULL? 0:p->parent->key)
template<class T>
void AVLTree<T>::preOrderTraverse(AVLTreeNode<T>* proot) {
	if (proot != NULL) {
		cout << proot->key << "(p:" << ParentKey(proot) << " H:" << proot->height << ")" << " ";
		preOrderTraverse(proot->lchild);
		preOrderTraverse(proot->rchild);
	}
}
template<class T>
void AVLTree<T>::InOrderTraverse(AVLTreeNode<T>* proot) {
	if (proot != NULL) {
		InOrderTraverse(proot->lchild);
		cout << proot->key <<"(p:" << ParentKey(proot) << " H:" << proot->height << ")" << " ";
		InOrderTraverse(proot->rchild);
	}
}
template<class T>
void AVLTree<T>::postOrderTraverse(AVLTreeNode<T>* proot) {
	if (proot != NULL) {
		postOrderTraverse(proot->lchild);
		postOrderTraverse(proot->rchild);
		cout << proot->key << "(p:" <<ParentKey(proot)<< " H:" << proot->height << ")" << " ";
	}
}
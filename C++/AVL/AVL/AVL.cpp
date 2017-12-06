// AVL.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>

#define Height(p) (TreeNode*)p==NULL? 0:p->height
#define Max(a,b) a>=b? a:b
using namespace std;

template<class T>
class TreeNode
{
public:
	T data;
	int height;
	TreeNode<T> *rchild, *lchild;
	//构造函数
	TreeNode(T data):data(data),rchild(NULL),lchild(NULL){}

};
template<class T>
class AVLTree
{
private:
	//私有成员设置，可以把节点的左旋，右旋等放入这里，根节点
	TreeNode<T> *root;
	void Left_Left_Rotation(TreeNode<T> **node);
	void Right_Right_Rotation(TreeNode<T> **node);
	void Left_Right_Rotation(TreeNode<T> **node);
	void Right_Left_Rotation(TreeNode<T> **node);

public:
	AVLTree() { root = NULL; }
	void Insert(T key);
	bool search(T key,TreeNode<T>* &prev);
};
template<class T>
void AVLTree<T>::Left_Left_Rotation(TreeNode<T> **node)//要改变node的指向，所以要传入指针的指针
{
	TreeNode<T> *temp;
	temp = (*node)->lchild;
	(*node)->lchild = temp->rchild;
	temp->rchild = (*node);

	(*node)->height = Max(Height((*node)->lchild), Height((*node)->rchild)) + 1;
	temp->height = Max((*node)->height,Height(temp->lchild)) + 1;

	(*node) = temp;
}
template<class T>
void AVLTree<T>::Right_Right_Rotation(TreeNode<T> **node)
{
	TreeNode<T> *temp;
	temp = (*node)->rchild;
	(*node)->rchild = temp->lchild;
	temp->lchild = (*node);

	(*node)->height = Max(Height((*node)->lchild), Height((*node)->rchild)) + 1;
	temp->height = Max((*node)->height, Height(temp->rchild)) + 1;

	(*node) = temp;
}
template<class T>
void AVLTree<T>::Left_Right_Rotation(TreeNode<T> **node)
{
	Right_Right_Rotation(&((*node)->lchild));
	Left_Left_Rotation(node);
}
template<class T>
void AVLTree<T>::Right_Left_Rotation(TreeNode<T> **node)
{
	Left_Left_Rotation(&((*node)->rchild));
	Right_Right_Rotation(node);
}
template<class T>
bool AVLTree<T>::search(T key,TreeNode<T>* &prev)
{
	TreeNode<T>* t = root;
	while (t != NULL&&t->data!=key)
	{
		prev = t;
		t = key >= t->data ? t->rchild : t->lchild;
	}
	return t == NULL ? false : true;
}
template<class T>
void AVLTree<T>::Insert(T key)
{
	if (root == NULL)
	{
		root = new TreeNode(key);
	}
	else
	{
		TreeNode<T> *prev;
		if (search(key, prev) == true) return;

	}
}
int main()
{
    return 0;
}


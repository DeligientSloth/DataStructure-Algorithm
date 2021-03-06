// BinarySearchTree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdlib.h>
#include<iostream>
#include<queue>
using namespace std;
typedef int  T;//T表示类型
struct BiTNode
{
	T key;
	struct BiTNode *lchild, *rchild;
};
typedef struct BiTNode BiTNode;
BiTNode* createTree1()
{
	T key;
	scanf_s("%c", &key);
	//key = getchar();
	if (key == '#') return NULL;
	
	//生成根节点
	BiTNode* node = (BiTNode*)malloc(sizeof(BiTNode));
	if (node == NULL) exit(-1);
	node->key = key;
	node->lchild = createTree1();
	node->rchild = createTree1();
	return node;//汇总
}
void createTree2(BiTNode **root)
{
	T key;
	cin >> key;
	if (key == '#') *root = NULL;
	else
	{
	  *root= (BiTNode*)malloc(sizeof(BiTNode));
	  (*root)->key = key;
	  createTree2(&((*root)->lchild));
	  createTree2(&((*root)->rchild));
	}
}
//根据数组层次建立二叉树
void createTree3(BiTNode **root)
{
	char ch;
	if (*root == NULL)
	{
		cout << "请输入根节点的值: ";
		cin >> ch;
		*root = new BiTNode;
		(*root)->key = ch;
		(*root)->lchild = NULL;
		(*root)->rchild = NULL;
	}
	queue<BiTNode*> Q;
	Q.push(*root);
	while (!Q.empty())
	{
		if (Q.front() != NULL)
		{
			BiTNode* lchildNode, *rchildNode;
			cout << "请输入节点" << Q.front()->key << "的左孩子：";
			cin >> ch;
			if (ch != '#')
			{
				lchildNode = new BiTNode;
				lchildNode->key = ch;
			}
			else
				lchildNode = NULL;
			Q.push(lchildNode);

			cout << "请输入节点" << Q.front()->key << "的右孩子：";
			cin >> ch;
			if (ch != '#')
			{
				rchildNode = new BiTNode;
				rchildNode->key = ch;
			}
			else
				rchildNode = NULL;
			Q.push(rchildNode);

			Q.front()->lchild = lchildNode;
			Q.front()->rchild = rchildNode;
		}
		Q.pop();
	}
}

void PreOrderTraverse(BiTNode* root)
{
	if (root == NULL) return;
	printf("%d ", root->key);
	PreOrderTraverse(root->lchild);
	PreOrderTraverse(root->rchild);
}
void InOrderTraverse(BiTNode* root)
{
	if (root == NULL) return;
	InOrderTraverse(root->lchild);
	printf("%d ", root->key);
	InOrderTraverse(root->rchild);
}
bool searchBinarySearchTree(BiTNode *root, T key,BiTNode* &prev)
{
	BiTNode *cur=root;
	prev = NULL;
	while (cur != NULL&&cur->key != key)
	{
		prev = cur;
		cur = key > cur->key ? cur->rchild : cur->lchild;
	}
	//cout << "haha" << endl;
	return cur==NULL? false:true;
}
//建立二叉排序树
void createBinarySearchTree(BiTNode **root,T key)
{
	//生成一个节点
	BiTNode* s = new BiTNode;
	s->key = key;
	//cout << s->lchild<<" -----"<<NULL<<endl;
	s->lchild = NULL;
	s->rchild = NULL;

	if (*root == NULL) {
		*root = s;
		return;
	}
	BiTNode  *prev = NULL;
	if (searchBinarySearchTree(*root, key, prev) == false)
	{
		if (key > prev->key) prev->rchild = s;//改变内容
		else prev->lchild = s;
	}
}
int main()
{
	/*BiTNode *root2=NULL;
	//int a[4] = { 1,2,3,4 };
	BiTNode* root1=createTree1();
	PreOrderTraverse(root1);
	createTree2(&root2);
	PreOrderTraverse(root2);*/
	/*BiTNode *root3 = NULL;
	createTree3(&root3);
	PreOrderTraverse(root3);*/
	BiTNode *bstTree = NULL;
	int a[11] = { 62,88,58,47,35,73,51,99,37,93,50 };
	for(int i=0;i<11;i++)
	    createBinarySearchTree(&bstTree, a[i]);
	InOrderTraverse(bstTree);
    return 0;
}


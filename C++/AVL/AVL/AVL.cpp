// AVL.cpp: 定义控制台应用程序的入口点。
//http://www.cnblogs.com/skywang12345/p/3577360.html
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>


using namespace std;
//创建AVL树节点
template<class T>
class AVLTreeNode
{
public:
	T key;
	int height;//高度，待会求BF
	AVLTreeNode<T> *rchild, *lchild,*parent;
	AVLTreeNode(T value,AVLTreeNode<T> *lchild,AVLTreeNode<T> *rchild, AVLTreeNode<T> *parent):
		key(value),lchild(lchild),rchild(rchild),parent(parent),height(0){}
};
template<class T>
class AVLTree
{
private:
	AVLTreeNode<T>* root;
public:
	size_t _size;
	AVLTree() :root(NULL),_size(0) {};
	//~AVLTree();
	//int Height() { return root->height; }//获取高度
	void preOrderTraverse() { cout << "前序遍历序列：" << " "; preOrderTraverse(root); cout << endl; }
	void InOrderTraverse() { cout << "中序遍历序列：" << " "; InOrderTraverse(root); cout << endl; }
	void postOrderTraverse() { cout << "后序遍历序列：" << " "; postOrderTraverse(root); cout << endl; }

	//查找，插入，删除
	AVLTreeNode<T>* search(T key) { 
		AVLTreeNode<T>* prev = NULL;
		return search(root,key, prev);
	};
	AVLTreeNode<T>* iterativeSearch(T key);
	T getMin() { return getMin(root)->key; }
	T getMax() { return getMax(root)->key; }
	bool insert(T key);
	bool remove(T key) { return remove(key, root); };
	bool Remove(T key) { return Remove(key, root); }
	void deleteTree();
	void printTree();

protected:
	void preOrderTraverse(AVLTreeNode<T>* proot);
	void InOrderTraverse(AVLTreeNode<T>* proot);
	void postOrderTraverse(AVLTreeNode<T>* proot);
	//旋转需要的
	AVLTreeNode<T>* LeftLeftRotation(AVLTreeNode<T>*& proot);
	AVLTreeNode<T>* LeftRightRotation(AVLTreeNode<T>*& proot);
	AVLTreeNode<T>* RightRightRotation(AVLTreeNode<T>*& proot);
	AVLTreeNode<T>* RightLeftRotation(AVLTreeNode<T>*& proot);

	AVLTreeNode<T>* getMin(AVLTreeNode<T>* proot) { 
		while (proot->lchild)proot = proot->lchild; 
		return proot; 
	}
	AVLTreeNode<T>* getMax(AVLTreeNode<T>* proot) { 
		while (proot->rchild)proot = proot->rchild; 
		return proot; 
	}

	int Height(AVLTreeNode<T>* proot) { return proot == NULL ? 0 : proot->height; }
	void updateHeight(AVLTreeNode<T>* proot){
		if(proot) proot->height = 1+max(Height(proot->lchild), Height(proot->rchild));
	}
	void updateHeightAbove(AVLTreeNode<T>* proot) {
		while (proot) {
			updateHeight(proot); proot = proot->parent;
		}
	}

	bool insert(T key,AVLTreeNode<T>*& proot, AVLTreeNode<T>* parent);
	bool Insert(T key, AVLTreeNode<T>*& proot);//采用search方法
	bool remove(T key, AVLTreeNode<T>*& proot);
	bool Remove(T key, AVLTreeNode<T>*& proot);
	AVLTreeNode<T>*& search(AVLTreeNode<T>*& proot,T key,AVLTreeNode<T>*& prev);

};
template<class T>
void AVLTree<T>::preOrderTraverse(AVLTreeNode<T>* proot) {
	if (proot != NULL) {
		cout << proot->key <<"("<<proot->height<<")"<< " ";
		preOrderTraverse(proot->lchild);
		preOrderTraverse(proot->rchild);
	}
}
template<class T>
void AVLTree<T>::InOrderTraverse(AVLTreeNode<T>* proot) {
	if (proot != NULL) {
		InOrderTraverse(proot->lchild);
		cout << proot->key << "(" << proot->height << ")" << " ";
		InOrderTraverse(proot->rchild);
	}
}
template<class T>
void AVLTree<T>::postOrderTraverse(AVLTreeNode<T>* proot) {
	if (proot != NULL) {
		postOrderTraverse(proot->lchild);
		postOrderTraverse(proot->rchild);
		cout << proot->key << "(" << proot->height << ")" << " ";
	}
}

#define EQUAL(e,proot) (!proot)||(e==proot->key) 
template<class T>
AVLTreeNode<T>*& AVLTree<T>::search(AVLTreeNode<T>*& proot, T key, AVLTreeNode<T>*& prev) {//这里的proot要是引用
	//查找以proot为根的子树，返回查找的节点，以及该节点的前一个节点
	if (EQUAL(key, proot)) return proot;
	prev = proot;
	while (true) {
		//curnode要是引用类型，这样curnode与prev的左右孩子绑定在一块
		//如果不是引用，curnode是左右孩子的地址，返回这个地址，insert需要改变这个地址指针的指向
		/*
		如果不是引用，系统开辟一个内存给curnode，curnode里面的内容是左右孩子,
		但是insert接口会new新的内存空间,curnode里面的地址值会重新指向这个空间，但是左右孩子不变
		因为curnode的地址与左右孩子不同，new后curnode地址里面的值改变了，但是左右孩子里面并没有改变
		可以返回左右孩子的地址！
		return &curnode;接口变为AVLTreeNode<T>**
		*/
		AVLTreeNode<T>*& curnode=(key < prev->key) ? prev->lchild : prev->rchild;//重新确定树根
		if (EQUAL(key, curnode)) { return curnode; }
		prev = curnode;//更新下次查询的前一个节点
	}
}
/*
两种写法：1、记下根节点的左子树 2、根节点左子树改为原来左子树的右子树 
          3、原来记下的左子树的右子树等于根节点 4、返回记下来的左子树作为新的树根，更新高度
*/
template<class T>
AVLTreeNode<T>* AVLTree<T>::LeftLeftRotation(AVLTreeNode<T>*& proot) {
	if (proot == NULL) return NULL;
	AVLTreeNode<T>* L = proot->lchild;
	AVLTreeNode<T>* pp = proot->parent;
	if (L == NULL) return proot;//不翻转
	proot->lchild = L->rchild;

	if(L->rchild) (L->rchild)->parent = proot;

	L->rchild = proot;
	
	proot->parent = L;
	L->parent = pp;
	//L和p的高度可能发生变化
	proot->height = max(Height(proot->rchild), Height(proot->lchild)) + 1;
	L->height = max(proot->height, Height(proot->lchild)) + 1;

	//proot = L;
	return L;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::RightRightRotation(AVLTreeNode<T>*& proot) {
	if (proot == NULL) return NULL;
	AVLTreeNode<T>* R = proot->rchild;
	AVLTreeNode<T>* pp = proot->parent;

	if (R == NULL) return proot;//不翻转
	proot->rchild=R->lchild;
	if(R->lchild) (R->lchild)->parent = proot;
	R->lchild = proot;
	R->parent = pp;

	proot->parent = R;
	
	proot->height= max(Height(proot->rchild), Height(proot->lchild)) + 1;
	R->height = max(proot->height, Height(R->rchild)) + 1;

	//proot = R;
	return R;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::LeftRightRotation(AVLTreeNode<T>*& proot) {
	proot->lchild = RightRightRotation(proot->lchild);
	proot = LeftLeftRotation(proot);
	return proot;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::RightLeftRotation(AVLTreeNode<T>*& proot) {
	proot->rchild = LeftLeftRotation(proot->rchild);
	proot = RightRightRotation(proot);
	return proot;
}

#define LeftLeftInsert(x,proot) x<proot->lchild->key
#define RightRightInsert(x,proot) x>proot->rchild->key
template<class T>
bool AVLTree<T>::insert(T key, AVLTreeNode<T>*& proot, AVLTreeNode<T>* parent) {
	//该树为空树
	if (proot == NULL) {
		proot = new AVLTreeNode<T>(key, NULL, NULL, parent);
	}
	else {
		if (key < proot->key) {//插入左子树，可能超出
			if(!insert(key, proot->lchild, proot)) return false;
			if (Height(proot->lchild) - Height(proot->rchild) == 2)
				proot = LeftLeftInsert(key,proot) ? LeftLeftRotation(proot) : LeftRightRotation(proot);
		}
		else {
			if(!insert(key, proot->rchild, proot)) return false;
			if (Height(proot->rchild) - Height(proot->lchild) == 2) {
				proot = RightRightInsert(key,proot)? RightRightRotation(proot) : RightLeftRotation(proot);
			}
		}
	}
	updateHeight(proot);
	return true;
}

#define LeftLeftDelete(x,proot) x>=proot->rchild->key
#define RightRightDelete(x,proot) x<=proot->lchild->key
template<class T>
bool AVLTree<T>::remove(T key, AVLTreeNode<T>*& proot) {
	if (proot == NULL) return false;
	if (key < proot->key) {
		//删除节点在左子树
		remove(key, proot->lchild);//执行删除
		cout << proot->key << ":delta:" << Height(proot->lchild) - Height(proot->rchild) << endl;
		if (Height(proot->rchild) - Height(proot->lchild) == 2) {
			//proot = RightRightDelete(key, proot) ? RightRightRotation(proot) : RightLeftRotation(proot);
			AVLTreeNode<T>* rnode = proot->rchild;
			if (Height(rnode->rchild) >= Height(rnode->lchild))
				proot = RightRightRotation(proot);
			else
				proot= RightLeftRotation(proot);
		}
	}
	else if (key > proot->key) {
		remove(key, proot->rchild);
		cout << proot->key << ":delta:" << Height(proot->lchild) - Height(proot->rchild) << endl;
		if (Height(proot->lchild) - Height(proot->rchild) == 2) {
			//proot = LeftLeftDelete(key, proot) ? LeftLeftRotation(proot) : LeftRightRotation(proot);
			AVLTreeNode<T>* lnode = proot->lchild;
			if (Height(lnode->lchild) >= Height(lnode->rchild))
				proot = LeftLeftRotation(proot);
			else
				proot = LeftRightRotation(proot);
		}
	}
	else {
		//开始删除
		if (proot->lchild == NULL || proot->rchild == NULL) {//左右子树一个为空或者都为空
			AVLTreeNode<T>* temp = proot;
			proot = proot->lchild ? proot->lchild : proot->rchild;
			delete temp;
		}
		else {
			if (Height(proot->lchild) > Height(proot->rchild)) {
				AVLTreeNode<T>* prevnode = getMax(proot->lchild);
				proot->key = prevnode->key;
				remove(prevnode->key,proot->lchild);
			}
			else {
				AVLTreeNode<T>* succnode = getMin(proot->rchild);
				proot->key = succnode->key;
				remove(succnode->key, proot->rchild);
			}
		}
	}
	updateHeight(proot);
	return true;
}
#define IsRoot(x) this->root==x
#define IsLChild(x) x->parent->lchild==x
#define FromParentTo(x) (IsRoot(x)? this->root:(IsLChild(x) ? x->parent->lchild: x->parent->rchild))

template<class T>
bool AVLTree<T>::Insert(T key, AVLTreeNode<T>*& proot) {
	AVLTreeNode<T>* prev = NULL;
	AVLTreeNode<T>*& x=search(proot, key, prev);
	if (x) return false;//插入失败
	x = new AVLTreeNode<T>(key, NULL, NULL, prev);//插入新节点
	x->height = 1;
	//updateHeightAbove(x);
	_size++;
	//开始avl调整
	AVLTreeNode<T>* g = prev;
	for (g = prev; g; g = g->parent) {
		if (Height(g->lchild) - Height(g->rchild) >= 2) {
			/*if (key < g->lchild->key) 
				FromParentTo(g)=LeftLeftRotation(g);
			else if (key > g->lchild->key) 
				FromParentTo(g)=LeftRightRotation(g);*/
			if(Height(g->lchild->lchild) >= Height(g->lchild->rchild))
				FromParentTo(g) = LeftLeftRotation(g);
			else 
				FromParentTo(g) = LeftRightRotation(g);
			break;
		}
		else if (Height(g->rchild) - Height(g->lchild) == 2) {
			/*if (key > g->rchild->key) 
				FromParentTo(g)=RightRightRotation(g);
			else if (key < g->rchild->key) 
				FromParentTo(g)=RightLeftRotation(g);*/
			if(Height(g->rchild->rchild)>=Height(g->rchild->lchild))
				FromParentTo(g) = RightRightRotation(g);
			else
				FromParentTo(g) = RightLeftRotation(g);
			break;
		}
		else updateHeight(g);
	}
	return true;
}
template<class T>
bool AVLTree<T>::Remove(T key, AVLTreeNode<T>*& proot) {
	AVLTreeNode<T>* prev = NULL;
	AVLTreeNode<T>*& x = search(proot, key, prev);
	if (x == NULL) return false;
	if (x->lchild == NULL || x->rchild == NULL) {
		AVLTreeNode<T>* p = x;
		x = x->lchild != NULL ? x->lchild : x->rchild; delete p;
	}
	else {
		AVLTreeNode<T>* succnode = getMin(x->rchild);
		swap(succnode->key, x->key);
		succnode->parent == x ? (x->rchild = succnode->rchild) : (succnode->parent->lchild= succnode->rchild);
		//x = succnode->parent;//删除位置
		prev = succnode->parent;
		delete succnode;
	}
	//平衡调整
	AVLTreeNode<T>* g = prev;
	for (g = prev; g; g = g->parent) {
		if (Height(g->lchild) - Height(g->rchild) >= 2) {
			if (Height(g->lchild->lchild) >= Height(g->lchild->rchild))
				FromParentTo(g) = LeftLeftRotation(g);
			else
				FromParentTo(g) = LeftRightRotation(g);
		}
		else if (Height(g->rchild) - Height(g->lchild) >= 2) {
			if (Height(g->rchild->rchild) >= Height(g->rchild->lchild))
				FromParentTo(g) = RightRightRotation(g);
			else
				FromParentTo(g) = RightLeftRotation(g);
		}
		updateHeight(g);
	}
	return true;
}
template<class T>
bool AVLTree<T>::insert(T key) {
	//return insert(key, root,NULL);
	//return insert(key, root, NULL);
	return Insert(key, root);
}
int main()
{
	/*AVLTree<int> avltree;
	vector<int> vec = { 3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9 };
	for (int item : vec) {
		avltree.insert(item);
		cout << "插入" << item << "后的前序中序后序遍历序列为" << endl;
		avltree.preOrderTraverse();
		avltree.InOrderTraverse();
		avltree.postOrderTraverse();
	}
	cout << avltree._size << endl;
	AVLTreeNode<int>* p;
	for (int item : vec) 
		if ((p = avltree.search(item)) != NULL) 
			cout << p->key <<":parent:"<<(p->parent==NULL? 0:p->parent->key)<<endl;

	cout << "Max: " << avltree.getMax() << "Min:"<<avltree.getMin()<<endl;
	avltree.remove(8);
	avltree.preOrderTraverse();
	avltree.InOrderTraverse();
	avltree.postOrderTraverse();*/
	/*int a = 1;
	int &x = a;
	cout << "&a" << &a << " " << "&x" << &x <<endl;
	a = 2;
	x = a;
	cout << "&a" << &a << " " << "&x" << &x<<endl;
	int b = 100;
	x = b;
	cout << "&a" << &b << " " << "&x" << &x<<endl;
	cout << a << " " << b << endl;*/
	return 0;
}
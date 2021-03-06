// LinkList.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
template<class T>
struct ListNode
{
	T data;
	ListNode *next;
};
//二级指针实现
template<class T>
void InsertList(ListNode<T> **head, T data)
{
	ListNode<T>* node = new ListNode<T>;
	node->data = data;
	node->next = NULL;
	if (*head == NULL)
		*head = node;
	else
	{
		ListNode<T>* p = *head;
		while ((p->next) != NULL)
			p = p->next;
		p->next = node;
	}
}
template<class T>
void InsertList_1(ListNode<T> *head, T data)
{
	if (data==1)
	{
		head->data = data;
		head->next = NULL;
	}
	else
	{
		ListNode<T>* node = new ListNode<T>;
		node->data = data;
		node->next = NULL;
		ListNode<T>* p = head;
		while ((p->next) != NULL)
		{
			p = p->next;
			//cout << "haha" <<data<< endl;
		}
		p->next = node;
	}
}
template<class T>
void showList(ListNode<T>* head)
{
	ListNode<T>* p = head;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
int main()
{
	ListNode<int>* head = NULL;//头结点指针
	for (int i = 1; i <= 10; i++)
		InsertList(&head, i);
	showList(head);

	ListNode<int>* head1 = new ListNode<int>;
	head1->next = NULL;
	for (int i = 1; i <= 10; i++)
		InsertList_1(head1, i);
	showList(head1);
    return 0;
}


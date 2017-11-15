#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;
/*�������ڵ��ʵ��*/
struct BiTNode
{
    ElemType data;
    struct BiTNode* lchild,*rchild;
};
typedef struct BiTNode BiTNode;
/*�������ڵ��ʾΪɭ��*/
typedef BiTNode* BiTree;
/*�����ʾ*/
void CreateBiTree(BiTree* Tree)
{
    ElemType data;
    scanf("%c",&data);
    if(data=='#')
        *Tree=NULL;
    else
    {
        *Tree=(BiTNode*)malloc(sizeof(BiTNode));//����һ���ڵ�
        if(*Tree==NULL){
            printf("�ڴ����ʧ�ܣ�\n");
            exit(-1);
        }
        (*Tree)->data=data;
        CreateBiTree(&((*Tree)->lchild));
        CreateBiTree(&((*Tree)->rchild));
    }
}
void PreOrderTraverse(BiTree Tree)
{
    if(Tree==NULL) return;
    printf("%c",Tree->data);
    PreOrderTraverse(Tree->lchild);
    PreOrderTraverse(Tree->rchild);
}
void InOrderTraverse(BiTree Tree)
{
    if(Tree==NULL) return;
    PreOrderTraverse(Tree->lchild);
    printf("%c",Tree->data);
    PreOrderTraverse(Tree->rchild);
}
void PostOrderTraverse(BiTree Tree)
{
    if(Tree==NULL) return;
    PreOrderTraverse(Tree->lchild);
    PreOrderTraverse(Tree->rchild);
    printf("%c",Tree->data);
}
int main()
{
    BiTree Tree;
    CreateBiTree(&Tree);
    PreOrderTraverse(Tree);
    InOrderTraverse(Tree);
    PostOrderTraverse(Tree);
    return 0;
}

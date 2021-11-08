#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode * next;
} LinkNode ;
//Create single list

void CreateListF(LinkNode *L,ElemType a[],int len)
{
    LinkNode * s;
    L=(LinkNode *)malloc(sizeof(LinkNode));
    L->next =NULL; //init
    for (int i =0;i<len;i++)
    {
        s=(LinkNode *)malloc(sizeof(LinkNode));
        s->data=a[i];
        s->next;
    }
}

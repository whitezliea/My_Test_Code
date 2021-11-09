#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include"iostream"
using namespace std;

typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode * next;
} LinkNode ;
//Create single list
//L->5->4->3->2->1  Head insert
void CreateListF(LinkNode *&L,ElemType a[],int len)
{
    LinkNode * s;
    //L=(LinkNode *)malloc(sizeof(LinkNode));
    L = new LinkNode;
    L->next =NULL; //init
    for (int i =0;i<len;i++)
    {
        s=(LinkNode *)malloc(sizeof(LinkNode));
        s->data=a[i];
        s->next=L->next;
        L->next=s;
    }
}

//Tail insert
//L->1->2->3->4->5
void CreateListR(LinkNode *&L,ElemType a[],int len)
{
    LinkNode *s;
    LinkNode *r;
    L = new LinkNode;
    L->next=NULL;
    r=L;
    for(int i =0;i<len;i++)
    {
        s=(LinkNode *)malloc(sizeof(LinkNode));
        s->data=a[i];
        r->next=s;
        r=s;
    }
    r->next =NULL;
}

void showList(LinkNode *L)
{
    LinkNode * p;
    p=L->next;
     cout<<"list is ";
    while(p!=NULL)
    {
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;

}


int main()
{
   LinkNode *L1;
   int a[5]={1,2,3,4,5};
   CreateListF(L1,a,5);
   cout<<"Head insert"<<endl;
   showList(L1);
   delete L1;
   LinkNode *L2;
   CreateListR(L2,a,5);
   cout<<"Tail insert"<<endl;
   showList(L2);
   delete L2;
   return 0;
}


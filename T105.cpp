#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <cstring>
#define MAXNUM 100

using namespace std;

typedef enum {atom, list} ElemTag;

typedef struct GLNode
{
    ElemTag tag;
    union 
    {
        char data;
        struct 
        {
            struct GLNode *head, *tail;
        }ptr;
    };
} *GList;

typedef struct GLNode2
{
    ElemTag tag;
    union {
        int data; 
        struct GLNode2 *head; 
    }atom_hp;
    struct GLNode2 *tail;

}GLNode2, *GList2;


void initGList1(GList list, char* input, int len)
{
    for(int i=0; i<len; i++)
    {
        if(input[i] == '(')
        {
            
        }
    }
    list->tag = 1;
    list->ptr = NULL;
}

void initGList2(GList2 list)
{
    list->tag = 1;
    list->ptr = NULL;
}

void inputList(int i, int j, int k, CrossList *p)
{
    OLink pt = (OLink)malloc(sizeof(OLNode));

    assert(pt != NULL);
    pt->i = i;
    pt->j = j;
    pt->elem = k;
    
    if (p->rHead[i] == NULL || p->rHead[i]->j > j)
    {
        pt->right = p->rHead[i];
        p->rHead[i] = pt;
    }
    else
    {

        OLink q = p->rHead[i];
        while (1)
        {

            if (q->right == NULL || q->right->j > j)
            {

                pt->right = q->right;
                q->right = pt;
                break;
            }

            q = q->right;
        }
    }

    if (p->cHead[j] == NULL || p->cHead[j]->i > i)
    {

        pt->down = p->cHead[j];
        p->cHead[j] = pt;
    }
    else
    {

        OLink q = p->cHead[j];
        while (1)
        {
            if (q->down == NULL || q->down->i > i)
            {
                pt->down = q->down;
                q->down = pt;
                break;
            }

            q = q->down;
        }
    }

    p->tu++;
}
void output(CrossList *p)
{

    OLink ptemp;
    for (int i = 0; i < p->mu; i++)
    {
        ptemp = p->rHead[i];

        if (ptemp == NULL)
        {
            continue;
        }
        while (ptemp != NULL)
        {
            printf("%d %d %d\n",
                   ptemp->i,
                   ptemp->j,
                   ptemp->elem);

            ptemp = ptemp->right;
        }
    }
}


void addMatrix(CrossList *p1, CrossList *p2, CrossList *p3)
{
    OLink p1temp, p2temp;

    for (int i = 0; i < p1->mu; i++)
    {
        p1temp = p1->rHead[i];
        p2temp = p2->rHead[i];

        for (int j = 0; j < p1->nu; j++)
        {
            if (p2temp == NULL && p1temp == NULL)
            {
                break;
            }
            else if (p2temp == NULL)
            {

                while (p1temp != NULL)
                {
                    inputMatrix(p1temp->i, p1temp->j, p1temp->elem, p3);
                    p1temp = p1temp->right;
                }
                break;
            }
            else if (p1temp == NULL)
            {
                while (p2temp != NULL)
                {
                    inputMatrix(p2temp->i, p2temp->j, p2temp->elem, p3);
                    p2temp = p2temp->right;
                }
                break;
            }
            else if (p2temp->j == j && p1temp->j == j)
            {
                if (p2temp->elem + p1temp->elem != 0)
                {
                    inputMatrix(p2temp->i, p2temp->j, p2temp->elem + p1temp->elem, p3);
                }
                p2temp = p2temp->right;
                p1temp = p1temp->right;
            }
            else if (p2temp->j == j)
            {
                inputMatrix(p2temp->i, p2temp->j, p2temp->elem, p3);
                p2temp = p2temp->right;
            }
            else if (p1temp->j == j)
            {
                inputMatrix(p1temp->i, p1temp->j, p1temp->elem, p3);
                p1temp = p1temp->right;
            }
        }
    }
}

int main()
{
    char str[MAXNUM];
    cin >> str;


    addMatrix(p1, p2, p3);

    output(p3);

    return 0;
}
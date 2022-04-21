#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <cstring>
#define MAXNUM 100

using namespace std;

typedef struct OLNode
{
    int i, j;
    int elem;
    struct OLNode *right, *down;
} OLNode, *OLink;

typedef struct CrossList
{
    OLink *rHead;
    OLink *cHead;
    int mu, nu, tu;
} CrossList;

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

CrossList *initMatrix(int mu, int nu)
{
    CrossList *p = (CrossList *)malloc(sizeof(CrossList));
    assert(p != NULL);

    OLink *rHead = (OLink *)malloc(mu * sizeof(OLink));
    assert(rHead != NULL);

    OLink *cHead = (OLink *)malloc(nu * sizeof(OLink));
    assert(cHead != NULL);

    p->mu = mu;
    p->nu = nu;
    p->tu = 0;
    p->rHead = rHead;
    p->cHead = cHead;

    for (int i = 0; i < mu; i++)
    {
        p->rHead[i] = NULL;
    }

    for (int i = 0; i < nu; i++)
    {
        p->cHead[i] = NULL;
    }

    return p;
}

void inputMatrix(int i, int j, int k, CrossList *p)
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
    int mu, nu, tu1, tu2;
    scanf("%d%d%d%d", &mu, &nu, &tu1, &tu2); 
/*     mu = 3;
    nu = 4;
    tu1 = 3;
    tu2 = 2; */

    CrossList *p1 = initMatrix(mu, nu);
    CrossList *p2 = initMatrix(mu, nu);
    CrossList *p3 = initMatrix(mu, nu);

    int i, j, k;

/*     i = 1;
    j = 1;
    k = 1;
    inputMatrix(i, j, k, p1);

    i = 1;
    j = 3;
    k = 1;
    inputMatrix(i, j, k, p1);

    i = 2;
    j = 2;
    k = 2;
    inputMatrix(i, j, k, p1);

    i = 1;
    j = 2;
    k = 1;
    inputMatrix(i, j, k, p2);

    i = 2;
    j = 2;
    k = 3;
    inputMatrix(i, j, k, p2); */
    for (int m = 0; m < tu1; m++)
    {
        scanf("%d%d%d", &i, &j, &k);
        inputMatrix(i, j, k, p1);
    }

    for (int m = 0; m < tu2; m++)
    {
        scanf("%d%d%d", &i, &j, &k);
        inputMatrix(i, j, k, p2);
    }

    addMatrix(p1, p2, p3);

    output(p3);

    return 0;
}
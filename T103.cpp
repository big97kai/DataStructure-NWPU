#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#define MAXNUM 100

using namespace std;

typedef struct Triple
{
    int i, j;
    int elem;
} Triple;

typedef struct Matrix
{
    Triple data[MAXNUM];
    int mu, nu, tu;
} Matrix;

typedef struct CpotAndNum
{
    int *dataCpot;
    int *dataNum;
    int length;
} CpotAndNum;

CpotAndNum *initCpot(int size)
{
    CpotAndNum *p = (CpotAndNum *)malloc(sizeof(CpotAndNum));
    assert(p != NULL);
    p->dataCpot = (int *)malloc(sizeof(int) * size);
    assert(p->dataCpot != NULL);
    p->dataNum = (int *)malloc(sizeof(int) * size);
    assert(p->dataNum != NULL);
    p->length = size;

    return p;
}

void transposeMatrix(Matrix *M, Matrix *T, CpotAndNum *list)
{
    T->mu = M->nu;
    T->nu = M->mu;
    T->tu = M->tu;

    if (T->tu != 0)
    {
        for (int col = 0; col < list->length; ++col)
            list->dataNum[col] = 0;
        for (int row = 0; row < M->tu; ++row)
            ++list->dataNum[M->data[row].j];

        list->dataCpot[0] = 0;

        for (int col = 1; col < M->nu; ++col)
            list->dataCpot[col] = list->dataCpot[col - 1] + list->dataNum[col - 1];


        int q, col;

        for (int i = 0; i < M->tu; i++)
        {   
            col = M->data[i].j;
            q = list->dataCpot[col];
            T->data[q].i = M->data[i].j;
            T->data[q].j = M->data[i].i;
            T->data[q].elem = M->data[i].elem;
            ++list->dataCpot[col];
        }
    }
}
void output(Matrix *p)
{
    for (int k = 0; k < p->tu; k++)
    {
        printf("%d %d %d \n",
               p->data[k].i,
               p->data[k].j,
               p->data[k].elem);
    }
}
Matrix *initMatrix(int mu, int nu)
{
    Matrix *p = (Matrix *)malloc(sizeof(Matrix));
    assert(p != NULL);
    p->mu = mu;
    p->nu = nu;
    p->tu = 0;

    return p;
}

void inputMatrix(int i, int j, int k, Matrix *p)
{
    Triple *pt = (Triple *)malloc(sizeof(Triple));
    assert(pt != NULL);
    pt->i = i;
    pt->j = j;
    pt->elem = k;
    p->data[p->tu] = *pt;
    p->tu++;
}

int main()
{
    int mu, nu;
    cin >> mu >> nu;

    Matrix *p1 = initMatrix(mu, nu);
    Matrix *p2 = initMatrix(mu, nu);
    int i, j, k;
    while (1)
    {
        scanf("%d", &i);
        getchar();
        scanf("%d", &j);
        getchar();
        scanf("%d", &k);

        if (i == 0 && j == 0 && k == 0)
            break;
        else
            inputMatrix(i, j, k, p1);
    }

    CpotAndNum *list = initCpot(p1->nu);

    transposeMatrix(p1, p2, list);
    output(p2);

    return 0;
}
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

void output(Matrix *p)
{
    for (int k = 0; k < p->tu; k++)
    {
        printf("%d %d %d \n",
               p->data[k].i + 1,
               p->data[k].j + 1,
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

void inputPara(Matrix *p)
{
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
            inputMatrix(i-1, j-1, k, p);
    }
}

void productMatrix(Matrix *p1, Matrix *p2, Matrix *p3)
{
    int p1temp, p2temp, temp, col;

    int c[p3->nu];
    int num1[p1->mu];
    int rpos1[p1->mu + 1];

    int num2[p2->mu];
    int rpos2[p2->mu + 1];

    for (int k = 0; k < p1->mu; k++)
    {
        rpos1[k] = 0;
        num1[k] = 0;
    }
    for (int k = 0; k < p2->mu; k++)
    {
        rpos2[k] = 0;
        num2[k] = 0;
    }
    rpos1[p1->mu + 1] = 0;
    rpos2[p2->mu + 1] = 0;

    for (int k = 0; k < p1->tu; k++)
    {

        num1[p1->data[k].i]++;
    }

    for (int k = 1; k < p1->mu + 1; k++)
    {
        rpos1[k] = rpos1[k - 1] + num1[k - 1];
    }

    for (int k = 0; k < p2->tu; k++)
    {

        num2[p2->data[k].i]++;
    }

    for (int k = 1; k < p2->mu + 1; k++)
    {

        rpos2[k] = rpos2[k - 1] + num2[k - 1];
    }

    for (int k = 0; k < p3->nu; k++)
    {

        c[k] = 0;
    }

    if (p1->tu * p2->tu != 0)
    {
        for (int i = 0; i < p1->mu; i++)
        {
            for (p1temp = rpos1[i]; p1temp < rpos1[i + 1]; p1temp++)
            {

                temp = p1->data[p1temp].j;

                for (p2temp = rpos2[temp]; p2temp < rpos2[temp + 1]; p2temp++)
                {
                    col = p2->data[p2temp].j;
                    c[col] += p1->data[p1temp].elem * p2->data[p2temp].elem;
                }
            }

            for (int ccol = 0; ccol < p3->nu; ccol++)
            {

                if (c[ccol])
                {
                    inputMatrix(i, ccol, c[ccol], p3);
                }
            }
            for (int k = 0; k < p3->nu; k++)
            {

                c[k] = 0;
            }
        }
    }
}

int main()
{
    int mu1, nu1, mu2, nu2;

    cin >> mu1 >> nu1; 

    Matrix *p1 = initMatrix(mu1, nu1);

    inputPara(p1); 

    cin >> mu2 >> nu2;
    Matrix *p2 = initMatrix(mu2, nu2);
    inputPara(p2);

    Matrix *p3 = initMatrix(mu1, nu2);

    productMatrix(p1, p2, p3);

    output(p3);
    return 0;
}
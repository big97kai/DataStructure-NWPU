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
        cout << p->data[k].i << " " << p->data[k].j << " " << p->data[k].elem << endl;
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

void addMatrix(Matrix *p1, Matrix *p2, Matrix *p3)
{
    int i = 0, j = 0;
    Triple p1i, p2j;
    while (i < p1->tu && j < p2->tu)
    {
        p1i = p1->data[i];
        p2j = p2->data[j];

        if (p1i.i < p2j.i)
        {

            inputMatrix(p1i.i, p1i.j, p1i.elem, p3);
            i++;
        }
        else if (p1i.i > p2j.i)
        {

            inputMatrix(p2j.i, p2j.j, p2j.elem, p3);
            j++;
        }
        else
        {

            if (p1i.j == p2j.j)
            {

                if (p2j.elem + p1i.elem != 0)
                {
                    inputMatrix(p2j.i, p2j.j, p2j.elem + p1i.elem, p3);
                }
                i++;
                j++;
            }
            else if (p1i.j < p2j.j)
            {

                inputMatrix(p1i.i, p1i.j, p1i.elem, p3);
                i++;
            }
            else
            {

                inputMatrix(p2j.i, p2j.j, p2j.elem, p3);
                j++;
            }
        }
    }

    while (i < p1->tu)
    {
        inputMatrix(p1i.i, p1i.j, p1i.elem, p3);
        i++;
    }
    while (j < p2->tu)
    {
        inputMatrix(p2j.i, p2j.j, p2j.elem, p3);
        j++;
    }
}
int main()
{
    int tu1, tu2;
    cin >> tu1 >> tu2;

    Matrix *p1 = initMatrix(10, 10);
    Matrix *p2 = initMatrix(10, 10);
    Matrix *p3 = initMatrix(10, 10);

    int i, j, k;
    for (int m = 0; m < tu1; m++)
    {
        cin >> i >> j >> k;

        inputMatrix(i, j, k, p1);
    }

    for (int m = 0; m < tu2; m++)
    {
        cin >> i >> j >> k;

        inputMatrix(i, j, k, p2);
    }

    addMatrix(p1, p2, p3);

    output(p3);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct G
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

// 初始化十字链表
CrossList *initMatrix(int mu, int nu)
{
    CrossList *p = (CrossList *)malloc(sizeof(CrossList));
    assert(p != NULL);

    OLink *rHead = (OLink *)malloc(mu * sizeof(OLink));
    assert(rHead != NULL);

    OLink *cHead = (OLink *)malloc(nu * sizeof(OLink));
    assert(cHead != NULL);
    //初始化各个数据
    p->mu = mu;
    p->nu = nu;
    p->tu = 0;
    p->rHead = rHead;
    p->cHead = cHead;

    // 习惯了 都初始化一下 心理舒服
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

    //行输入，如果行是空的，或者第一个值比输入节点大
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
            // 向下搜索哪个节点的值比输入节点大
            if (q->right == NULL || q->right->j > j)
            {

                pt->right = q->right;
                q->right = pt;
                break;
            }

            q = q->right;
        }
    }

    //列插入，逻辑和行插入一样
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

CrossList *addCrossList(CrossList *a, CrossList *b)
{

    int i;
    OLink temp1, temp2;

    for (i = 0; i < a->mu; i++)
    {
        //如果b这一行是空的
        if (b->rHead[i] == NULL)
        {
            continue;
        }
        else
        {
            // a这一行没有数据，把b复制过来
            if (a->rHead[i] == NULL)
            {
                a->rHead[i] = b->rHead[i];
            }
            // a b都有数据
            else
            {
                temp1 = a->rHead[i]; //遍历a
                temp2 = b->rHead[i]; //遍历b
                while (1)
                {
                    if (temp2->j == temp1->j)
                    {
                        temp1->elem = temp1->elem + temp2->elem;
                        if (temp1->elem == 0) //相加为0,删去此节点
                        {
                            OLink pp = a->rHead[i];
                            OLink pd = a->cHead[temp1->j];

                            while (pp->right != temp1)
                            {
                                pp = pp->right;
                            }
                            pp->right = temp1->right;

                            while (pd->down != temp1)
                            {
                                pd = pd->down;
                            }
                            pd->down = temp1->down;
                        }
                        temp1 = temp1->right;
                        temp2 = temp2->right;
                    }
                    else
                    {
                        // a列小
                        if (temp1->j < temp2->j)
                        {
                            temp1 = temp1->right;
                        }
                        else
                        {
                            // a列大
                            inputMatrix(temp2->i, temp2->j, temp2->elem, a);
                            temp2 = temp2->right;
                        }
                    }
                    if (temp2 == NULL)
                        break;
                    if (temp1 == NULL)
                    {
                        temp1->right = temp2;
                        break;
                    }
                }
            }
        }
    }

    return a;
}

// 输出矩阵
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
int main()
{
    int mu, nu, tu1, tu2;
    scanf("%d%d%d%d", &mu, &nu, &tu1, &tu2);

    CrossList *p1 = initMatrix(mu, nu);
    CrossList *p2 = initMatrix(mu, nu);

    int i, j, k;

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

    p1 = addCrossList(p1, p2);

    output(p1);

    return 0;
}

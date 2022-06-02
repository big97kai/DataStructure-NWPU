#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge
{
    int weight[100][100];
} Edge, *PEdge;

typedef struct Smatrix
{
    int weight[100][100];
} Smatrix, *PSmatrix;

typedef struct Node
{
    int before;
    int already_in_list;
    int nearest_edge;
} Node, *PNode;

// 初始化矩阵
PEdge init_edge()
{
    PEdge edge = (PEdge)malloc(sizeof(Edge));
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {

            edge->weight[i][j] = 10000;
        }
    }
    return edge;
}

// 输入矩阵
void input_edge(PEdge edge, int size)
{

    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            scanf("%d", &edge->weight[j][i]);
        }
    }
}

PSmatrix init_smitrix(PEdge edge)
{
    PSmatrix edge2 = (PSmatrix)malloc(sizeof(Smatrix));
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (edge->weight[i][j] == 10000)
            {
                edge2->weight[i][j] = -1;
            }
            else
            {
                edge2->weight[i][j] = j;
            }
        }
    }
    return edge2;
}

void compute(int size, PEdge edge, PSmatrix smatrix)
{
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (edge->weight[i][k] + edge->weight[k][j] < edge->weight[i][j])
                {
                    edge->weight[i][j] = edge->weight[i][k] + edge->weight[k][j];
                    smatrix->weight[i][j] = k;
                }
            }
        }
    }
}

void computoutput(PEdge edge, PSmatrix smatrix, int number, int *first, int *last, int size)
{
    int in, out;
    for (int i = 0; i < number; i++)
    {
        in = first[i];
        out = last[i];
        printf("%d\n", in);
        while (smatrix->weight[in][out] != out)
        {
            printf("%d\n", smatrix->weight[in][out]);
            in = smatrix->weight[in][out];
        }
        printf("%d\n", out);
    }
}
int main(void)
{
    int size, number;
    scanf("%d", &size);
    PEdge edge = init_edge();
    input_edge(edge, size);
    PSmatrix smatrix = init_smitrix(edge);
    
    scanf("%d", &number);
    int first[number];
    int last[number];
    for (int i = 0; i < number; i++)
    {
        scanf("%d", &first[i]);
        scanf("%d", &last[i]);
    }

    compute(size, edge, smatrix);
    computoutput(edge, smatrix, number, first, last, size);
    return 0;
}
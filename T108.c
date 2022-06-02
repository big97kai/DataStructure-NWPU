#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge
{
    int weight[100][100];
} Edge, *PEdge;

PEdge init_dege()
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

int find_smallest(int *nearest_edge, int size, int *already_have)
{
    int smlles = 0;
    for (int i = 1; i < size; i++)
    {

        if (already_have[i] == 0 && (nearest_edge[smlles] == 0 || nearest_edge[i] < nearest_edge[smlles]))
        {
            smlles = i;
        }
    }
    return smlles;
}

void renew(PEdge edge, int *nearest_edge, int *already_have, int size, int node, int neighbour)
{
    if (already_have[neighbour] == 1 || node == neighbour)
    {
        return;
    }

    if (nearest_edge[neighbour] > nearest_edge[node] + edge->weight[node][neighbour])
    {
        nearest_edge[neighbour] = nearest_edge[node] + edge->weight[node][neighbour];
    }
}

void compute(PEdge edge, int *output, int size)
{
    int already_have[size]; // 已经计算好长度的集合
    for (int i = 0; i < size; i++)
    {
        already_have[i] = 0;
    }
    output[0] = 0;

    int nearest_edge[size]; //相对于已选边的最短路径；
    nearest_edge[0] = 0;
    for (int i = 1; i < size; i++)
    {
        nearest_edge[i] = 10000;
    }

    int current = 0;
    int flag = 1;
    while (flag != 0)
    {
        for (int i = 1; i < size; i++)
        {
            renew(edge, nearest_edge, already_have, size, current, i);
        }
        already_have[current] = 1;
        current = find_smallest(nearest_edge, size, already_have);
        output[current] = nearest_edge[current];
        flag = current;
    }
}

int main(void)
{

    int size;
    scanf("%d", &size);
    PEdge edge = init_dege();
    input_edge(edge, size);

    int output[size];
    compute(edge, output, size);

        for (int i = 0; i < size; i++)
        {

            printf("%d\n", output[i]);
        }
    return 0;
}
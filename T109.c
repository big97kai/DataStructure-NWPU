#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge
{
    int weight[100][100];
} Edge, *PEdge;

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

// 初始化节点
PNode init_node(int size)
{
    // 初始化
    PNode node_list = (Node *)malloc(sizeof(Node) * size); // node的序列，
    for (int i = 0; i < size; i++)
    {
        node_list[i].already_in_list = 0;
        node_list[i].before = -1;
        node_list[i].nearest_edge = 10000;
    }

    return node_list;
}
// 寻找此时节点列表中距离已经选中节点最短的那一个
int find_smallest(int size, Node *node_list, int first)
{
    int smlles = first;
    for (int i = 0; i < size; i++)
    {
        if (node_list[i].already_in_list == 0 && (node_list[smlles].nearest_edge == 0 || node_list[i].nearest_edge < node_list[smlles].nearest_edge))
        {
            smlles = i;
        }
    }
    return smlles;
}

// 更新算法
void renew(PEdge edge, Node *node_list, int size, int node, int neighbour)
{
    // 如果neighbour 已经选中节点，或者node == neibour 返回， 不用计算
    if (node_list[neighbour].already_in_list == 1 || node == neighbour)
    {
        return;
    }

    // 如果从原点到neibour距离大于 原点经过node到neighbour距离，更新
    if (node_list[neighbour].nearest_edge > node_list[node].nearest_edge + edge->weight[node][neighbour])
    {
        node_list[neighbour].nearest_edge = node_list[node].nearest_edge + edge->weight[node][neighbour];
        node_list[neighbour].before = node;
    }
}
// 主要算法，计算各个节点最短路径
void compute(int first, PEdge edge, Node *node_list, int size)
{
    // 初始节点
    node_list[first].nearest_edge = 0;
    int current = first;
    int flag = 1;
    while (flag != 0)
    {
        // 更新距离选中节点的未选节点的距离
        for (int i = 0; i < size; i++)
        {
            renew(edge, node_list, size, current, i);
        }
        node_list[current].already_in_list = 1;
        // 选中最短的一个
        current = find_smallest(size, node_list, first);
        // 如果已经全部选中，则此时current = first
        if(current == first)
        {
            flag = 0;
        }
    }
}
/**
 * @brief 输出结果
 * 
 * @param node_list 
 * @param size 
 * @param first 
 */
void computoutput(Node *node_list, int size, int final, int first)
{
    // 因为是逆反顺序输出，所以需要用一个临时列表，再反序输出
    int current = final;
    int output[100];
    int i = 0;
    // 输入到临时列表中
    while(current != first)
    {
        output[i] = current;
        i++;
        current = node_list[current].before;
    }
    output[i] = current;
    // 输出
    for(; i >=0 ; i--)
    {
        printf("%d\n", output[i]);
    }
}
int main(void)
{
    int size, first, final;
    scanf("%d", &size);
    PEdge edge = init_edge();
    input_edge(edge, size);
    scanf("%d", &first);
    scanf("%d", &final);
    PNode node_list = init_node(size);
    compute(first ,edge, node_list, size);
    computoutput(node_list, size, final, first);
    return 0;
}
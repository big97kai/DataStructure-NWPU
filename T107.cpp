
#include <string>
#include <iostream>
#define MAXNUM 100

using namespace std;

typedef struct HuffNode
{
    int weight;
    int parent;
    int Lchild;
    int Rchild;
} HuffNode;

HuffNode *init_huffmantree(int *weight, int size, char *node, HuffNode *tree);
int select(HuffNode *tree, int size);
void construct_huffmantree(HuffNode *tree, int size);
int getcode(int codesize, HuffNode *tree, int *codetrans, int *num);
void transmit(char chars[], string code, int num[], int charsize, int codesize);
int getreversecode(int size, char *reversecodetrans, int sizeOfCode, HuffNode *tree, int *codetrans, char* node);;
void output(int sizeOfcode, int sizeOfdecode, int* codetrans, char* reversecodetrans);

int main(void)
{
    char node[MAXNUM];
    int weight[MAXNUM];
    int codetrans[MAXNUM];
    char reversecodetrans[MAXNUM];
    int num[MAXNUM];
    string input;
    int size;

    cin >> size;

    for (int i = 0; i < size; i++)
    {
        cin >> node[i];
    }
    for (int i = 0; i < size; i++)
    {
        cin >> weight[i];
    }
    cin >> input;
/*          size = 5;
        char node[] = {'a' ,'b', 'c', 'd', 'e'};
        int weight[] = {12, 40, 15, 8, 25};
        input = "bbbaddeccbbb"; */
    HuffNode tree[2 * size - 1];
    HuffNode *tree2 = init_huffmantree(weight, size, node, tree);
    construct_huffmantree(tree2, size);
    transmit(node, input, num, size, input.size());
    int sizeOfcode = getcode(input.size(), tree2, codetrans, num);
    int sizeOfdecode = getreversecode(size, reversecodetrans, sizeOfcode, tree2, codetrans, node);
    output(sizeOfcode, sizeOfdecode, codetrans, reversecodetrans);
}

void print(int size, HuffNode *tree)
{

    for (int i = 0; i < size; i++)
    {
        cout << tree[i].weight << ' ' << tree[i].parent
             << ' ' << tree[i].Lchild << ' ' << tree[i].Rchild << endl;
    }
}

HuffNode *init_huffmantree(int *weight, int size, char *node, HuffNode *tree)
{
    for (int i = 0; i < size; i++)
    {

        HuffNode *p = (HuffNode *)malloc(sizeof(HuffNode));
        p->weight = weight[i];
        p->parent = 0;
        p->Lchild = 0;
        p->Rchild = 0;
        tree[i] = *p;
    }
    return tree;
}

int select(HuffNode *tree, int size)
{
    int temp = -1;
    int pos;

    for (int i = 0; i < size; i++)
    {
        if (tree[i].parent == 0 && (tree[i].weight < temp || temp == -1))
        {
            temp = tree[i].weight;
            pos = i;
        }
    }
    return pos;
}

void construct_huffmantree(HuffNode *tree, int size)
{
    int i = 0;
    int first, second;
    while (i < size - 1)
    {
        int first = select(tree, size + i);
        tree[first].parent = size + i;
        int second = select(tree, size + i);
        tree[second].parent = size + i;
        tree[size + i].Lchild = first;
        tree[size + i].Rchild = second;
        tree[size + i].parent = 0;
        tree[size + i].weight = tree[first].weight + tree[second].weight;
        i++;
    }
}

void transmit(char chars[], string code, int num[], int charsize, int codesize) //将目标报文按照给定的字符对应关系转化为数组
{
    int i, j;
    for (i = 0; i < codesize; i++) //遍历目标报文的每一个字符
    {
        for (j = 0; j < charsize; j++) //查找字符与数字的对应关系，然后转化为数字
        {
            if (code[i] == chars[j])
            {
                num[i] = j;
                break;
            }
        }
    }
}

int getcode(int codesize, HuffNode *tree, int *codetrans, int *num) //编码
{
    int par, cur, posOfTemp;
    int posOfCodetrans = 0;
    int temp[MAXNUM];
    for (int j = 0; j < codesize; j++)
    {
        par = tree[num[j]].parent;
        cur = num[j];
        posOfTemp = 0;
        while (par != 0)
        {
            if (tree[par].Lchild == cur)
            {
                temp[posOfTemp] = 0;
            }
            else
            {
                temp[posOfTemp] = 1;
            }
            posOfTemp++;
            cur = par;
            par = tree[cur].parent;
        }
        posOfTemp--;
        while (posOfTemp >= 0)
        {

            codetrans[posOfCodetrans] = temp[posOfTemp];
            posOfTemp--;
            posOfCodetrans++;
        }
    }

    return posOfCodetrans;
}

int getreversecode(int size, char *reversecodetrans, int sizeOfCode, HuffNode *tree, int *codetrans, char* node) //对目标编码进行解码，得到解码后的报文
{
    int root;
    int j=0;
    for (int j = 0; j < 2 * size - 1; j++)
    {
        if (tree[j].parent == 0)
        {

            root = j;
        }
    }
    int posOfCode = 0;
    while (posOfCode < sizeOfCode)
    {
        int parent = root;
        while (tree[parent].Lchild != 0 || tree[parent].Rchild != 0)
        {
            if (codetrans[posOfCode] == 0)
            {
                parent = tree[parent].Lchild;
            }
            else
            {
                parent = tree[parent].Rchild;
            }
            posOfCode++;
        }
        reversecodetrans[j] = node[parent];
        j++;
    }

    return j;
}
void output(int sizeOfcode, int sizeOfdecode, int* codetrans, char* reversecodetrans) //输出编码
{
    for(int i=0; i<sizeOfcode; i++){

        cout << codetrans[i];
    }

    printf("\n");

    for(int i=0; i<sizeOfdecode; i++){

        cout << reversecodetrans[i];
    }
}

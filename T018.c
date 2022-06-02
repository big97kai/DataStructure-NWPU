#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bintree
{
    struct Bintree *lchild;
    struct Bintree *rchild;
    char data;
} Bintree, *PBintree;

PBintree construct_tree(char *input_first, char *input_second, int *already_in_tree, int loc_of_first, int total);
void print_tree(PBintree tree);

int main(void)
{
    char input_first[100];
    char input_second[100];
    int already_in_tree[100];
    for (int i = 0; i < 100; i++)
    {

        already_in_tree[i] = 0;
    }
    scanf("%s", &input_first);
    getchar();
    scanf("%s", &input_second);
    getchar();

    int len = strlen(input_first);

    PBintree tree = construct_tree(input_first, input_second, already_in_tree, 0, len);

    print_tree(tree);

    return 0;
}

/**
 * @brief 找到对应的先序序列中某个char对应的中序的位置。则此中徐之前的为左孩子，中序之后为右孩子
 *
 * @param input_first
 * @param input_second
 * @param len
 * @param loc
 * @return int
 */
int find_divide_in_second(char *input_first, char *input_second, int loc_of_first, int len)
{

    for (int i = 0; i < len; i++)
    {
        if (input_first[loc_of_first] == input_second[i])
        {
            return i;
        }
    }

    return -1; // 不可能输出-1
}

/**
 * @brief 找到此时左孩子有几个，如果个数为0，说明此节点为叶子节点
 * 
 * @param already_in_tree 
 * @param pos 
 * @return int 
 */
int find_number_of_left(int *already_in_tree, int pos)
{
    int sum = 0;
    for (int i = pos - 1; i >= 0; i--)
    {
        if(already_in_tree[i] == 1)
        {
            break;
        }
        sum++;
    }

    return sum;
}

/**
 * @brief 找到此时右孩子有几个，如果个数为0，说明此节点为叶子节点
 * 
 * @param already_in_tree 
 * @param pos 
 * @param len 
 * @return int 
 */
int find_number_of_right(int *already_in_tree, int pos, int len)
{
    int sum = 0;
    for (int i = pos + 1; i < len; i++)
    {
        if(already_in_tree[i] == 1)
        {
            break;
        }
        sum++;
    }

    return sum;
}

/**
 * @brief 主函数
 * 
 * @param input_first 
 * @param input_second 
 * @param already_in_tree 
 * @param loc_of_first 
 * @param total 
 * @return PBintree 
 */
PBintree construct_tree(char *input_first, char *input_second, int *already_in_tree, int loc_of_first, int total)
{
    // 构建新的节点
    PBintree node = (PBintree)malloc(sizeof(Bintree));

    node->data = input_first[loc_of_first];
    node->lchild = NULL;
    node->rchild = NULL;

    // 找到此时对应的中序节点
    int divid_node_of_second = find_divide_in_second(input_first, input_second, loc_of_first, total);
    // 此节点此时已经输入树中
    already_in_tree[divid_node_of_second] = 1;
    // 左孩子数量
    int number_of_left = find_number_of_left(already_in_tree, divid_node_of_second);
    // 右孩子数量
    int number_of_right = find_number_of_right(already_in_tree, divid_node_of_second, total);
    // 递归构造
    if(number_of_left != 0){

        node->lchild = construct_tree(input_first, input_second, already_in_tree, loc_of_first + 1, total);
    }

    if(number_of_right != 0){

        node->rchild = construct_tree(input_first, input_second, already_in_tree, loc_of_first + number_of_left + 1, total);
    }
    return node;
}

void print_tree(PBintree tree)
{
    if(tree != NULL){

        print_tree(tree->lchild);
        print_tree(tree->rchild);
        printf("%c", tree->data);
    }
}
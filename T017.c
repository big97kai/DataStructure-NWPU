#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bintree
{
    struct Bintree *lchild;
    struct Bintree *rchild;
    char data;
} Bintree, *PBintree;

//因为先须便利， 自定义一个栈
typedef struct Stack
{
    Bintree _list[1000];
    int bottom;
    int top;
} Stack, *PStack;

// init stack
PStack _init_stack()
{
    PStack temp = (PStack)malloc(sizeof(Stack));
    temp->bottom = 0;
    temp->top = 0;
    return temp;
}
// pop of stack
void push(PStack stack, PBintree tree)
{
    if(tree == NULL){

        return;
    }
    stack->_list[stack->top] = *tree;
    stack->top++;
}

// push of stack

PBintree pop(PStack stack)
{
    if(stack->top != stack->bottom){
        stack->top--;
        return &stack->_list[stack->top];
    }

    printf("error!");
    return (PBintree)NULL;
}
// 初始化节点
PBintree init_list()
{
    PBintree list = (PBintree)malloc(sizeof(Bintree));
    list->data = NULL;
    list->lchild = NULL;
    list->rchild = NULL;

    return list;
}

char c;
// 因为是先序遍历，所以先注入此节点，后左右
PBintree creat_tree()
{

    c = getchar();

    if (c == '#')
    {

        return NULL; //到达叶子节点 返回
    }
    else
    {
        PBintree list = init_list();
        list->data = c;

        list->lchild = creat_tree();
        list->rchild = creat_tree();
        return list;
    }
}

// 核心是将先序遍历转换成中序遍历
void first_print_tree(PBintree tree, PStack stack)
{
    PBintree x;
    if(tree != NULL){
        push(stack, tree);

        while(stack->top != 0){

            x = pop(stack);
            printf("%c", x->data);
            push(stack, x->rchild);
            push(stack, x->lchild);
        }
    }
}
// 只要到某个节点，先找其所有的左孩子
void go_along_left(PBintree tree, PStack stack){

    while(tree != NULL){

        push(stack, tree);
        tree = tree->lchild;
    }
}
// 中序遍历，藤蔓结构是无论到什么节点，都现到此节点的最左侧的节点，然后读取自身，转向右儿子，在向上到左侧的节点
void middle_print_tree(PBintree tree, PStack stack)
{
    PBintree x = tree;
    if(tree != NULL){

        while(1){

            // 找到其所有的左孩子，压入栈
            go_along_left(x, stack);
            // 结束
            if(stack->top == 0){

                break;
            }
            // 找到最左的左孩子
            x = pop(stack);
            printf("%c", x->data);
            // 进入右子树
            x = x->rchild;
        }

    }
}

int main()
{

    PBintree list = creat_tree();
    PStack stack = _init_stack();
    middle_print_tree(list, stack);
    return 0;
}

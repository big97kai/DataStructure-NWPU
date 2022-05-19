#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bintree
{
    struct Bintree *lchild;
    struct Bintree *rchild;
    char data;
} Bintree, *PBintree;

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

// count个数
int count_tree(PBintree list)
{

    if (list == NULL)
    {

        return 0;
    }
    if (list->lchild == NULL && list->rchild == NULL)
    {
        return 1;
    }

    return count_tree(list->lchild) + count_tree(list->rchild);
}
int main()
{

    PBintree list = creat_tree();
    printf("%d", count_tree(list));

    return 0;
}

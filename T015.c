#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bintree
{
    struct Bintree *lchild;
    struct Bintree *rchild;
    char data;
}Bintree, *PBintree;

// 初始化节点
PBintree init_list()
{
    PBintree list = (PBintree) malloc (sizeof(Bintree));
    list->data = NULL;
    list->lchild = NULL;
    list->rchild = NULL;

    return list;
}

int loc = 0;

void creat_tree(PBintree list, char* str){

    if(str[loc] != NULL){

        if(str[loc] == '#'){

            // �����ݣ���������ݣ��˽ڵ����
            list->data = str[loc];
            loc++;
            return;
        }else{

            list->data = str[loc];
            loc++; //ȥ�����Ų��ж�

            if(str[loc] == '('){

                loc++;
                // ����������������������
                list->lchild = init_list();
                creat_tree(list->lchild, str);
                loc++; //ȥ������
                list->rchild = init_list();
                creat_tree(list->rchild, str);
                loc++;
                return;
            }else{

                return;
            }
        }
    }
}



// �ݹ���ʽ���������
void print_tree(PBintree list){

    if(list == NULL){

        return;
    }

    printf("%c", list->data);
    print_tree(list->lchild);
    print_tree(list->rchild);
}
int main()
{

    char str[100];
    scanf("%s", str);
    PBintree list = init_list();
    creat_tree(list, str);
    print_tree(list);

    return 0;
}

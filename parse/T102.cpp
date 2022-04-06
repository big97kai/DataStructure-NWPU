#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief 定义数据结构
 * 
 */
typedef struct DoubleNode{

    int value; 
    struct DoubleNode *next, *before;
}DoubleNode, *PDoubleNode;

typedef struct DLinkList{

    PDoubleNode head;
    PDoubleNode tail;
    int length;
}DLinkList, *PDLinkList;

/**
 * @brief 初始化node数据结构
 * 
 * @param n 
 * @return PDoubleNode 
 */
PDoubleNode init_DoubleNode(int n){

    PDoubleNode p;
    PDoubleNode list2;
    PDoubleNode list = (PDoubleNode) malloc (sizeof(DoubleNode));
    assert(list != NULL);
    p = list;
    list -> value = 1;
    list -> next = NULL;
    list -> before = NULL;

    for(int i=1; i<n+1; i++){

        list2 = (PDoubleNode) malloc (sizeof(DoubleNode));
        assert(list2 != NULL);
        list2 -> value = 0;
        list2 -> next = NULL;
        list2 -> before = NULL;

        list -> next = list2;
        list2->before = list;
        list = list->next;
    }
    p->before = list2;
    list2->next = p;
    return p;
}

/**
 * @brief  初始化链表
 * 
 * @param n 
 * @return PDLinkList 
 */
PDLinkList init_PDLinkList(int n){

    PDLinkList list = (PDLinkList) malloc (sizeof(DLinkList));
    assert(list != NULL);

    list->length = n;
    list->head = init_DoubleNode(list->length);
    list->tail = list->head->before;

    return list; 
}

int precision;
int termN;

PDLinkList listOfPi;

/**
 * @brief 记录输入 并且 计算k的数字
 * 
 */
void get_input(){

    cin >> precision;
    double temp = 0;
    termN = 1;

    while(temp < precision + 1){

        temp += log10((2 * termN + 1) / termN);
        termN++;
    }
}

/**
 * @brief 大数乘法 对10取余数， 落入本位 对10取整数进行进位
 * 
 * @param list 
 * @param n 
 */
void bigMul(PDLinkList list, int n){

    PDoubleNode p = list->tail;

    int carry = 0;
    int present;
    
    do{

        present = p->value * n + carry;
        carry = present / 10;
        present = present % 10;
        p->value = present;
        p = p->before;
    }while(p != list->tail);
}

/**
 * @brief 大数除法，从head开始，本位/k落入本位，余数*10并入下一位
 * 
 * @param list 
 * @param n 
 */
void bigDiv(PDLinkList list, int n){

    PDoubleNode p = list->head;

    int carry = 0;
    int present;
    
    do{

        present = carry * 10 + p->value;
        carry = present % n;
        p->value = present / n;
        p = p->next;
    }while(p != list->head);
}

/**
 * @brief 依据大数乘法和除法进行计算pi
 * 
 */
void computePi(){

    for(int i=termN; i>0; i--){

        bigDiv(listOfPi, 2 * i + 1);
        bigMul(listOfPi, i);

        listOfPi->head->value += 2; 
    }
}

/**
 * @brief 输出
 * 
 */
void printDLList(){

    PDoubleNode p = listOfPi->head;
    printf("%d", p->value);
    p = p->next;
    printf(".");
    int temp = 0;
    while(temp < precision){

        printf("%d", p->value);
        p = p->next;
        temp++;
    }
    printf("\n");
}
/**
 * @brief free linked list;
 * 
 */
void deleteList(){

    PDoubleNode p = listOfPi->head;
    PDoubleNode q;
    while(p != listOfPi->head){

        q = p;
        p = p->next;
        free(q);
    }

    free(listOfPi);
}
int main(){

    get_input();
    listOfPi = init_PDLinkList(500);

    computePi();
    printDLList();
    deleteList();
    return 0;
}





#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>

using namespace std;

/**
 * @author yikaiyang
 * @version 1.00
 * 
 * practice for linear-list
 * 
 */

typedef struct linear_list{

    int length;
    int* data;
    int size;
}linear_list;

int size[2];
linear_list* list1;
linear_list* list2;
linear_list* list3;

/**
 * @brief 创建链表
 * 
 * @param list 
 * @return vector_t* 
 */
linear_list* creatNullList_seq(linear_list* list){

    list = (linear_list*)malloc(sizeof(linear_list));
    list -> data = (int*) malloc (sizeof(int) * 100);
    assert(list -> data != NULL);
    list -> length = 0;
    list -> size = 100;
    return list;
}

/**
 * @brief 向链表中输入值
 * 
 * @param list 
 */
void input_list(linear_list* list, int k){

    for(int i=0; i<k; i++){

        cin >> list->data[i];
        assert(list->length < list->size);
        list->length++;
    }
}

/**
 * @brief 输入 并且初始化链表
 * 
 * 
 */
void get_input_list(int n){

    cin >> size[n];

    if(n == 1){

        list1 = creatNullList_seq(list1);
        input_list(list1, size[n]);
    }else{

        list2 = creatNullList_seq(list2);
        input_list(list2, size[n]);
    }
}

/**
 * @brief 将数字放入到链表末尾
 * 
 * @param list 
 * @param number 
 * 
 */
void insert_seq(linear_list* list, int number){

    if(list->length >= list->size){

        fprintf(stderr, "no space \n");
        exit(1);
    }

    list->data[list->length] = number;
    list->length++;
}

/**
 * @brief get the nth number in list
 * 
 * @param list 
 * @param n 
 * @return int 
 */
int retrive_seq(linear_list* list, int n){

    if(n >= list->length){

        fprintf(stderr, "out of space \n");
        exit(1);
    }
    return list->data[n];
}

/**
 * @brief 将list1， list2中的数字按照顺序放入list3中
 * 
 * @param list1 
 * @param list2 
 * @param list3 
 */
void mergeLists_seq(linear_list* list1, linear_list* list2, linear_list* list3){

    int po_a = 0;
    int po_b = 0;
    int item_x;
    int item_y;
    while(po_a < list1->length && po_b < list2->length){
	//获得list1， list2中最小的数字
        item_x = retrive_seq(list1, po_a);
        item_y = retrive_seq(list2, po_b);
	//进行比较，将更小的放入list3中， 并将提取的数字位置下移一位
        if(item_x < item_y){

            insert_seq(list3, item_x);
            po_a++;
        }else{

            insert_seq(list3, item_y);
            po_b++;
        }
    }
	//将剩余的数字放入list3中
    while(po_a < list1->length){

        item_x = retrive_seq(list1, po_a);
        insert_seq(list3, item_x);
        po_a++;
    }

    while(po_a < list1->length){

        item_y = retrive_seq(list1, po_b);
        insert_seq(list3, item_y);
        po_b++;
    }
}

/**
 * @brief free all list
 * 
 */
void delete_list(){

    free(list1);
    free(list2);
    free(list3);
}
/**
 * @brief print value in list
 * 
 * @param list 
 */
void output(linear_list* list){

    for(int i=0; i<list->length; i++){

        printf("%d", list->data[i]);
        printf("\n");
    }
}

int main(){

    get_input_list(0);
    get_input_list(1);

    list3 = creatNullList_seq(list3);

    mergeLists_seq(list1, list2, list3);

    output(list3);

    delete_list();
    return 0;
}

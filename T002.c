#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// kai

//form the struct of linear list
typedef struct vector_t{
    int length;
    int* data;
    int size;
}vector_t;

//form the struct of linked list
typedef struct vector_t2{
    int value;
    struct vector_t2 *next;
}vector_t2;

//init linear list
vector_t* init_list1(){

    vector_t* lsit;
    lsit = (vector_t*)malloc(sizeof(vector_t));
    lsit -> data = (int*) malloc (sizeof(int) * 100);
    assert(lsit -> data != NULL);
    lsit -> length = 0;
    lsit -> size = 100;
    return lsit;
}

//init linked list
vector_t2* init_list2(){

    vector_t2* p;

    vector_t2* list = (vector_t2*) malloc (sizeof(vector_t2));
    assert(list != NULL);
    p = list;
    list -> value = 0;
    list -> next = NULL;

    for(int i=1; i<100; i++){

        vector_t2* list2 = (vector_t2*) malloc (sizeof(vector_t2));
        list2 -> value = i;
        list2 -> next = NULL;

        list -> next = list2;
        list = list->next;
    }

    return p;
}

// reverse linear list
void reverse(vector_t* vector_t){

    int a = 0;
    int b = vector_t -> length-1;

    int temp;

    while(a < b){

        temp = vector_t -> data[a];
        vector_t -> data[a] = vector_t -> data[b];
        vector_t -> data[b] = temp;
        a++;
        b--;
    }
}

//reverse linked list
vector_t2* reverse2(vector_t2* list2, int a){

    vector_t2* temp;
    vector_t2* temp2;

    temp = NULL;
    temp2 = NULL;
    int tempnumber = 0;
    while(tempnumber < a){

        temp2 = list2 ->next;

        list2 -> next = temp;
        temp = list2;
        list2 = temp2;
        tempnumber++;
    }

    return temp;
}


int main(){

    //input and init linear list and linked list
    int size;

    scanf("%d", &size);

    vector_t* list1 = init_list1();
    vector_t2* list2 = init_list2();

    vector_t2* temp = list2;

    int temp2 = 0;
    list1 -> length = 0;
    while(temp2 < size){

        scanf("%d", &(list1 -> data[temp2]));
        list1 -> length ++;
        temp2++;
    }

    temp2 = 0;
    while(temp2 < size){

        temp -> value = list1 -> data[temp2];
        temp = temp -> next;
        temp2++;
    }

    //reverse these two list
    temp = list2;
    reverse(list1);
    list2 = reverse2(list2, size);

    temp2 = 0;
    // output
    while(temp2 < size){

        printf("%d ", list1->data[temp2]);
        temp2++;
    }
    printf("\n");
    while(list2 != NULL){

        printf("%d ", list2->value);
        list2 = list2 -> next;
    }
    printf("\n");

    free(list1 -> data);
    free(temp);
    return 0;
}
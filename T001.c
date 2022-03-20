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

// init the linear list
vector_t* init_list1(){

    vector_t* lsit;
    lsit = (vector_t*)malloc(sizeof(vector_t));
    lsit -> data = (int*) malloc (sizeof(int) * 100);
    assert(lsit -> data != NULL);
    lsit -> length = 0;
    lsit -> size = 100;
    return lsit;
}

//insert the number into the linear list
void temprature(int number, vector_t* list){

    //find the location of the number
    int first =0;

    while(list->data[first] < number){

        first++;
    }

    //insert the number
    int temp = list->data[first];
    while(first <= list->length){

        list->data[first] = number;
        number = temp;
        first++;
        temp = list->data[first];
    }

    list->length++;
}
int main(){

    //init list and input
    vector_t* list = init_list1();
    int c;
    scanf("%d", &list->length);
    int temp = 0;
    while(temp < list->length){

        scanf("%d", &list->data[temp]);
        temp++;
    }
    scanf("%d", &c);

    // insert the number
    temprature(c, list);

    temp = 0;

    //ouput
    while(temp < list->length){

        printf("%d ", list->data[temp]);
        temp++;
    }

    return 0;
}
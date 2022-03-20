#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// kai

// form the struct of the linear list
typedef struct vector_t{
    int length;
    int* data;
    int size;
}vector_t;

// init linear list
vector_t* init_list1(){

    vector_t* lsit;
    lsit = (vector_t*)malloc(sizeof(vector_t));
    lsit -> data = (int*) malloc (sizeof(int) * 100);
    assert(lsit -> data != NULL);
    lsit -> length = 0;
    lsit -> size = 100;
    return lsit;
}

int size[3];

vector_t* list1;
vector_t* list2;
vector_t* list3;

// input the list
void listinput(vector_t* list, int n){

    for(int i=0;i<n;i++){

        scanf("%d", &(list->data[i]));
    }

    list->length = n;
}

// the full init and input
void innitinput(){

    for(int i=0;i<3;i++){

        scanf("%d", &(size[i]));
    }

    list1 = init_list1();
    list2 = init_list1();
    list3 = init_list1();

    listinput(list1, size[0]);
    listinput(list2, size[1]);
    listinput(list3, size[2]);

}

//find the number in list2 and delete if from list1
void algorithm(vector_t* list1, vector_t* list2){

    for(int i=0; i<list2->length; i++){

        for(int j=0; j<size[0]; j++){

            if(list2->data[i] > list1->data[size[0]-1]){

                break;
            }
            if(list1->data[j] == list2->data[i]){

                list1->data[j] = -1;
            }else if(list1->data[j] > list2->data[i]){

                break;
            }
        }
    }
}

// find the shared number in list1 and list2
vector_t* algorithm1(vector_t* list1, vector_t* list2){

    vector_t* list3;
    list3 = init_list1();

    for(int i=0; i<list2->length; i++){

        for(int j=0; j<list1->length; j++){

            if(list2->data[i] > list1->data[list1->length-1]){

                break;
            }
            if(list1->data[j] == list2->data[i]){

                list3->data[list3->length] = list1->data[j];
                list3->length++;
                break;
            }else if(list1->data[j] > list2->data[i]){

                break;
            }
        }
    }

    return list3;
}

int main(){

    innitinput();
    vector_t* list4 = algorithm1(list2, list3);
    algorithm(list1, list4);

    //output
    for(int i=0; i<size[0]; i++){

        if(list1->data[i] != -1){

            printf("%d ", list1->data[i]);
        }
    }
    printf("\n");
    return 0;
}
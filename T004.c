#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// kai

// form the struct of the linked list
typedef struct vector_t2{
    int value;
    struct vector_t2 *next;
}vector_t2;

// init the list
vector_t2* init_list2(int n){

    vector_t2* p=NULL;

    vector_t2* list = (vector_t2*) malloc (sizeof(vector_t2));
    assert(list != NULL);
    p = list;
    list -> value = 0;
    list -> next = NULL;

    for(int i=1; i<n; i++){

        vector_t2* list2 = (vector_t2*) malloc (sizeof(vector_t2));
        list2 -> value = i;
        list2 -> next = NULL;

        list -> next = list2;
        list = list->next;
    }

    return p;
}

int size[2];

vector_t2* list1;
vector_t2* list2;

// input number into the list
void listinput(vector_t2* list, int n){

    vector_t2* temp = list;

    for(int i=0;i<n;i++){

        scanf("%d", &(temp->value));
        temp = temp->next;
    }
}

// innit the list and put number into list
void innitinput(){

    for(int i=0;i<2;i++){

        scanf("%d", &(size[i]));
    }

    list1 = init_list2(size[0]);
    list2 = init_list2(size[1]);

    listinput(list1, size[0]);
    listinput(list2, size[1]);
}

//reverse the list
vector_t2* reverse2(vector_t2* list2, int a){

    vector_t2* temp = NULL;
    vector_t2* temp2 = NULL;
    vector_t2* origin = NULL;
    origin = list2;

    while(list2 != NULL){

        temp2 = list2->next;

        list2->next = temp;
        temp = list2;
        list2 = temp2;
    }
    origin->next = temp2;

    return temp;
}

// link two list with crecendol number
vector_t2* algorithm(vector_t2* list1, vector_t2* list2){

    vector_t2* p1 = NULL;
    vector_t2* p2 = NULL;
    vector_t2* p3 = NULL;
    vector_t2* origin = NULL;

    // find the smallest first number in two list
    if(list1->value > list2->value){

        p1 = list1;
        p2 = list2;
    }else{

        p1 = list2;
        p2 = list1;
    }

    origin = p1;
    p3 = p1;
    p1 = p1->next;

    // compare current smallest number in two list and choose the smaller one into the final list
    while(p1 != NULL || p2 != NULL){

        if(p1 != NULL && p2 != NULL){

            if(p1->value < p2->value){

                p3->next = p2;
                p3 = p2;
                p2 = p2->next;
            }else{

                p3->next = p1;
                p3 = p1;
                p1 = p1->next;
            }   
        }else if(p2 != NULL){

            p3->next = p2;
            p3 = p2;
            p2 = p2->next;
        }else if(p1 != NULL){

            p3->next = p1;
            p3 = p1;
            p1 = p1->next;
        }
    }

    return origin;
}
int main(){

    innitinput();

    list1 = reverse2(list1, size[0]);
    list2 = reverse2(list2, size[1]);

    list1 = algorithm(list1, list2);
    //output
    for(int i=0; i<size[0]+size[1]; i++){

        printf("%d ", list1->value);
        list1 = list1->next;
    }
    printf("\n");
    return 0;
}
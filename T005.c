#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// kai
// form the struct of the list
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

int size[3];

vector_t2* list1;
vector_t2* list2;
vector_t2* list3;

// input the number into list
void listinput(vector_t2* list, int n){

    vector_t2* temp = list;

    for(int i=0;i<n;i++){

        scanf("%d", &(temp->value));
        temp = temp->next;
    }
}

// init and input
void innitinput(){

    for(int i=0;i<3;i++){

        scanf("%d", &(size[i]));
    }

    list1 = init_list2(size[0]);
    list2 = init_list2(size[1]);
    list3 = init_list2(size[2]);

    listinput(list1, size[0]);
    listinput(list2, size[1]);
    listinput(list3, size[2]);

}

//delete the same number in these list
vector_t2* algorithm1(vector_t2* list1, vector_t2* list2){

    vector_t2* p1 = NULL;
    vector_t2* p2 = NULL;

    p1 = list1;
    p2 = list2;

    while(p1 != NULL || p2 != NULL){

        if(p1 != NULL && p2 != NULL){

            if(p1->value != p2->value){

                if(p1->value > p2->value){

                    p2 = p2->next;
                }else{

                    p1->value = -1;
                    p1 = p1->next;
                }
            }else{

                p1 = p1->next;
                p2 = p2->next;
            }
        }else if(p2 == NULL){

            p1->value = -1;
            p1 = p1->next;
        }else if(p1 == NULL){

            break;
        }
    }

    return list1;
}

// delete the number in list2 in list1
vector_t2* algorithm2(vector_t2* list1, vector_t2* list2){

    vector_t2* p1 = NULL;
    vector_t2* p2 = NULL;
    vector_t2* p3 = NULL;

    while(list1->value == list2->value){

        list1 = list1->next;
    }
    p1 = list1->next;
    p2 = list2;
    p3 = list1;

    while(p1 != NULL && p2 != NULL){

        if(p2->value == -1){

            p2 = p2->next;
            continue;
        }
        if(p1->value != p2->value){

            if(p1->value > p2->value){

                p2 = p2->next;
            }else{

                p1 = p1->next;
                p3 = p3->next;
            }
        }else{

            p3->next = p1->next;
            p1 = p1->next;
        }
    }

    return list1;
}


int main(){

    innitinput();

    list2 = algorithm1(list2, list3);
    vector_t2* p1 = list2;

    list1 = algorithm2(list1, list2);

    // output
    while(list1 != NULL){

        printf("%d ", list1->value);
        list1 = list1->next;
    }
    printf("\n");
    return 0;
}
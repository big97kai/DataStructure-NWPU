#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>

using namespace std;

// kai
// form the list of two side list
typedef struct vector_t2{
    char value;
    int fluent;
    struct vector_t2 *next, *before;
}vector_t2;

// init list
vector_t2* init_list2(int n){

    vector_t2* p=NULL;
    vector_t2* list2=NULL;
    vector_t2* list = (vector_t2*) malloc (sizeof(vector_t2));
    assert(list != NULL);
    p = list;
    list -> value = '0';
    list -> fluent = 0;
    list -> next = NULL;
    list -> before = NULL;

    for(int i=1; i<n; i++){

        list2 = (vector_t2*) malloc (sizeof(vector_t2));
        list2 -> value = '0';
        list2 -> fluent = 0;
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

int a;
int b;
char list2[100];
vector_t2* list1;
char temp2[100];

// input number into list
void listinput(vector_t2* list){

    vector_t2* tem = list;

    for(int i=0; i<a;i++){

        tem->value = temp2[i];
        tem = tem->next;
    }
}

// init an put number
void innitinput(){

    cin >> a >> b;

    for(int i=0; i<a; i++){

        cin >> temp2[i];
    }

    for(int i=0; i<b; i++){

        cin >> list2[i];
    }
}

// add the fluent of the list
vector_t2* put(vector_t2* list){

    vector_t2* temp = list;

    for(int i=0;i<b;i++){

        temp = list;

        do{

            if(list2[i] == temp->value){

                temp->fluent++;
            }
            temp=temp->next;

        }while(temp != list);
    }
    temp = list;

    return list;
}

// booble algorithm to put the bigger number front
vector_t2* booble(vector_t2* list){

    vector_t2* temp = list->before;;
    char a2;
    int b;
    for(int i=0;i<a;i++){

        temp = list->before;
        while(temp != list){

            if(temp->fluent > temp->before->fluent){

                a2 = temp->value;
                b = temp->fluent;
                temp->value = temp->before->value;
                temp->fluent = temp->before->fluent;
                temp->before->value = a2;
                temp->before->fluent = b;
            }

                temp = temp->before;
        }
    }
    return list;
}
int main(){

    innitinput();
    list1 = init_list2(a);

    listinput(list1);

    list1 = put(list1);
    list1 = booble(list1);

    vector_t2* temp = list1;

    // output
    do{

        cout << list1->value << " ";
        list1 = list1->next;

    }while(temp != list1);

    cout << endl;
    return 0;
}
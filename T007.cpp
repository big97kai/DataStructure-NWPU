#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>

#define MAXNUM 100
using namespace std;

typedef struct stack_temp{
    char base[MAXNUM];
    char* top;
    int stacksize;
}stack_temp;

stack_temp stack_all;
char input[100];
void init_stack(stack_temp& stack){
    

    stack_temp* p = (stack_temp*)malloc(sizeof(stack));
    assert(p != NULL);
    stack.top = stack.base;
    stack.stacksize = MAXNUM;
}

void input_stack(char* input, int size){

    cin.getline(input, size);
}

void push(stack_temp& stack, char element){

    if(stack.top >= stack.base + 4*stack.stacksize){

        printf("run out of memery");
        exit(1);
    }
    *stack.top = element;
    stack.top++;
}

char pop(stack_temp& stack){

    if(stack.top != stack.base){

        stack.top--;
        char temp = *stack.top;
        return temp;
    }

    return '0';
}

int algorithm(stack_temp& stack, char* input, int size){

    char temp;
    int flag;
    for(int i=0; i<size-1; i++){

        switch (input[i])
        {
        case '(':
            push(stack, input[i]);
            break;
        
        case '[':
            push(stack, input[i]);
            break;

        case ']':
            temp = pop(stack);

            if(temp != '[' ){

                return 0;
            }
            break;

        case ')':
            temp = pop(stack);

            if(temp != '('){

                return 0;
            }
            break;
        }
    }

    if(stack.top != stack.base){

        return 0;
    }

    return 1;
}

int main(){

    init_stack(stack_all);
    input_stack(input, 99);

    int flag = algorithm(stack_all, input, 99);

    if(flag == 1){

        printf("yes");
    }else{

        printf("no");
    }

    return 0;
}
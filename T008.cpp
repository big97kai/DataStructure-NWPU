#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>

#define MAXNUM 100
using namespace std;
/**
 * @brief  practice of stack
 * 
 */
typedef struct stack_temp{
    char base[MAXNUM];
    int top;
}stack_temp;

stack_temp stack_all;
char input[100];
/**
 * @brief init stack
 * 
 * @param stack 
 */
void init_stack(stack_temp& stack){
    
    stack_temp* p = (stack_temp*)malloc(sizeof(stack_temp));
    assert(p != NULL);
    stack.top = -1;
}
/**
 * @brief input the income
 * 
 * @param input 
 * @param size 
 */
void input_stack(char* input, int size){

    scanf("%s",input);
}

/**
 * @brief push the stuff into stack
 * 
 * @param stack 
 * @param element 
 */
void push(stack_temp& stack, char element){

    if(stack.top >= MAXNUM - 1){

        printf("run out of memery");
        exit(1);
    }
    stack.top++;
    stack.base[stack.top] = element;
}

/**
 * @brief pop out the top of the stack
 * 
 * @param stack 
 * @return char 
 */
char pop(stack_temp& stack){

    if(stack.top != -1){

        char temp = stack.base[stack.top];
        stack.top--;
        return temp;
    }

    printf("run out of size0");
    exit(1);
}

/**
 * @brief Get the stack top
 * 
 * @param stack 
 * @return char 
 */
char get_stack(stack_temp& stack){

    return stack.base[stack.top];
}
/**
 * @brief compare c1 and c2
 * 
 * @param stack 
 * @param compared 
 * @return char 
 */
char compare(stack_temp& stack, char compared){

    switch (compared)
    {
    case '(':
        return '<';
        break;
    
    case '+':
        if(get_stack(stack) == '(' || get_stack(stack) == '#'){

            return '<';
        }else{

            return '>';
        }
        break;
    
    case '*':
            
        return '<';
        break;
    
    case '/':

        return '<';
        break;

    case '-':
        if(get_stack(stack) == '(' || get_stack(stack) == '#'){

            return '<';
        }else{

            return '>';
        }
        break;

    case ')':
        if(get_stack(stack) == '('){

            return '=';
        }else{

            return '>';
        }
        break;

    default:
        return '$';
    }
}

/**
 * @brief change to the post-form
 * 
 * @param stack 
 * @param input 
 * @param size 
 */
void algorithm(stack_temp& stack, char* input, int size){

    char output[100];
    int outnumber = 0;
    push(stack, '#');
    int temp=0;
    while(temp<size){

        switch (compare(stack, input[temp]))
        {
        case '>':
            output[outnumber] = pop(stack);
            outnumber++;
            break;
        
        case '<':
            push(stack, input[temp]);
            temp++;
            break;

        case '$':
            output[outnumber] = input[temp];
            outnumber++;
            temp++;
            break;

        case '=':
            pop(stack);
            temp++;
            break;
        }
    }

    while(get_stack(stack) != '#'){

        output[outnumber] = pop(stack);
        outnumber++;
    }

    for(int i=0; i<outnumber; i++){

        cout << output[i];
    }
    cout << endl;
}

int main(){

    init_stack(stack_all);
    input_stack(input, 99);

    algorithm(stack_all, input, strlen(input));

    return 0;
}
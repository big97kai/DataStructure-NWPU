#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>

using namespace std;

typedef struct queue
{
    int *data;
    int rear;
    int front;
    int length;
} queue, *pqueue;

/**
 * @brief push the x into the rear position of queue
 * 
 * @param q 
 * @param x 
 */
void push(pqueue q, int x)
{
    if ((q->rear + 1) % q->length == q->front)
        printf("Full queue.\n");
    else
    {
        q->data[q->rear] = x;
        q->rear = (q->rear + 1) % q->length;
    }
}
/**
 * @brief pop out the front number of queue
 * 
 * @param q 
 * @return int 
 */
int pop(pqueue q)
{
    if (q->front == q->rear)
    {
        printf("Is Empty.\n");
    }
    else
    {
        int temp = q->data[q->front];
        q->front = (q->front + 1) % q->length;
        return temp;
    }
    return 0;
}

/**
 * @brief if queue is empty
 * 
 * @param q 
 * @return true 
 * @return false 
 */
bool isEmpty(pqueue q)
{
    return (q->rear == q->front);
}

/**
 * @brief get the top of queue
 * 
 * @param q 
 * @return int 
 */
int top(pqueue q)
{
    return q->data[q->front];
}

/**
 * @brief Create a Queue object
 * 
 * @return pqueue 
 */
pqueue createQueue()
{
    pqueue q = (queue *)malloc(sizeof(queue));
    assert(q != NULL);
    q->length = 0;
    q->front = 0;
    q->rear = 0;

    return q;
}

/**
 * @brief get the input and put the number into queue
 * 
 * @param q 
 * @param tmp 
 */
void input(pqueue q, int &tmp)
{

    while (1)
    {
        char x = getchar();
        if (x == ' ')
            continue;
        else if (x == '\n')
            break;
        else
            push(q, (x - '0'));
    }
    char s[4];
    scanf("%s", s);

    scanf("%d", &tmp);
}
int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    pqueue q = createQueue();
    q->length = n+1;
    q->data = (int *)malloc(sizeof(int) * (n + 1));
    int tmp;
    input(q, tmp);
    while (pop(q) != tmp) //判断是否是输入的tmp 如果不是 挨个pop
        ;
    int thistop = top(q);

    while (q->front != q->rear)
    {

        cout << pop(q) << ' ';
    }

    printf("\n");
    printf("%d\n", thistop);

    return 0;
}

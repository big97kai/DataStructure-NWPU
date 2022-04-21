#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#define MAXNUM 100

using namespace std;

typedef struct queue
{
    int data[MAXNUM];
    int rear;
    int front;
} queue, *pqueue;

/**
 * @brief push the x into the rear position of queue
 *
 * @param q
 * @param x
 */
void push(pqueue q, int x, int size)
{
    if ((q->rear + 1) % size == q->front)
        printf("Full queue.\n");
    else
    {
        q->data[q->rear] = x;
        q->rear = (q->rear + 1) % size;
    }
}
/**
 * @brief pop out the front number of queue
 *
 * @param q
 * @return int
 */
int pop(pqueue q, int size)
{
    if (q->front == q->rear)
    {
        printf("Is Empty.\n");
    }
    else
    {
        int temp = q->data[q->front];
        q->front = (q->front + 1) % size;
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
 * @brief if queue is full
 *
 * @param q
 * @return true
 * @return false
 */
bool isFull(pqueue q, int size)
{
    return ((q->rear + 1) % size == q->front);
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
    q->front = 0;
    q->rear = 0;

    return q;
}

/**
 * @brief caiculate fibonacci
 *
 * @param q
 * @param size
 * @param max
 * @return int
 */
void caculate(pqueue q, int size, int max)
{
	//初始化队列
    for(int i=0; i<size-2; i++){

        push(q, 0, size);
    }
    
    push(q, 1, size);

    int sum = 0;
    int temp;
    while (1)
    {
        for(int i=0; i<size-1; i++){
	//计算新的fibonacci数字
            temp = pop(q, size);
            sum += temp;
            push(q, temp, size);
        }
	//取边界值
        if(sum <= max){

            pop(q, size);
            push(q, sum, size);
            sum = 0;
        }else{
            break;
        }
    }
}
int main()
{
    int size, max;

    cin >> max;
    cin >> size;
    size++;
    pqueue q = createQueue();

    caculate(q, size, max);

    while (!isEmpty(q))
    {

        printf("%d ", pop(q, size));
    }
    printf("\n");
    return 0;
}

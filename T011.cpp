#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>

using namespace std;

typedef struct thislist
{
    int *data;
    int length;
    int size;
} thislist, *plist;

/**
 * @brief Create a List object and the length is always 0
 *
 * @param size
 * @return plist
 */
plist createList(int size)
{
    plist q = (plist)malloc(sizeof(thislist));
    assert(q != NULL);
    q->data = (int *)malloc(sizeof(int) * size);
    assert(q->data != NULL);
    q->length = 0;
    q->size = size;

    return q;
}

/**
 * @brief transfer the number this number time
 *
 * @param list
 * @param number
 */
void trans(thislist *list, int number)
{

    int temp;
    for (int i = 0; i < number; i++)
    {
        temp=list->data[list->length];
        while (list->length != list->size - 1){
        
            list->data[list->length] = list->data[list->length + 1];
            list->length++; // 挨个交换list和list后面的 一次完成即为成功交换一次 一共完成number次
        }
        list->length = 0;
        list->data[list->size-1] = temp;
    }
}

/**
 * @brief output
 *
 * @param list
 */
void output(thislist *list)
{
    for (int i = 0; i < list->size; i++)
    {

        printf("%d ",list->data[i]);
    }
}
/**
 * @brief  input the list
 *
 * @param size
 * @param number
 */
void input(int &size, int &number)
{
    cin >> size;
    cin >> number;
}

int main(void)
{
/*     int size;
    int number;
    input(size, number);
    plist p = createList(size);

    for (int i = 0; i < size; i++)
    {

        cin >> p->data[i];
    }
    trans(p, number);
    output(p); */

    int size,number;
    scanf("%d %d",&size,&number);
    int list[size];

    for(int i=0;i<size;i++)
        scanf("%d",&list[i]);
    int temp;
    for(int i=0;i<number;i++){
        
        temp = list[0]; //保存第一个
        for(int j=0; j<size-1; j++)
            list[j]=list[j+1];  //每个想向后面进行交换
        list[size-1]=temp; //最后一个方第一个
    }
    for(int i=0; i<size; i++)
        printf("%d ",list[i]);
    return 0;

}

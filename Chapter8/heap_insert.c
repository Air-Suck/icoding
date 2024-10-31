#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//非常阴间的设定，下标为0的位置存储根节点。。。。
typedef struct _otherInfo
{
    int i;
    int j;
}OtherInfo;

typedef struct _minHeapNode
{
    int value;
    OtherInfo otherInfo;
}MinHeapNode, *PMinHeapNode;

typedef struct _minPQ {
    PMinHeapNode heap_array; // 指向堆元素数组
    int heap_size; // 当前堆中的元素个数
    int capacity;  //堆数组的大小
}MinHeap, *PMinHeap;

extern int parent(int i);

extern int left(int i);

extern int right(int i);

extern void swap_node(MinHeapNode* x, MinHeapNode* y);

bool heap_insert_value(PMinHeap pq, int value) {
    //指针判空
    if (pq == NULL) {
        return false;
    }
    //如果堆已经装不下了也要退出
    if (pq->heap_size == pq->capacity) {
        return false;
    }
    int i;
    //初始化节点
    pq->heap_array[pq->heap_size].value = value;
    pq->heap_size++;
	//从最后一位向上沿路径调整为小顶堆（路径之外的子树本身是小顶堆，且根和其父节点都满足小顶堆的定义，所以这里可以不用考虑路径外的节点）
    //要从size-1开始！因为size是存储的元素个数，size-1才是下标
    i = pq->heap_size-1;
    while (i > 0) {
        //当父节点的值比子节点的值大的时候交换
        if (pq->heap_array[parent(i)].value > pq->heap_array[i].value) {
            swap_node(&(pq->heap_array[parent(i)]), &(pq->heap_array[i]));
        }
        i = parent(i);
    }
    //最后一次循环时i的值仍然>0，所以这里不用多做一次交换
    return true;
}
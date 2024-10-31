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

void init_min_heap(PMinHeap pq, int capacity) {
    //这里的pq是已经在函数外部malloc了
    if (pq == NULL) {
        return;
    }
    pq->capacity = capacity;
    pq->heap_size = 0;
    //通过malloc函数动态分配数组内存（甚至不让多分配一点内存。。。。）
    pq->heap_array = (MinHeapNode*)malloc(sizeof(MinHeapNode) * capacity);
    return;
}
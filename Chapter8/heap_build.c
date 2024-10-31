#include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>
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

void min_heapify(PMinHeap pq, int i) {
    int smallest;
    //若要进行堆的调整，就一定要有孩子，这里先保证有孩子存在（即保证左孩子存在）
    while (left(i) < pq->heap_size) {
        int l = left(i);
        int r = right(i);
        //这里再进一步判断右孩子是否存在，因为需要比较左右孩子的值
        if (r<pq->heap_size&&pq->heap_array[l].value > pq->heap_array[r].value) {
            smallest = r;
        }
        //这个else有两种情况，一种是右孩子不存在，那么小节点就是左孩子；另一种是右孩子存在，但是右孩子的值大于左孩子的值，这个时候小节点还是左孩子
        else {
            smallest = l;
        }
		//若当前节点大于孩子中的小节点就要进行交换
        if (pq->heap_array[i].value > pq->heap_array[smallest].value) {
            swap_node(&(pq->heap_array[i]), &(pq->heap_array[smallest]));
            i = smallest;
        }
        //若当前节点小于孩子中的小节点说明当前树已经满足小顶堆的条件，就可以退出循环了
        else {
            break;
        }
    }
}
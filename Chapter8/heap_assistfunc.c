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

int parent(int i) {
    //通过i-1来把2n+1和2n+2变成2n和2n+1，这样不论是左孩子还是右孩子，只要除以2就能得到n（整数截断处理）
    return (i - 1) / 2;
}

int left(int i) {
    //左孩子为2n+1
    return 2 * i + 1;
}

int right(int i) {
    //右孩子为2n+2
    return 2 * i + 2;
}

void swap_node(MinHeapNode* x, MinHeapNode* y) {
    //这里要注意节点信息有两个，这里两个值都要交换
    int temp1;
    OtherInfo temp2;
    //交换节点的值
    temp1 = x->value;
    x->value = y->value;
    y->value = temp1;
    //交换节点的其他信息
    temp2 = x->otherInfo;
    x->otherInfo = y->otherInfo;
    y->otherInfo = temp2;
}
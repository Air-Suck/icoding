// #include<stdio.h>
#define MAXSIZE 100

typedef int ElemType;
struct _seqlist {
    ElemType elem[MAXSIZE];
    int last;
};
typedef struct _seqlist SeqList;

void del_dupnum(SeqList* L) {
    //通过两个记录量来实现只遍历一次数组（通过后项覆盖前项）
    int front = 0, rear = 1;

    while (rear <= L->last) {
        //由于是非递减数组，所以当后项不等于前项的时候就可以进行覆盖
        if (L->elem[rear] != L->elem[front]) {
            front++;
            L->elem[front] = L->elem[rear];
            rear++;
        }
        //当front和rear对应的元素相同的时候，说明该元素要删除，所以直接rear++跳过该元素
        else {
            rear++;
        }
    }
    //注意到if语句中front是先进行++再进行赋值
    //说明最后出循环时front对应位置是有元素的，故last的值就应为front
    L->last = front;
}
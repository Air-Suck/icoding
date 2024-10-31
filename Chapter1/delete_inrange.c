// #include<stdio.h>
#define MAXSIZE 100

typedef int ElemType;

struct _seqlist {
    ElemType elem[MAXSIZE];
    int last;
};
typedef struct _seqlist SeqList;

void del_x2y(SeqList* L, ElemType x, ElemType y) {
    //通过两个记录量来实现只遍历一次数组（通过后项覆盖前项）
    int front = 0, rear = 0;

    while (rear <= L->last) {
        //如果是要删除的元素，就直接rear++跳过
        if ((L->elem[rear] >= x) && (L->elem[rear] <= y)) {
            rear++;
        }
        //如果是不要删除的元素，向前覆盖front的位置，然后rear和front一起后移
        else {
            L->elem[front] = L->elem[rear];
            front++;
            rear++;
        }
    }
    //出循环时front指向的位置并没有元素，所以是front-1
    L->last = front - 1;
}
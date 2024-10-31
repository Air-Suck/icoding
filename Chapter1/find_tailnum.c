#include<stdio.h>

typedef int ElemType;
struct _lnklist {
    ElemType data;
    struct _lnklist* next;
};

typedef struct _lnklist Node;
typedef struct _lnklist* LinkList;

int lnk_search(LinkList L, int k, ElemType* p_ele) {
    int i;
    LinkList front, rear;
    front = L->next;
    rear = front;
    //若链表为空直接退出（使用指针前判空）
    if (front == NULL) {
        return 0;
    }
    //先将rear向后移动k位
    for (i = 0;i < k - 1;i++) {
        if (rear->next != NULL) {
            rear = rear->next;
        }
        else {
            return 0;
        }
    }
    //此时若rear到尾，则front到倒k位
    while (rear->next != NULL) {
        rear = rear->next;
        front = front->next;
    }
    *p_ele = front->data;
    return 1;
}
#include<stdio.h>
#include <stdlib.h>

typedef int ElemType ;
struct _lnklist {
    ElemType data;
    struct _lnklist* next;
};
typedef struct _lnklist Node;
typedef struct _lnklist* LinkList;

void lnk_del_x2y(LinkList L, ElemType mink, ElemType maxk) {
    LinkList p, pre;
    p = L->next;
    pre = L;
    //若链表中没有元素直接退出（使用指针前判空）
    if (p == NULL) {
        return;
    }
    //循环遍历链表删除满足条件的结点
    while (p != NULL) {
        if (p->data > mink && p->data < maxk) {
            pre->next = p->next;
            free(p);
            p = pre->next;
        }
        else {
            p = p->next;
            pre = pre->next;
        }
    }
    return;
}
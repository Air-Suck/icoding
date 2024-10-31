#include<stdio.h>

typedef int ElemType ;
struct _lnklist {
    ElemType data;
    struct _lnklist* next;
};

typedef struct _lnklist Node;
typedef struct _lnklist* LinkList;

void lnk_merge(LinkList A, LinkList B, LinkList C) {
    LinkList tempA;
    LinkList tempB;
    LinkList tempC;
    tempA = A->next;
    tempB = B->next;
    tempC = C;
    //先判断ab链表是否为空（使用指针前判空）
    if (tempA == NULL) {
        if (tempB == NULL) {
            return;
        }
        else {
            tempC->next = tempB->next;
            return;
        }
    }
    //ab链表都还未遍历到链表末尾时交替插入元素
    while (tempA != NULL && tempB != NULL) {
        tempC->next = tempA;
        tempC = tempC->next;
        //此时就应该将tempA后移，因为若放在后面后移的话，tempA->next将变为tempB，导致死循环
        tempA = tempA->next;
        tempC->next = tempB;
        tempC = tempC->next;
        tempB = tempB->next;
    }
    //循环退出时必有一链表遍历到尾部，此时只需将另一个链表直接接到c表后即可
    if (tempA != NULL) {
        tempC->next = tempA;
    }
    if (tempB != NULL) {
        tempC->next = tempB;
    }
    return;
}
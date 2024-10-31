#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef struct _QueueNode {
    ElemType data;          // 数据域
    struct _QueueNode* next;      // 指针域
}LinkQueueNode, * LinkQueue;

//由于要修改LQ的值所以要传入二级指针
int init_queue(LinkQueue* LQ){

    (*LQ) = (LinkQueue)malloc(sizeof(LinkQueueNode));
    //申请失败时直接退出函数
    if (LQ == NULL) {
        return 0;
    }
    //结点申请成功就形成一个头结点的自环
    else {
        (* LQ)->next = *LQ;
        return 1;
    }
}
//这里不修改LQ所以实际上可以传入LQ，不用传入二级指针
int enter_queue(LinkQueue* LQ, ElemType x)
{
    LinkQueue p = (LinkQueue)malloc(sizeof(LinkQueueNode));
    //结点申请失败直接退出函数
    if (p == NULL) {
        return 0;
    }
    //结点申请成功就尾插该结点
    else {
        p->data = x;
        p->next = (*LQ)->next;
        (*LQ)->next = p;
        //注意要修改尾指针的值
        *LQ = (*LQ)->next;
        return 1;
    }
}

int leave_queue(LinkQueue* LQ, ElemType* x)
{
    LinkQueue temp,p;
    p = *LQ;
    //为空队列时直接退出函数
    if ((*LQ)->next == (*LQ)) {
        return 0;
    }
    //只有一个结点的时候单独判断，以保证尾指针不丢失
    if (p->next->next == p) {  
        *x = (*LQ)->data;
        p = p->next;
        p->next = p;
        free(*LQ);
        (*LQ) = p;
    }
    //这种操作方式并没有包含只含一个结点的情况
    //因为此时尾结点就是要free的结点，这样操作会导致尾指针丢失
    else {
        *x = (*LQ)->next->next->data;
        temp = (*LQ)->next->next;
        (*LQ)->next->next = (*LQ)->next->next->next;
        free(temp);
        return 1;
    }
    return 0;
}

//用于检测上述函数功能
int show_queue(LinkQueue LQ) {
    LinkQueue p;
    if (LQ->next == LQ) {
        return 0;
    }
    p = LQ->next->next;
    while (p != LQ->next) {
        printf("%d\n", p->data);
        p = p->next;
    }
    return 1;
}

int main() {
    LinkQueue tail;
    int data;
    init_queue(&tail);
    enter_queue(&tail, 43);
    show_queue(tail);
    printf("\n");
    for (int j = 0;j < 4;j++) {
        leave_queue(&tail,&data);
        printf("%d\n", data);
    }
    printf("\n");
    show_queue(tail);
    printf("1");
    return 0;
}
#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

// 非零元素结点结构
typedef struct OLNode
{
    int row, col;
    ElemType value;
    struct OLNode* right, * down;
}OLNode, * OLink;

// 十字链表结构
typedef struct
{
    OLink* rowhead, * colhead;
    int rows, cols, nums;
}CrossList, * PCrossList;

int init_cross_list(PCrossList L, const ElemType* A, int m, int n)
{
    int i;
    OLink q, p;
    L->rows = m;
    L->cols = n;
    L->nums = 0;
    //申请连续空间（申请连续空间后可以像数组一样加下标来使用）
    if (!(L->rowhead = (OLink*)malloc((m + 1) * sizeof(OLink))))
        return 0;
    //申请连续空间
    if (!(L->colhead = (OLink*)malloc((n + 1) * sizeof(OLink))))
        return 0;
    //为行头指针初始化（不带头结点）
    for (i = 0; i <= m; i++)
        L->rowhead[i] = NULL;
    //为列头指针初始化（不带头结点）
    for (i = 0; i <= n; i++)
        L->colhead[i] = NULL;
    //遍历数组A
    for (i = 0; i < m * n; i++) {
        //跳过零元素
        if (A[i] == 0);
        else {
            //新建结点
            if (!(p = (OLNode*)malloc(sizeof(OLNode))))
                return 0;
            //计算行数和列数
            p->col = i % n + 1;
            p->row = (i + 1 - p->col) / n + 1;
            p->value = A[i];
            p->right = NULL;
            L->nums++;
            p->down = NULL;
            //若是行头结点
            if (L->rowhead[p->row] == NULL)
                L->rowhead[p->row] = p;
            //若不是行头结点
            else {
                q = L->rowhead[p->row];
                while (q->right != NULL)
                    q = q->right;
                q->right = p;
            }
            //若是列头结点
            if (L->colhead[p->col] == NULL)
                L->colhead[p->col] = p;
            //若不是列头结点
            else {
                q = L->colhead[p->col];
                while (q->down != NULL)
                    q = q->down;
                q->down = p;
            }
        }
    }
    return L->nums;
}
int del_cross_list(PCrossList L, ElemType k)
{
    int count = 0;
    //循环行数（先不进行free，在col的循环中free结点）
    for (int i = 0; i < L->rows + 1; ++i) {
        //将指针p初始化为行头指针
        OLink p = L->rowhead[i];
        //p不空即当前行还未遍历完
        while (p) {
            if (p->value == k) {
                OLink q;
                //寻找p的前驱
                for (q = L->rowhead[i]; q != p && q->right != p; q = q->right) {
                }
                //相等时说明头结点的值为k
                if (q == p) {
                    L->rowhead[i] = p->right;
                    p = L->rowhead[i];
                    count++;
                    continue;
                }
                else {
                    q->right = p->right;
                    p = p->right;
                    count++;
                    continue;
                }
            }
            p = p->right;
        }
    }
    //循环列数（此时开始释放结点）
    for (int i = 0; i < L->cols + 1; ++i) {
        //将指针p初始化为列头指针
        OLink p = L->colhead[i];
        //p不空即当前列还未遍历完
        while (p != NULL) {
            if (p->value == k) {
                OLink q;
                //寻找p的前驱
                for (q = L->colhead[i]; q != p && q->down != p; q = q->down) {
                }
                //pq相等时说明头结点的值为k
                if (q == p) {
                    L->colhead[i] = p->down;
                    p = L->colhead[i];
                    free(q);
                    continue;
                }
                else {
                    OLink tmp = q->down;
                    q->down = p->down;
                    p = p->down;
                    free(tmp);
                    continue;
                }
            }
            p = p->down;
        }
    }
    return count;
}
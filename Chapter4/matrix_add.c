#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef int ElemType ;
#define MAXSIZE 100         
typedef struct {
    //非零元的行下标和列下标，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
    int i, j;
    //非零元的值
    ElemType e;						
}Triple;

typedef struct {
    // 非零元三元组表
    Triple data[MAXSIZE];			
    // 矩阵的行数、列数和非零元个数
    int    m, n, len;							
}TSMatrix;

//bool类型函数
int add_matrix(const TSMatrix* pM, const TSMatrix* pN, TSMatrix* pQ) {
    if (pM == NULL || pN == NULL||pQ==NULL) {
        return 0;
    }
    if (pM->m != pN->m || pM->n != pN->n) {
        return 0;
    }
    int pmIndex = 0, pnIndex = 0,pqIndex=0,i,j;
    //用temp存储pm和pn的和矩阵
    int temp[MAXSIZE+1][MAXSIZE+1] = { 0 };
    //将pm还原
    for (;pmIndex < pM->len;pmIndex++) {
        temp[pM->data[pmIndex].i][pM->data[pmIndex].j] += pM->data[pmIndex].e;
    }
    //将pn加到pm矩阵上
    for (;pnIndex < pN->len;pnIndex++) {
        temp[pN->data[pnIndex].i][pN->data[pnIndex].j] += pN->data[pnIndex].e;
    }
    //将得到的temp矩阵用三元组存储到pq中
    for (i = 1;i < MAXSIZE + 1;i++) {
        for (j = 1;j < MAXSIZE + 1;j++) {
            if (temp[i][j] != 0) {
                pQ->data[pqIndex].e = temp[i][j];
                pQ->data[pqIndex].i = i;
                pQ->data[pqIndex].j = j;
                pqIndex++;
            }
        }
    }
    //调整pq中的参数
    pQ->len = pqIndex;
    pQ->m = pM->m;
    pQ->n = pM->n;
    return 1;
}
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
// #include "bitree.h" //请不要删除，否则检查不通过

#define Stack_Size 50

typedef int DataType;

typedef struct Node{
    DataType data;
    struct Node* left;
    struct Node* right;
}BiTNode, *BiTree;

typedef BiTNode* ElemType;

typedef struct{
    ElemType elem[Stack_Size];
    int top;
}Stack;

bool path(BiTNode* root, BiTNode* node, Stack* s);

// 初始化栈
void init_stack(Stack *S); 
//x 入栈
bool push(Stack* S, ElemType x); 
//出栈，元素保存到px所指的单元，函数返回true,栈为空时返回 false
bool pop(Stack* S, ElemType *px); 
//获取栈顶元素，将其保存到px所指的单元，函数返回true，栈满时返回 false
bool top(Stack* S, ElemType *px); 
// 栈为空时返回 true，否则返回 false
bool is_empty(Stack* S);  

//思路：只要从根节点开始看pq两个结点的路径，直到遇到不同的节点为止，不同节点的上一个节点即为最近公共祖先
BiTNode* nearest_ancestor(BiTree root, BiTNode* p, BiTNode* q) {
    if (root == NULL || p == NULL || q == NULL) {
        return NULL;
    }
    int i =0;
    //初始化两个栈来记录两个结点的路径
    Stack stackp, stackq;
    //使用一个数组来保存栈元素（模拟的栈）
    ElemType stackElem[Stack_Size];
    ElemType temp;
    //初始化两个栈
    init_stack(&stackp);
    init_stack(&stackq);
    path(root, p, &stackp);
    path(root, q, &stackq);
    //用数组存储栈stackp中的元素
    while (!is_empty(&stackp)) {
        pop(&stackp, &temp);
        stackElem[i] = temp;
        i++;
    }
    //为倒序读取栈元素做准备
    i--;
    //将stackq中的元素存入stackp中实现倒序
    while (!is_empty(&stackq)) {
        pop(&stackq, &temp);
        push(&stackp, temp);
    }
    pop(&stackp, &temp);
    //开始比对知道遇到不同节点
    while (temp == stackElem[i]) {
        pop(&stackp, &temp);
        i--;
    }
    return stackElem[i + 1];
}
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
//访问结点
void visit_node(BiTNode *node);

void pre_order(BiTree root) {
    BiTNode* p = root;
    Stack stack;
    init_stack(&stack);
    //退出循环的条件应该是p指针在叶子结点上并且没有办法再回退（栈空）
    while (p != NULL|| !is_empty(&stack)) {
        //先序遍历先向左子树走，如果左子树根节点不空的话将左子树的根节点入栈
        if (p != NULL) {
            //先访问根节点
            visit_node(p);
            push(&stack, p);
            //继续向左深入
            p=p->left;
        }
        //如果左子树是空的话就找右子树
        else {
            pop(&stack, &p);
            p = p->right;
        }
    }
}
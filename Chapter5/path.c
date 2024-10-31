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

//要求栈内元素从栈底到栈顶是从根节点到node的路径
bool path(BiTNode* root, BiTNode* node, Stack* s) {
    BiTNode* p = root, * q = NULL;
    //传入的栈已经初始化过了
    //init_stack(s);
    //要先进行指针判空，否则这些便捷情况也将进入循环导致入栈出栈操作次数过多
    //比如node==NULL时将找到第一个叶子结点的左子树，而不是返回空栈
    if (p == NULL || node == NULL || !is_empty(s)) {
        return 0;
    }
    //实际上就是遍历的框架
    while (p != NULL || !is_empty(s)) {
        //遍历左子树
        if (p != NULL) {
        	//如果找到node直接退出函数
            if (p == node) {
                return 1;
            }
            push(s, p);
            p = p->left;
        }
        //遍历右子树
        else {
            //右子树还没遍历完时不能将栈顶弹出（保证站内元素的路径不断）
            top(s, &p);
            //右子树遍历完成
            if (p->right == NULL || p->right == q) {
                q = p;
                //弹出栈顶元素
                pop(s, &p);
                //将指针p置空以便下次进入循环时退层
                p = NULL;
            }
            //右子树还未遍历完
            else {
                p = p->right;
            }
        }
    }
    //若未在循环中退出函数则没找到node，返回false
    return 0;
}
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
// #include "bitree.h" //请不要删除，否则检查不通过

#define MAX_CHILDREN_NUM 5

typedef int DataType;

typedef struct Node{
    DataType data;
    struct Node* left;
    struct Node* right;
}BiTNode, *BiTree;

struct _CSNode{
    DataType data;
    struct _CSNode *children[MAX_CHILDREN_NUM];
};
typedef struct _CSNode CSNode;

struct __Queue
{
    int i, j; //指向数组内元素的游标
    void **array;
};
typedef struct __Queue Queue;

//创建队列
Queue* create_queue(); 
//队为空返回true,不为空时返回false
bool is_empty_queue(Queue *tree);
//结点指针出队
void* del_queue(Queue *tree); 
//结点指针入队
void add_queue(Queue *tree, void *node); 
//释放队列
void free_queue(Queue *tree); 

//重点是保证两个队列同步，如果两个队列没有同步的话
//从queue中取出的孩子结点不知道应该作为二叉树中的那个结点的左右孩子
BiTNode* transform(CSNode* root) {
    //创建两个队列，通过queue来获取子节点，通过bitQueue来进行二叉树的创建（必须保证两个队列同步）
    Queue* queue = create_queue();
    Queue* bitQueue = create_queue();
    //申请根节点
    BiTNode* bitRoot = (BiTNode*)malloc(sizeof(BiTNode));
    BiTNode*pre;
    CSNode* temp;
    int i;
    bitRoot->data = root->data;
    bitRoot->left = NULL;
    bitRoot->right = NULL;
    add_queue(queue, root);
    add_queue(bitQueue, bitRoot);
    while (!is_empty_queue(queue)) {
        //由于两个队列同步，所以temp内存储的子节点即为当前二叉树结点pre接下来的节点（左右孩子）
        pre = del_queue(bitQueue);
        temp = del_queue(queue);
        for (i = 0;i < MAX_CHILDREN_NUM;i++) {
            //数组中的空指针直接丢弃即可
            if (temp->children[i] != NULL) {
                //第一个孩子当做左孩子
                if (i == 0) {
                    pre->left = (BiTNode*)malloc(sizeof(BiTNode));
                    pre = pre->left;
                    pre->data = temp->children[i]->data;
                    pre->left = NULL;
                    pre->right = NULL;
                    add_queue(queue, temp->children[i]);
                    add_queue(bitQueue, pre);
                }
                //其余孩子为左孩子的右孩子
                else {
                    pre->right = (BiTNode*)malloc(sizeof(BiTNode));
                    pre = pre->right;
                    pre->data = temp->children[i]->data;
                    pre->left = NULL;
                    pre->right = NULL;
                    add_queue(queue, temp->children[i]);
                    add_queue(bitQueue, pre);
                }
            }
        }
    }
    //释放内存
    free_queue(queue);
    free_queue(bitQueue);
    return bitRoot;
}
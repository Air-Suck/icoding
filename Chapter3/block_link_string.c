//抽象玩意......
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_SUB_STR_LEN 100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BLOCK_SIZE 4    // 可由用户定义的块大小
#define BLS_BLANK '#'   // 用于空白处的补齐字符

typedef struct _block {
    char ch[BLOCK_SIZE];    //块的数据域
    struct _block* next;    //块的指针域
} Block;

typedef struct {
    Block* head;        // 串的头指针
    Block* tail;        // 串的尾指针
    int len;            // 串的当前长度
} BLString;

//字符串初始化函数：
void blstr_init(BLString* T) {
    T->len = 0;
    T->head = NULL;
    T->tail = NULL;
}

int blstr_substr(BLString src, int pos, int len, BLString* sub) {
    int i, j;
    int index = 0;
    int index1 = 0;
    sub->head = (Block*)malloc(sizeof(Block));
    Block* temp = src.head;
    Block* temp1;
    if (sub != NULL) {
        sub->len = len;
        temp1 = sub->head;
    }
    else {
        return 0;
    }
    if (temp == NULL) {
        return 0;
    }
    if (temp1 == NULL) {
        return 0;
    }
    for (i = 0;i < pos;i++) {
        index++;
        if (index >= BLOCK_SIZE) {
            index = index % BLOCK_SIZE;
            if (temp!=src.tail) {
                temp = temp->next;
            }
            else {
                return 0;
            }
        }
    }
    for (j = 0;j < len;j++) {
        temp1->ch[index1] = temp->ch[index];
        index++;
        index1++;
        if (index >= BLOCK_SIZE) {
            index = index % BLOCK_SIZE;
            if (temp!=src.tail) {
                temp = temp->next;
            }
            else {
                return 0;
            }
        }
        if (index1 >= BLOCK_SIZE) {
            index1 = index1 % BLOCK_SIZE;
            Block*p = (Block*)malloc(sizeof(Block));
            if (p != NULL) {
                temp1->next= p;
                sub->tail = p;
                temp1 = temp1->next;
                temp1->next = NULL;
            }
            else {
                return 0;
            }
        }
    }
    return 1;
}

void add(BLString* sub,char elem) {
    if (strlen(sub->tail->ch)>= BLOCK_SIZE) {
        Block* p = (Block*)malloc(sizeof(Block));
        p->ch[0] = elem;
        sub->tail->next = p;
        sub->tail = sub->tail->next;
    }
    else {
        sub->tail->ch[strlen(sub->tail->ch)] = elem;
    }
}

//为块链串装载字符串
void blstr_assign(BLString* T, const char* src_str)
{

    T->head = (Block*)malloc(sizeof(Block));



    //下面的循环是为了把新分配给头节点的内存空间的数据域全填上'#'
    for (int j = 0; j < BLOCK_SIZE; j++)
    {
        T->head->ch[j] = BLS_BLANK;
    }

    T->tail = T->head;


    //下面的循环为块链串装载指定的字符串
    //这里默认字符串以'\0'结尾
    for (int i = 0; i < strlen(src_str) && *(src_str + i) != '\0'; i++)
    {
        if (i != 0 && i % 4 == 0)    //每装4个字符就分配新节点
        {
            T->tail->next = (Block*)malloc(sizeof(Block));
            T->tail = T->tail->next;
            T->tail->next = NULL;


            //下面的循环用于给新分配的节点的字符数据域全部填上'#'
            for (int j = 0; j < BLOCK_SIZE; j++)
            {
                T->tail->ch[j] = BLS_BLANK;
            }
        }

        T->tail->ch[i % 4] = *(src_str + i);
        T->tail->ch[i % 4 + 1] = BLS_BLANK;
    }
    T->len = strlen(src_str);
}



//取出src中第pos个字符开始的len长度的子串, 然后用sub返回
// bool blstr_substr(BLString src, int pos, int len, BLString* sub)
// {
//     //icoding似乎没测试len为0的情况，这里（按照题目意思）该返回true还是false有待商榷
//     if (len == 0)
//     {
//         return false;
//     }


//     Block* current_block = src.head;
//     int src_cursor = 0;
//     for (; src_cursor <= pos && current_block != NULL && current_block->ch[src_cursor % 4] != BLS_BLANK; src_cursor++)
//     {
//         if (src_cursor != 0 && src_cursor % 4 == 0)
//         {
//             current_block = current_block->next;
//             if (current_block == NULL)
//             {
//                 return false;
//             }
//         }
//     }

//     src_cursor -= 1;

//     char __sub[MAX_SUB_STR_LEN];

//     for (int sub_cursor = 0; sub_cursor < len; src_cursor++, sub_cursor++)
//     {

//         //下面这个if似乎有点多余，不过能过就不管了:)，有兴趣可以去掉这个if分支试试
//         if (current_block != NULL)
//         {
//             if (sub_cursor != 0 && src_cursor % 4 == 0)
//             {
//                 current_block = current_block->next;

//                 //如果主串指针的下一个节点为空（即到达末尾)，则截断子串并装载给sub
//                 if (current_block == NULL)
//                 {
//                     blstr_assign(sub, __sub);
//                     return true;
//                 }
//             }


//             //如果主串指针在子串长度小于len之前就遇到'#'（即到达末尾），则截断子串并装载给sub
//             if (current_block->ch[src_cursor % 4] == BLS_BLANK)
//             {
//                 blstr_assign(sub, __sub);
//                 return true;
//             }

//             __sub[sub_cursor] = current_block->ch[src_cursor % 4];
//             __sub[sub_cursor + 1] = '\0';
//         }

//         else
//         {
//             return false;
//         }
//     }
//     blstr_assign(sub, __sub);
//     return true;
// }
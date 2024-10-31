#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

typedef int bool;

typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    struct node* parent;
    int height;
} node_t;

node_t* path[100];

//分为两步：1.插入节点	2.更新高度	3.查找失衡结点	4.调整为平衡树	5.再次更新高度保证节点值正确
node_t* avl_insert(node_t* root, int val) {
    //1.插入节点
    node_t* pre = root, * temp = root;
    node_t* temp1;
    int balnaceNum, i = 0, j;
    //当传入根节点为空时说明当前树为空树，创建一个根节点
    if (root == NULL) {
        root = (node_t*)malloc(sizeof(node_t));
        root->height = 1;
        root->left = NULL;
        root->parent = NULL;
        root->right = NULL;
        root->val = val;
        return root;
    }
    node_t* insertNode = (node_t*)malloc(sizeof(node_t));
    //指针判空
    if (insertNode == NULL) {
        return NULL;
    }
    insertNode->height = 1;
    insertNode->left = NULL;
    insertNode->right = NULL;
    insertNode->val = val;
	//由于需要前驱才能添加节点，所以需要让temp向下走一步
    //但是根节点的左右孩子不一定存在
    //如果temp向右走
    if (val >= root->val) {
        //若根节点的右孩子不存在，那么根节点的右孩子就是要插入的位置
        if (root->right == NULL) {
            root->right = insertNode;
            insertNode->parent = root;
        }
        //根节点的右孩子存在，这个时候pre就可以是temp的前驱了，通过循环插入节点
        else {
            temp = temp->right;
            while (temp != NULL) {
                if (val >= temp->val) {
                    pre = temp;
                    temp = temp->right;
                }
                else {
                    pre = temp;
                    temp = temp->left;
                }
            }
            if (val >= pre->val) {
                pre->right = insertNode;
                insertNode->parent = pre;
            }
            else {
                pre->left = insertNode;
                insertNode->parent = pre;
            }
        }
    }
    //如果temp向左走
    if(val < root->val) {
        //若根节点的左孩子不存在，那么根节点的左孩子就是要插入的位置
        if (root->left == NULL) {
            root->left = insertNode;
            insertNode->parent = root;
        }
        //根节点的左孩子存在，这个时候pre就可以是temp的前驱了，通过循环插入节点
        else {
            temp = temp->left;
            while (temp != NULL) {
                if (val >= temp->val) {
                    pre = temp;
                    temp = temp->right;
                }
                else {
                    pre = temp;
                    temp = temp->left;
                }
            }
            if (val >= pre->val) {
                pre->right = insertNode;
                insertNode->parent = pre;
            }
            else {
                pre->left = insertNode;
                insertNode->parent = pre;
            }
        }
    }
    //2.更新高度
    temp = insertNode->parent;
    while (temp != NULL) {
        //temp不可能左右子树都为空，因为有insertNode在下面，这样就只有三种情况：1.有左无右  2.有右无左  3.有左有右
        if (temp->right == NULL) {
            temp->height = temp->left->height + 1;
            temp = temp->parent;
        }
        else if (temp->left == NULL) {
            temp->height = temp->right->height + 1;
            temp = temp->parent;
        }
        else {
            if (temp->right->height >= temp->left->height) {
                temp->height = temp->right->height + 1;
                temp = temp->parent;
            }
            else {
                temp->height = temp->left->height + 1;
                temp = temp->parent;
            }
        }
    }
    //3.寻找失衡结点
    //通过path数组从下至上沿着路径寻找最近的失衡节点
    path[i++] = insertNode;
    temp = insertNode->parent;
    while (temp != NULL) {
        path[i++] = temp;
        //这里temp因为是由parent指针取出的，所以至少有一个孩子
        //这里将temp只有一个孩子的情况拿出来单独讨论是害怕取空指针里的值
        //若temp只有右孩子
        if (temp->left == NULL) {
            balnaceNum = temp->right->height;
            temp = temp->parent;
        }
        //若temp只有左孩子
        else if (temp->right == NULL) {
            balnaceNum = temp->left->height;
            temp = temp->parent;
        }
        //temp左右孩子都存在
        else {
            if (temp->left->height >= temp->right->height) {
                balnaceNum = temp->left->height - temp->right->height;
            }
            else {
                balnaceNum = temp->right->height - temp->left->height;
            }
            temp = temp->parent;
        }
        //如果找到失衡节点，退出循环，当前节点就是距离插入节点最近的失衡节点
        if (balnaceNum > 1) {
            break;
        }
    }
    //调整i的值，因为i每次都是后自增
    i--;
    //4.调整为平衡树
    //如果没有找到失衡节点说明当前树还是一个平衡树，返回根节点即可
    if (balnaceNum <= 1) {
        return root;
    }
    //否则就是找到了失衡节点，这个时候开始判断失衡类型
    else {
        //单向右型
        if (path[i]->left == path[i - 1] && path[i - 1]->left == path[i - 2]) {
            //进行额外节点保存（额外节点有可能为NULL）
            temp = path[i - 1]->right;
            pre = path[i]->parent;
            path[i]->left = temp;
            //指针要判空！！！（取指针的值之前先想想当前指针会不会是空指针）
            if (temp != NULL) {
                temp->parent = path[i];
            }
            //指针要判空！！！（取指针的值之前先想想当前指针会不会是空指针）
            if (pre != NULL) {
                if (pre->left == path[i]) {
                    pre->left = path[i - 1];
                }
                else {
                    pre->right = path[i - 1];
                }
            }
            path[i - 1]->parent = pre;
            path[i - 1]->right = path[i];
            path[i]->parent = path[i - 1];
        }
        //左右型
        if (path[i]->left == path[i - 1] && path[i - 1]->right == path[i - 2]) {
            //进行额外节点保存
            temp = path[i - 2]->left;
            pre = path[i]->parent;
            path[i - 2]->parent = path[i];
            path[i]->left = path[i - 2];
            path[i - 1]->right = temp;
            //指针要判空！！！（取指针的值的时候想想当前指针会不会是空指针）
            if (temp != NULL) {
                temp->parent = path[i - 1];
            }
            path[i - 1]->parent = path[i - 2];
            path[i - 2]->left = path[i - 1];
            //进行顺序交换便于直接套用单向右型的代码
            temp1 = path[i - 2];
            path[i - 2] = path[i - 1];
            path[i - 1] = temp1;

			//下面就是单向右型调整的代码
            temp = path[i - 1]->right;
            pre = path[i]->parent;
            path[i]->left = temp;
            //指针要判空！！！（取指针的值之前先想想当前指针会不会是空指针）
            if (temp != NULL) {
                temp->parent = path[i];
            }
            //指针要判空！！！（取指针的值之前先想想当前指针会不会是空指针）
            if (pre != NULL) {
                if (pre->left == path[i]) {
                    pre->left = path[i - 1];
                }
                else {
                    pre->right = path[i - 1];
                }
            }
            path[i - 1]->parent = pre;
            path[i - 1]->right = path[i];
            path[i]->parent = path[i - 1];
        }
        //单向左型
        if (path[i]->right == path[i - 1] && path[i - 1]->right == path[i - 2]) {
            //进行额外节点保存
            temp = path[i - 1]->left;
            pre = path[i]->parent;
            path[i]->right = temp;
            //指针要判空！！！（取指针的值之前先想想当前指针会不会是空指针）
            if (temp != NULL) {
                temp->parent = path[i];
            }
            //指针要判空！！！（取指针的值之前先想想当前指针会不会是空指针）
            if (pre != NULL) {
                if (pre->left == path[i]) {
                    pre->left = path[i - 1];
                }
                else {
                    pre->right = path[i - 1];
                }
            }
            path[i - 1]->parent = pre;
            path[i - 1]->left = path[i];
            path[i]->parent = path[i - 1];
        }
        //右左型
        if (path[i]->right == path[i - 1] && path[i - 1]->left == path[i - 2]) {
            //进行额外节点保存
            temp = path[i - 2]->right;
            pre = path[i]->parent;
            path[i - 2]->parent = path[i];
            path[i]->right = path[i - 2];
            path[i - 1]->left = temp;
            //指针要判空！！！（取指针的值之前先想想当前指针会不会是空指针）
            if (temp != NULL) {
                temp->parent = path[i - 1];
            }
            path[i - 1]->parent = path[i - 2];
            path[i - 2]->right = path[i - 1];
            //进行顺序交换便于直接套用单向右型的代码
            temp1 = path[i - 2];
            path[i - 2] = path[i - 1];
            path[i - 1] = temp1;
            
			//下面就是单向左型调整的代码
            temp = path[i - 1]->left;
            pre = path[i]->parent;
            path[i]->right = temp;
            //指针要判空！！！（取指针的值之前先想想当前指针会不会是空指针）
            if (temp != NULL) {
                temp->parent = path[i];
            }
            //指针要判空！！！（取指针的值之前先想想当前指针会不会是空指针）
            if (pre != NULL) {
                if (pre->left == path[i]) {
                    pre->left = path[i - 1];
                }
                else {
                    pre->right = path[i - 1];
                }
            }
            path[i - 1]->parent = pre;
            path[i - 1]->left = path[i];
            path[i]->parent = path[i - 1];
        }
    }
    //5.再次更新高度
    //如果进行了失衡调整的话，那么中间的节点一定是当前子树的根节点
    //而每次失衡调整只会影响这三个节点以上、且在路径上的节点
    //这里先调整当前三个节点
    for (j = 0;j < 3;j++) {
        temp = path[i - 2 + j];
        if (temp->right == NULL) {
            //指针要判空！！！（取指针的值之前先想想当前指针会不会是空指针）
            if (temp->left != NULL) {
                temp->height = temp->left->height + 1;
            }
            else {
                temp->height = 1;
            }
            temp = temp->parent;
        }
        else if (temp->left == NULL) {
            //指针要判空！！！（取指针的值之前先想想当前指针会不会是空指针）
            if (temp->right != NULL) {
                temp->height = temp->right->height + 1;
            }
            else {
                temp->height = 1;
            }
            temp = temp->parent;
        }
        else {
            if (temp->right->height >= temp->left->height) {
                temp->height = temp->right->height + 1;
                temp = temp->parent;
            }
            else {
                temp->height = temp->left->height + 1;
                temp = temp->parent;
            }
        }
    }
    //从当前子树的根节点（第二个节点）开始向上沿着路径更新高度
    temp = path[i - 1];
    //退出循环时temp指向当前树的根节点，虽然少调整了根节点的高度，但是便于函数返回（可以直接返回temp）
    while (temp->parent != NULL) {
        //temp不可能左右子树都为空，这样就只有三种情况：1.有左无右  2.有右无左  3.有左有右
        //1.有左无右
        if (temp->right == NULL) {
            temp->height = temp->left->height + 1;
            temp = temp->parent;
        }
        //2.有右无左
        else if (temp->left == NULL) {
            temp->height = temp->right->height + 1;
            temp = temp->parent;
        }
        //3.有左有右
        else {
            if (temp->right->height >= temp->left->height) {
                temp->height = temp->right->height + 1;
                temp = temp->parent;
            }
            else {
                temp->height = temp->left->height + 1;
                temp = temp->parent;
            }
        }
    }
    //调整根节点的高度（temp不需要再取下一个指针）
    if (temp->right == NULL) {
        temp->height = temp->left->height + 1;
    }
    else if (temp->left == NULL) {
        temp->height = temp->right->height + 1;
    }
    else {
        if (temp->right->height >= temp->left->height) {
            temp->height = temp->right->height + 1;
        }
        else {
            temp->height = temp->left->height + 1;
        }
    }
    //直接返回temp（此时temp指向根节点）
    return temp;
}

//测试代码
int main() {
    int choice;
    node_t* temp;
    node_t* root = (node_t*)malloc(sizeof(node_t));
    if (root == NULL) {
        return -1;
    }
    root->height = 1;
    root->left = NULL;
    root->parent = NULL;
    root->right = NULL;
    root->val = 5;
    printf("输入1测试单向右\n输入2测试右左\n输入3测试单向左\n输入4测试左右\n");
    scanf("%d", &choice);

    //测试单向右
    if (choice == 1) {
        root = avl_insert(root, 4);
        root = avl_insert(root, 3);
        if (root != NULL) {
            printf("根节点值为%d\n", root->val);
        }
        if (root->left != NULL) {
            printf("左孩子值为%d\n", root->left->val);
        }
        if (root->right != NULL) {
            printf("右孩子值为%d\n", root->right->val);
        }
    }
    //测试右左
    if (choice == 2) {
        root = avl_insert(root, 7);
        root = avl_insert(root, 6);
        if (root != NULL) {
            printf("根节点值为%d\n", root->val);
        }
        if (root->left != NULL) {
            printf("左孩子值为%d\n", root->left->val);
        }
        if (root->right != NULL) {
            printf("右孩子值为%d\n", root->right->val);
        }
    }
    //测试单向左
    if (choice == 3) {
        root = avl_insert(root, 6);
        root = avl_insert(root, 7);
        if (root != NULL) {
            printf("根节点值为%d\n", root->val);
        }
        if (root->left != NULL) {
            printf("左孩子值为%d\n", root->left->val);
        }
        if (root->right != NULL) {
            printf("右孩子值为%d\n", root->right->val);
        }
    }
    //测试左右
    if (choice == 4) {
        root = avl_insert(root, 3);
        root = avl_insert(root, 4);
        if (root != NULL) {
            printf("根节点值为%d\n", root->val);
        }
        if (root->left != NULL) {
            printf("左孩子值为%d\n", root->left->val);
        }
        if (root->right != NULL) {
            printf("右孩子值为%d\n", root->right->val);
        }
    }
    return 0;
}
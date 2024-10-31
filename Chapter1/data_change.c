#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAXSIZE 100


typedef int ElemType;
struct _seqlist {
    ElemType elem[MAXSIZE];
    int last;
};
typedef struct _seqlist SeqList;

void odd_even(SeqList* L) {
    //通过两个量分别从头尾遍历，做到只遍历一遍数组
    int front = 0, rear = L->last;
    //通过临时变量来交换前后两个值
    int temp;
    //前后量未相遇时进行循环
    while (front < rear) {
        if (L->elem[front] % 2 == 1) {
            //前面的数若是奇数front++
            front++;
            //保证每次只走一步，防止最后一次循环front++，切rear--，然后再进行一次最后一个判断
            continue;
        }
        if (L->elem[rear] % 2 == 0) {
            //后面的数若是偶数rear--
            rear--;
            //保证每次只走一步，防止最后一次循环front++，切rear--，然后再进行一次最后一个判断
            continue;
        }
        if (L->elem[front] % 2 == 0 && L->elem[rear] % 2 == 1) {
            //前面的数是偶数且后面的数是奇数就交换两个数
            temp = L->elem[front];
            L->elem[front] = L->elem[rear];
            L->elem[rear] = temp;
            front++;
            rear--;
            //保证每次只走一步，防止最后一次循环front++，切rear--，然后再进行一次最后一个判断
            continue;
        }
    }
    return;
}

int main() {
    SeqList data;
    int i = 0, j = 0;

    while (scanf("%d", &(data.elem[i])) == 1) {
        if (data.elem[i] == 0) {
            break;
        }
        i++;
    }
    i--;
    data.last = i;

    odd_even(&data);

    while (j <= i) {
        printf("%d", data.elem[j]);
        if (data.elem[j] % 2 == 0) {
            printf("偶数\t下标为%d\n",j);
            j++;
        }
        else {
            printf("奇数\t下标为%d\n",j);
            j++;
        }
    }
    return 0;
}
#include<stdio.h>
#include<string.h>

#define Stack_Size 50
typedef int ElemType;
typedef struct {
    ElemType elem[Stack_Size];
    int top;
}Stack;

int push(Stack* S, ElemType x) {
    S->elem[++(S->top)] = x;
    return 0;
}
int pop(Stack* S, ElemType* x) {
    *x = S->elem[(S->top)--];
    return 0;
}

void init_stack(Stack* S) {
    S->top = -1;
}

int compute_reverse_polish_notation(char* str) {
    //只需创建一个栈，因为遇到运算符时只需从数字栈中取出两个数字即可，不存在符号的入栈
    Stack num;
    int popNum, number, num1, num2, pushNum, i = 0;
    init_stack(&num);
    //若所需计算的表达式为空直接退出函数
    if (str == NULL) {
        return 0;
    }
    else {
        //未遍历到尾部时持续向后读入数据
        while (str[i] != '\0') {
            //如果读入的数据是数字的话
            if (str[i] >= '0' && str[i] <= '9') {
                //每次读入数字时都要将pushNum置为零防止影响下次读入数据
                pushNum = 0;
                //循环读入数字，计算数字位数大于等于1的情况
                while (1) {
                    //number用于计算pushNum位数大于1的情况
                    switch (str[i]) {
                    case'0':number = 0;
                        break;
                    case'1':number = 1;
                        break;
                    case'2':number = 2;
                        break;
                    case'3':number = 3;
                        break;
                    case'4':number = 4;
                        break;
                    case'5':number = 5;
                        break;
                    case'6':number = 6;
                        break;
                    case'7':number = 7;
                        break;
                    case'8':number = 8;
                        break;
                    case'9':number = 9;
                        break;
                    default:break;
                    }
                    //计算pushNum（特别是位数大于1的情况）
                    pushNum = pushNum * 10 + number;
                    i++;
                    //若读入空格说明当前数字已经读完
                    if (str[i] == 32) {
                        break;
                    }
                }
                //将读到的pushNum入栈
                if (num.top != Stack_Size - 1) {
                    push(&num, pushNum);
                }
            }
            //如果读入的数据是运算符的话
            else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%') {
                //碰到运算符连续弹出两个数字
                if (num.top != -1) {
                    pop(&num, &num1);
                }
                if (num.top != -1) {
                    pop(&num, &num2);
                }
                switch (str[i]) {
                //注意运算顺序，是num2-num1
                case'+':pushNum = num2 + num1;
                    break;
                case'-':pushNum = num2 - num1;
                    break;
                case'*':pushNum = num2 * num1;
                    break;
                //测试数据是有设计的，使除数不为零。一般操作时要注意除数是否为零
                case'/':pushNum = num2 / num1;
                    break;
                case'%':pushNum = num2 % num1;
                    break;
                default:break;
                }
                //将计算结果入栈
                if (num.top != Stack_Size - 1) {
                    push(&num, pushNum);
                }
                i++;
            }
            //如果读入的数据是空格的话直接读入下一位数据
            else {
                i++;
            }
        }
    }
    //若数据处理完毕后仅剩下一个数字，说明表达式合法，弹出最后的结果
    if (num.top == 0) {
        pop(&num, &popNum);
        return popNum;
    }
    //若数据处理完剩下不止一个数字，说明表达式不合法，直接退出函数
    else {
        return 0;
    }
}

int main() {
    int result,i;
    char str[50];
    char m = getchar();
    for (i = 0;m!='\n';i++) {
        str[i] = m;
        m = getchar();
    }
    str[i + 1] = '\0';
    result=compute_reverse_polish_notation(str);
    printf("%d", result);
    return 0;
}
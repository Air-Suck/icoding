#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX_NUM 100
#define true 1;
#define false 0;

typedef int bool;

typedef int VertexType;

typedef enum {
    DG, UDG
}GraphType;

typedef struct ArcNode
{
    int adjvex;
    //InfoPtr* info;
    struct ArcNode* nextarc;

}ArcNode;

typedef struct VNode
{
    VertexType data;
    ArcNode* firstarc;
}VNode;
typedef struct
{
    VNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphType type;
}ListGraph;

//返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
int locate_vertex(ListGraph* G, VertexType v); 
//要修改的部分有四个
//1.G->vertex数组中下标为V的单链表
//2.数组维护
//3.G->vertex数组其他单链表中出现adj=V的节点
//4.每个节点中的adj的值若大于V要--
bool del_vertex(ListGraph* G, VertexType v) {
    //每次都要指针判空！
    if (G == NULL) {
        return false;
    }
    //delNum用于记录删除的边数，用于最后修改G->arcnum的值
    //有向图就直接减去delNum
    //无向图由于一条边在邻接表中被记录两次，导致delNum为实际删除边数的两倍，所以减去delNum/2
    int i,delNum=0;
    int V = locate_vertex(G, v);
    ArcNode* temp,*late;
    //要删除的结点在图中如果不存在，返回false
    if (V == -1) {
        return false;
    }
    //1.删除G->vertex数组中下标为V的单链表
    temp = G->vertex[V].firstarc;
    //指针要判空！取指针内的元素使想想当前指针有没有可能是空的
    //temp指针不空时要删除单链表
    //temp指针为空时不需要做任何操作
    if (temp != NULL) {
        G->vertex[V].firstarc = NULL;
        late = temp->nextarc;
        while (late != NULL) {
            free(temp);
            delNum++;
            temp = temp->nextarc;
            late = late->nextarc;
        }
        free(temp);
        delNum++;
    }
    //2.数组维护
    //要用后项覆盖前项
    for (i = V;i < G->vexnum - 1;i++) {
        G->vertex[i] = G->vertex[i + 1];
    }
    //注意调整G->vexnum和G->arcnum的值
    G->vexnum--;
    //3.删除G->vertex数组其他单链表中adj为V的节点
    for (i = 0;i < G->vexnum;i++) {
        temp = G->vertex[i].firstarc;
        //temp指针为空时不需要对当前单链表做任何操作
        if (temp == NULL) {
            continue;
        }
        //当前第一个节点需要删除时（不带头指针是这样的）
        if (temp->adjvex == V) {
            G->vertex[i].firstarc = temp->nextarc;
            free(temp);
            delNum++;
            continue;
        }
        late = temp->nextarc;
        //遍历单链表
        while (late != NULL) {
            //若找到V了可以直接break，因为一个结点只可能有一条连向v的边
            if (late->adjvex == V) {
                temp->nextarc = late->nextarc;
                free(late);
                delNum++;
                break;
            }
            late = late->nextarc;
            temp = temp->nextarc;
        }
    }
    //4.修改结点中的adj值
    for (i = 0;i < G->vexnum;i++) {
        temp = G->vertex[i].firstarc;
        //这里写的时候恰恰好判空了，使用指针前要记得判空
        while (temp != NULL) {
            if (temp->adjvex > V) {
                temp->adjvex--;
            }
            temp = temp->nextarc;
        }
    }
    //修改G->arcnum的值
    if (G->type == DG) {
        G->arcnum = G->arcnum - delNum;
    }
    else {
        G->arcnum = G->arcnum - delNum / 2;
    }
    return true;
}
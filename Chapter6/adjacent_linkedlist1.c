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

int locate_vertex(ListGraph* G, VertexType v); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1

bool insert_vertex(ListGraph* G, VertexType v) {
    //当当前节点在当前图中存在时，返回false
    if (locate_vertex(G, v) != -1) {
        return false;
    }
    else {
        //插入顶点只需要对G->vertex数组进行操作即可
        G->vertex[G->vexnum].data = v;
        G->vertex[G->vexnum].firstarc = NULL;
        G->vexnum++;
        return true;
    }
}


bool insert_arc(ListGraph* G, VertexType v, VertexType w) {
    //计算vw两个结点在vertex数组中的角标
    int V = locate_vertex(G, v);
    int W = locate_vertex(G, w);
    //将p置为v的第一个邻接节点，便于后续判断当前边是否存在
    ArcNode* p = G->vertex[V].firstarc;
    //当v或者w节点在图中不存在时，返回false
    if (V == -1 || W == -1) {
        return false;
    }
    //查找当前边是否存在
    //不论是有向图还是无向图都只需要判断边vw是否存在即可
    while (p != NULL) {
        if (p->adjvex == W) {
            return false;
        }
        p = p->nextarc;
    }
    //当图为有向图时，只需要插入vw边
    if (G->type == DG) {
        p = (ArcNode*)malloc(sizeof(ArcNode));
        if (p == NULL) {
            return false;
        }
        //弧尾为w
        p->adjvex = W;
        //头插法
        p->nextarc = G->vertex[V].firstarc;
        G->vertex[V].firstarc = p;
    }
    //当图为无向图时，要插入vw和wv两条边
    else {
        //插入vw边
        p = (ArcNode*)malloc(sizeof(ArcNode));
        if (p == NULL) {
            return false;
        }
        //w为弧尾
        p->adjvex = W;
        //头插法
        p->nextarc = G->vertex[V].firstarc;
        G->vertex[V].firstarc = p;
        //插入wv边
        p = (ArcNode*)malloc(sizeof(ArcNode));
        if (p == NULL) {
            return false;
        }
        //v为弧尾
        p->adjvex = V;
        //头插法
        p->nextarc = G->vertex[W].firstarc;
        G->vertex[W].firstarc = p;
    }
    G->arcnum++;
    return true;
}
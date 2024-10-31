// #include<stdio.h>
// #include<stdlib.h>
#define MAX_VERTEX_NUM 100
#define true 1
#define false 0

typedef int VertexType;
typedef int bool;


typedef enum {
    DG, UDG
}GraphType;

typedef struct {
    VertexType vertex[MAX_VERTEX_NUM]; //顶点矩阵
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵
    int vexnum, arcnum;   //图的当前顶点数和弧数
    GraphType type;     //图的种类标志
}MatrixGraph;

int matrix_locate_vertex(MatrixGraph* MG, VertexType vex); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
//要注意locate函数返回的是该结点的下标
bool matrix_insert_vertex(MatrixGraph* G, VertexType v) {
    int i;
    //要插入的节点已经存在或者数组存满时，返回false
    if (matrix_locate_vertex(G, v) != -1||G->vexnum == MAX_VERTEX_NUM) {
        return false;
    }
    else {
        //此时的vexnum指向尾结点的下一个结点
        G->vertex[G->vexnum] = v;
        G->vexnum++;
        for (i = 0;i < G->vexnum;i++) {
            //将邻接矩阵中的行列初始化
            G->arcs[G->vexnum - 1][i] = 0;
            G->arcs[i][G->vexnum - 1] = 0;
        }
        return true;
    }
}

bool matrix_insert_arc(MatrixGraph* G, VertexType v, VertexType w) {
    //记录v和w的位置便于后续操作
    int V = matrix_locate_vertex(G, v);
    int W = matrix_locate_vertex(G, w);
    //当v或者w不存在时返回false（注意角标要用大写的VW，而不是小写的vw）
    //若有向图当前边存在，就是[V][W]=1
    //若是无向图的当前边存在，就是[V][W]=[W][V]=1
    //所以判断当前边是否存在只需要判断[V][W]是否为1
    if (V == -1 || W == -1||G->arcs[V][W] == 1) {
        return false;
    }
    else {
        //当图为无向图时，要将v到w和w到v的元素都置为1
        if (G->type == UDG) {
            G->arcs[V][W]=1;
            G->arcs[W][V]=1;
        }
        //当图为有向图时，只需要将v到w的元素置为1
        else {
            G->arcs[V][W]=1;
        }
        G->arcnum++;
        return true;
    }
}
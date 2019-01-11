#include <iostream>     // use cout
using namespace std;
const int MAX = 10;

//访问标志数组
int visited[MAX] = {0};

//用邻接表方式实现深度优先搜索(递归方式）
//v 传入的是第一个需要访问的顶点
void DFS(Graph G, int v)
{
    //图的顶点的搜索指针
    ArcNode *p;
    //置已访问标记
    visited[v] = 1;
    //输出被访问顶点的编号
    cout << v;
    //p指向顶点v的第一条弧的弧头结点
    p = G.vertices[v].firstarc;
    while (p != NULL)
    {
        //若p->adjvex顶点未访问,递归访问它
        if (visited[p->adjvex] == 0)
        {
            DFS(G, p->adjvex);
        }
        //p指向顶点v的下一条弧的弧头结点
        p = p->nextarc;
    }
}
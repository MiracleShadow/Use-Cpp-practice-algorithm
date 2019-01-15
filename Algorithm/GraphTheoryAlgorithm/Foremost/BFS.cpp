#include <iostream>
#include<queue>
using namespace std;

const int MAX = 10;
//辅助队列的初始化，置空的辅助队列Q，类似二叉树的层序遍历过程
queue<int> q;
//访问标记数组
bool visited[MAX];
//图的广度优先搜索算法
void BFSTraverse(Graph G, void (*visit)(int v))
{
    int v = 0;
    //初始化访问标记的数组
    for (v = 0; v < G.vexnum; v++)
    {
        visited[v] = false;
    }
    //依次遍历整个图的结点
    for (v = 0; v < G.vexnum; v++)
    {
        //如果v尚未访问，则访问 v
        if  (!visited[v])
        {
            //把 v 顶点对应的数组下标处的元素置为真，代表已经访问了
            visited[v] = true;
            //然后v入队列，利用了队列的先进先出的性质
            q.push(v);
            //访问 v，打印处理
            cout << q.back() << " ";
            //队不为空时
            while (!q.empty())
            {
                //队头元素出队,并把这个出队的元素置为 u，类似层序遍历
                Graph *u = q.front();
                q.pop();
                //w为u的邻接顶点
                for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G,u,w))
                {
                    //w为u的尚未访问的邻接顶点
                    if (!visited[w])
                    {
                        visited[w] = true;
                        //然后 w 入队列，利用了队列的先进先出的性质
                        q.push(w);
                        //访问 w，打印处理
                        cout << q.back() << " ";
                    }
                }
            }
        }
    }
}
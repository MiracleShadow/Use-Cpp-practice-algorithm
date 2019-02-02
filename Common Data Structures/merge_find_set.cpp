/*
 * 常用于：
 * 1. 判断两个元素是否属于同一集合
 * 2. 判断图是否联通或是否有环
 * 3. 配合其他算法如最小生成树Kruskal、DP等共同使用
 */

# include <iostream>

const int MAXN = 1e5+5;

int fa[MAXN];

void init(int n) {
    for (int i = 0; i < n; i++)
        fa[i] = i;
}

int find(int u) {
    return fa[u] == u ? fa[u] : fa[u] = find(fa[u]);
}

void merge(int u, int v) {
    fa[find(v)] = find(u);
}

int main()
{
    // TODO
    return 0;
}
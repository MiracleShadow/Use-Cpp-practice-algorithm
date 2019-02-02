/*
 * 主要用于查询任意两位之间元素的和，每次能且只能修改一个元素的值
 * 查询和修改都复杂度都为O(log(n))
 * 经修改后可在log(n)的复杂度下进行范围修改，但这时只能查询其中一个元素的值
 */
# include <iostream>

const int MAXN = 1e7+5;
int a[MAXN], b[MAXN][MAXN], len;

int lowbit(int x) {
    return x & (-x);
}

// 一维
void modify(int x, int data) { 
    while(x <= len) {
        a[x] += data;
        x += lowbit(x);
    }
}

int get_sum(int x) {
    int ret = 0;
    while(x != 0) {
        ret += a[x];
        x -= lowbit(x);
    }
    return ret;
}

// 二维
void modify(int x, int y, int data) {
    for(int i = x; i < len; i += lowbit(x))
        for(int j = y; j < len; j += lowbit(x))
            b[i][j] += data;
}

int get_sum(int x, int y) {
    int ret = 0;
    for(int i = x; i > 0; i -= lowbit(i))
        for(int j = y; j > 0; j -= lowbit(j))
            ret += b[i][j];
    return ret;
}

int main()
{
    // TODO
    return 0;
}
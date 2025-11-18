/*
最优装载问题
有一批集装箱要装上一艘载重量为 c 的轮船。
其中集装箱 i 的重量为 wi。
最优装载问题要求确定在装载体积不受限制的情况下，
将尽可能多的集装箱装上轮船。
*/
#include <iostream>

// 将集装箱从轻到重排序，轻的先装
template<typename Type>
void loading(int x[], Type w[], Type c, int n) {
    int* t = new int[n + 1]; // 按重量记录物品编号
    sorted(t, w, n); // 按重量从轻到重排序
    for (int i = 1; i <= n; i++)
        x[i] = 0; // 初始化
    for (int i = 1; i <= n && w[t[i]] <= c; i++) {
        x[t[i]] = 1; // 能装则装
        c -= w[t[i]]; // 剩余载重减少
    }
}
#include <iostream>
#include <limits>
using namespace std;

int n = 5; // 城市数量
int a[5][5]; // 表示城市间权重的邻接矩阵
int x[5]; // 当前路径
int current_c = 0; // 当前路径的成本
int best_x[5]; // 最优路径
int best_c  = numeric_limits<int>::max(); // 最低成本

// （1）不加界值函数的TSP实现
/*
bool check(int t) {
    if (t < 1)
        return 1;
    if (t >= n)
        return 0;
    if (t < n) {
        for (int i = 0; i < t; i++) {
            if (x[i] == x[t])
                return 0;
        }
        if (a[x[t - 1]][x[t]] == -1)
            return 0;
        if (t == n - 1)
            if (a[x[t]][x[0]]== -1)
                return 0;
    }
    return 1;
}

// 计算当前路径的成本
int cost(int x[]) {
    int cost = 0;
    for (int i = 0; i < n - 1; i++)
        cost += a[x[i]][x[i + 1]];
    cost += a[x[n - 1]][x[0]];
    return cost;
}

// 不加界值函数的TSP实现
void TSP_backtrack(int t) {
    if (t == n) {
        if (cost(x) < best_c) {
            best_c = cost(x);
            for (int i = 0; i < n; i++)
                best_x[i] = x[i];
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            x[t] = i;
            if (check(t)) {
                TSP_backtrack(t + 1);
            }
        }
    }
}
*/

// （2）使用界值函数
bool check(int t) {
    int from = x[t - 1];
    int to = x[t];

    if (a[from][to] == -1)
        return 0;
    if (t == n - 1) {
        if (a[x[t]][0] == -1)
            return 0;
    }
    return 1;
}

void TSP_backtrack(int t) {
    if (t == n) {
        best_c = current_c;
        for (int i = 0; i < n; i++)
            best_x[i] = x[i];
    }
    else {
        for (int i = t; i < n; i++) {
            swap(x[i], x[t]);
            if (check(t)) {
                if (t < n - 1 && current_c + a[x[t - 1]][x[t]] < best_c) {
                    current_c += a[x[t - 1]][x[t]];
                    TSP_backtrack(t + 1);
                    current_c -= a[x[t - 1]][x[t]];
                }
                if (t == n - 1 && current_c + a[x[t - 1]][x[t]] + a[x[t]][x[0]] < best_c) {
                    current_c += a[x[t - 1]][x[t]] + a[x[t]][x[0]];
                    TSP_backtrack(t + 1);
                    current_c -= a[x[t - 1]][x[t]] + a[x[t]][x[0]];
                }
            }
            swap(x[i], x[t]);
        }
    }
}

int main() {
int graph[5][5] = {
    {0, 2, 9, 100, 3},
    {2, 0, 4, 7, 5},
    {9, 4, 0, 3, 8},
    {100, 7, 3, 0, 6},
    {3, 5, 8, 6, 0}
};


    for (int i = 0; i < n; i++) {
        x[i] = i;
        for (int j =0; j < n; j++)
            a[i][j] = graph[i][j];
    }

    TSP_backtrack(1);

    for (int i = 0; i < n; i++)
        cout << best_x[i] << " ";
    cout << endl;
    cout << best_c << endl;
}
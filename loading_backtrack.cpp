#include <iostream>
using namespace std;

int n = 7;// 集装箱数量
int w[7]; // 集装箱重量
int x[7]; // 当前解
int best_x[7]; // 最优解
int best_w; // 最优载重量
int cw; // 当前载重量
int c1 = 152; // 第一艘轮船载重量
int c2 = 130; // 第二艘轮船载重量
int r = 0; // 剩余可选集装箱重量之和

bool found = false; // 若载重量恰好等于c1，则已经找到理论最优解，递归直接结束

void loading(int t) {
    if (found) return;

    if (t == n) {
        if (cw > best_w) {
            best_w = cw;
            if (best_w == c1)
                found = true;
            for (int i = 0; i < n; i++) {
                best_x[i] = x[i];
            }
        }
    }
    else {
        r -= w[t]; // t + 1 ~ n的总重量
        if (cw + w[t] <= c1) {
            x[t] = 1;
            cw += w[t];
            loading(t + 1);
            x[t] = 0;
            cw -= w[t];
        }
        if (cw + r > best_w) {
            x[t] = 0;
            loading(t + 1);
        }
        r += w[t];
    }
}

int main() {
    int weight[] = {90, 80, 40, 30, 20, 12, 10};
    for (int i = 0; i < n; i++) {
        r += weight[i];
        w[i] = weight[i];
    }

    loading(0);
    int remainW = r - best_w;
    if (remainW <= c2) {
        cout << "Yes" << endl;
        cout << best_w << endl;
        for (int i = 0; i < n; i++) {
            cout << best_x[i] << " ";
        }
    }
    else {
        cout << "No" << endl;
    }
}
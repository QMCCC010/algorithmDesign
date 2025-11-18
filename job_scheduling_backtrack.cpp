#include <iostream>
#include <limits>
using namespace std;

#define N 3

int n = N; // 作业个数
int F[2][N]; // 作业在机器一和机器二上的加工时间
int best_x[N]; // 最佳调度
int best_c = numeric_limits<int>::max();
int current_c = 0; // 记录当前完成时间和
int x[N]; // 当前序列
int M1 = 0; // 机器1的完成时间
int M2[N] = {0}; // 机器2的完成时间

void job_scheduling(int t) {
    if (t == n) {
        if (current_c < best_c) {
            best_c = current_c;
            for (int i = 0; i < n; i ++) {
                best_x[i] = x[i];
            }
        }
    }
    else {
        for (int i = t; i < n; i++) {
            swap(x[i], x[t]);
            M1 += F[0][x[t]];
            M2[t] = max(t > 0 ? 0 : M2[t - 1], M1) + F[1][x[t]];
            current_c += M2[t];

            if (current_c < best_c) {
                job_scheduling(t + 1);
            }
            M1 -= F[1][x[t]];
            current_c -= M2[t];
            swap(x[i], x[t]);
        }
    }
}

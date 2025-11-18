#include <iostream>
using namespace std;

// p存储矩阵链中每个矩阵的大小，如3x5,5x4则对应p[0] = 3,p[1] = 5, p[2] = 4.
// n表示矩阵个数
// m[i][j]表示长度为矩阵从i到j所需的最小计算量
// s[i][j]表示从矩阵i到矩阵j的最佳分割位置
void MatrixChain(int* p, int n, int** m, int** s) {
    for (int i = 1; i <= n; i++)
        m[i][i] = 0;
    for (int r = 2; r <= n; r++) {
        for (int i = 1; i <= n - r + 1; i++) {
            int j = r + i - 1;
            m[i][j] = m[i + 1][j] + p[i - 1]*p[i]*p[j];
            s[i][j] = i;
            for (int k = i + 1; k < j; k++) {
                if (m[i][k] + m[k][j] + p[i-1]*p[k]*p[j] < m[i][j]) {
                    m[i][j] = m[i][k] + m[k + 1][j] + p[i-1]*p[k]*p[j];
                    s[i][j] = k;
                }
            }
        }
    }
}

void TraceBack(int i, int j, int** s) {
    if (i == j)
        cout << "A" << i;
    else {
        cout << "(";
        TraceBack(i, s[i][j], s);
        TraceBack(s[i][j] + 1, j, s);
        cout << "）";
    }
}
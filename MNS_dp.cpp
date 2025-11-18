#include <iostream>
using namespace std;

void MNS(int C[], int n, int** Size) {
    for (int j = 0; j < C[1]; j++)
        Size[1][j] = 0;
    for (int j = C[1]; j <= n; j++)
        Size[1][j] = 1;
    
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < C[i]; j++)
            Size[i][j] = Size[i - 1][j];
        for (int j = C[i]; j <= n; j++)
            Size[i][j] = max(Size[i - 1][C[i] - 1] + 1, Size[i - 1][j]);
    }
}
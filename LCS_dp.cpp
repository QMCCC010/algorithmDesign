#include <iostream>
using namespace std;

//c[i][j]记录X[i]和Y[j]的最长公共子序列长度
// b[i][j]记录X[i]和Y[j]最长公共子序列的来源，便于回溯寻找子序列
void LCS (int m, int n, char* X, char* Y, int** c, int** b) {
    for (int i = 1; i <= m; i++)
        c[i][0] = 0;
    for (int i = 1; i <= n; i++)
        c[0][i] = 0;
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i] == Y[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            }
            else if (c[i - 1][j] > c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = 2;
            }
            else {
                c[i][j] = c[i][j - 1];
                b[i][j] = 3;
            }
        }
    }
}

// 辅助函数：分配二维数组
int** allocate2D(int rows, int cols) {
    int** arr = new int*[rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols]();
    }
    return arr;
}

// 辅助函数：释放二维数组
void free2D(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

void TraceBack(int i, int j, char* X, int** b) {
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == 1) {
        TraceBack(i - 1, j - 1, X, b);
        cout << X[i];
    }
    else if (b[i][j] == 2)
        TraceBack(i - 1, j, X, b);
    else
        TraceBack(i, j - 1, X, b);
}

int main() {
    // 测试用例1：经典案例
    cout << "Test 1: X=ABCBDAB, Y=BDCABA" << endl;
    char X1[] = " ABCBDAB";
    char Y1[] = " BDCABA";
    int m1 = 7, n1 = 6;
    int** c1 = allocate2D(m1 + 1, n1 + 1);
    int** b1 = allocate2D(m1 + 1, n1 + 1);
    LCS(m1, n1, X1, Y1, c1, b1);
    cout << "LCS length: " << c1[m1][n1] << endl;
    cout << "LCS: ";
    TraceBack(m1, n1, X1, b1);
    cout << "\n" << endl;
    free2D(c1, m1 + 1);
    free2D(b1, m1 + 1);

    // 测试用例2：完全相同
    cout << "Test 2: X=ABC, Y=ABC" << endl;
    char X2[] = " ABC";
    char Y2[] = " ABC";
    int m2 = 3, n2 = 3;
    int** c2 = allocate2D(m2 + 1, n2 + 1);
    int** b2 = allocate2D(m2 + 1, n2 + 1);
    LCS(m2, n2, X2, Y2, c2, b2);
    cout << "LCS length: " << c2[m2][n2] << endl;
    cout << "LCS: ";
    TraceBack(m2, n2, X2, b2);
    cout << "\n" << endl;
    free2D(c2, m2 + 1);
    free2D(b2, m2 + 1);

    // 测试用例3：无公共子序列
    cout << "Test 3: X=ABC, Y=DEF" << endl;
    char X3[] = " ABC";
    char Y3[] = " DEF";
    int m3 = 3, n3 = 3;
    int** c3 = allocate2D(m3 + 1, n3 + 1);
    int** b3 = allocate2D(m3 + 1, n3 + 1);
    LCS(m3, n3, X3, Y3, c3, b3);
    cout << "LCS length: " << c3[m3][n3] << endl;
    cout << "LCS: ";
    TraceBack(m3, n3, X3, b3);
    cout << "\n" << endl;
    free2D(c3, m3 + 1);
    free2D(b3, m3 + 1);

    // 测试用例4：子序列关系
    cout << "Test 4: X=ACE, Y=ABCDE" << endl;
    char X4[] = " ACE";
    char Y4[] = " ABCDE";
    int m4 = 3, n4 = 5;
    int** c4 = allocate2D(m4 + 1, n4 + 1);
    int** b4 = allocate2D(m4 + 1, n4 + 1);
    LCS(m4, n4, X4, Y4, c4, b4);
    cout << "LCS length: " << c4[m4][n4] << endl;
    cout << "LCS: ";
    TraceBack(m4, n4, X4, b4);
    cout << "\n" << endl;
    free2D(c4, m4 + 1);
    free2D(b4, m4 + 1);

    // 测试用例5：长字符串
    cout << "Test 5: X=AGGTAB, Y=GXTXAYB" << endl;
    char X5[] = " AGGTAB";
    char Y5[] = " GXTXAYB";
    int m5 = 6, n5 = 7;
    int** c5 = allocate2D(m5 + 1, n5 + 1);
    int** b5 = allocate2D(m5 + 1, n5 + 1);
    LCS(m5, n5, X5, Y5, c5, b5);
    cout << "LCS length: " << c5[m5][n5] << endl;
    cout << "LCS: ";
    TraceBack(m5, n5, X5, b5);
    cout << endl;
    free2D(c5, m5 + 1);
    free2D(b5, m5 + 1);

    return 0;
}




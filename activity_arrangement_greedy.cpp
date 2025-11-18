#include <iostream>
using namespace std;

 /*
#define N 10 // 活动个数
int s[N]; // 活动开始时间
int f[N]; // 活动结束时间
bool A[N]; // 活动是否选择
*/


// 活动按结束时间从早到晚排序
template<typename Type>
void GreedySelected(int n, Type s[], Type f[], bool A[]) {
    A[1] = true; // 第一个活动一定在最优安排中

    int j = 1; // 记录当前活动的结束时间，用于安排下一个活动
    for (int i = 2; i <= n; i++) {
        if (s[i] >= f[j]) {
            A[i] = true;
            j = i;
        }
        else {
            A[i] = false;
        }
    }
}
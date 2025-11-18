#include <iostream>
#include <limits>
using namespace std;

#define MaxInt numeric_limits<ll>::max()

//n 节点数，v源节点，dist特殊路径，prev前驱节点矩阵， c邻接矩阵
template<typename Type>
void dijkstra(int n, Type dist, int prev[], Type** c) {
    bool s[n]; // 记录节点是否被选择过
    for (int i = 1; i <=n; i++) {
        dist[i] = c[v][i]; // 特殊路径初始化为权值
        s[i] = false;
        if (dist[i] == MaxInt) // 如果节点和初始节点没有边连接
            prev[i] = -1;
        else 
            prev[i] = v;
    }
    dist[v] = 0;
    s[v] = true;
    prev[v] = -1;
    
    for (int i = 1; i < n; i++) { // 除去源节点后还有n - 1个节点
        temp = MaxInt;
        int u = v;

        for (int j = 1; j <= n; j++) { // 贪心法选择节点（即当前路径中dist最小的点）
            if (!s[j] && dist[j] < temp) {
                temp = dist[j];
                u = j;
            }
        }
        s[u] = true;
        for (int j = 1; i <= n; j++) {
            if(!s[j] && c[u][j] < MaxInt) {
                tempDist = dist[u] + c[u][j];
                if (tempDist < dist[j]) {
                    dist[j] = tempDist;
                    prev[j] = u;
                }
            }
        }
    }
}
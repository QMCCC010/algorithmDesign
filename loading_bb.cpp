#include <iostream>
#include <queue>
#include <memory>
#include <vector>
using namespace std;

struct Qnode {
    int cw;
    Qnode* parent;
    bool Lchild;
};

queue<Qnode> Q;
int bestw = 0;
vector<int> bestH;

void MaxLoadingFIFOImpr(int w[], int c, int n) {
    Q.push({-1, nullptr, false});
    int cw = 0;
    int i = 1;
    int r = 0; // 记录剩余容量

    for (int j = 2; j <= n; j++)
        r += w[j];
    Qnode root; // 根节点

    while (Q.size() != 0) {
        
    }
}


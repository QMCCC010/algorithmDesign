#include <iostream>
#include <queue>
#include <memory>
#include <vector>
using namespace std;

/*
struct Qnode {
    int cw;
    Qnode* parent;
    bool Lchild;

};

int n;
queue<Qnode> Q;
Qnode bestNode;
int bestw = 0;
vector<int> bestH;

void addLiveNode(int cw, Qnode parent, bool Lchild, int i) {
    if (i == (n + 1)) {
        if (cw >= bestw)
            bestw = cw;
    }
    else {
        Q.push({cw, &parent, Lchild});
    }
}

void MaxLoadingFIFOImpr(int w[], int c, int n) {
    Q.push({-1, nullptr, false});
    int cw = 0;
    int i = 1; // 记录层数，同时记录放入哪一个物品
    int r = 0; // 记录剩余容量

    for (int j = 2; j <= n; j++)
        r += w[j];
    Qnode root; // 根节点

    while (Q.size() != 0) {
        if (w[i] + cw <= c) { // 左子树判断约束
            if (cw + w[i] > bestw) {
                bestw = cw + w[i];
                bestNode = {bestw, &root, true};
            }
            addLiveNode(cw + w[i], root, true, i + 1);
        }

        if (cw + r > bestw) { // 右子树判断界（利用界剪枝）
            addLiveNode(cw, root, false, i + 1);
        }
        root = Q.front(); // 取下一个节点，作为新的根节点
        Q.pop();
        cw = root.cw;
        if (cw == -1) {
            if (Q.size() == 0)
                break;
            Q.push({-1, nullptr, false});
            root = Q.front();
            Q.pop();
            cw = root.cw;
            i++; // 进入下一层
            r -= w[i];
        }
    }
    while(bestNode.parent != nullptr) {
        bestH.push_back(bestNode.Lchild);
        bestNode = *bestNode.parent;
    }
}
*/

/*-------------------------------------------------------------------*/
struct Node {
    int uweight; // 记录节点的上界
    int level; // 记录节点的层
    Node* parent; // 父节点
    bool Lchild; // 记录是否为左子树

        // 按上界从大到小排序 (大顶堆)
    bool operator<(const Node& other) const {
        return uweight < other.uweight;  // 注意: < 实现大顶堆
    }
};

priority_queue<Node> heap;
int n;
int bestw = 0;
vector<bool> bestH;
Node bestNode;

void addLiveNode(int uweight, int level, Node parent, bool Lchild, int n) {
    if (level == (n + 1)) {
        if (uweight > bestw)
            bestw = uweight;
    }
    else {
        heap.push({uweight, level, &parent, Lchild});
    }
}

void MaxLoadingPrior(int w[], int c, int n) {
    Node cNode; // 当前拓展节点
    int i = 1; // 当前层数
    int cw = 0; // 当前载重量

    int* r = new int[n+2];
    r[n+1] = 0; // 边界条件
    for (int j = n; j > 0; j--) // 记录每一层的剩余重量
        r[j] = r[j+1] + w[j];
    
    while (i != (n + 1)) {
        if (cw + w[i] <= c) { // 左节点判断约束
            if (cw + w[i] > bestw) { // 提前更新bestw
                bestw = cw + w[i];
                bestNode = {bestw + r[i+1], i+1, &cNode, true};
            }
            addLiveNode(cw + w[i] + r[i+1], i+1, cNode, true, n);
        }
        if (cw + r[i+1] > bestw) { // 利用上界剪枝
            addLiveNode(cw + r[i+1], i+1, cNode, false, n);
        }
        if (heap.empty())
            break;
        cNode = heap.top();
        heap.pop();
        i = cNode.level;
        cw = cNode.uweight - r[i];
    }
    while(bestNode.parent != nullptr) {
        bestH.push_back(bestNode.Lchild);
        bestNode = *bestNode.parent;
    }

    delete[] r;
}

// 重置全局变量
void reset() {
    while (!heap.empty()) heap.pop();
    bestH.clear();
    bestw = 0;
    bestNode = {0, 0, nullptr, false};
}

int main() {
    // 测试用例1: 基本情况
    cout << "========== 测试用例1 ==========" << endl;
    cout << "物品重量: [20, 15, 10]" << endl;
    cout << "背包容量: 30" << endl;
    
    int n1 = 3;
    int w1[] = {0, 20, 15, 10};  // w[0]不使用
    int c1 = 30;
    
    MaxLoadingPrior(w1, c1, n1);
    cout << "最大装载重量: " << bestw << endl;
    cout << "期望结果: 30 (选20+10 或 15+15)" << endl;
    cout << endl;
    
    reset();
    
    // 测试用例2: 无法全部装入
    cout << "========== 测试用例2 ==========" << endl;
    cout << "物品重量: [16, 15, 15, 10]" << endl;
    cout << "背包容量: 50" << endl;
    
    int n2 = 4;
    int w2[] = {0, 16, 15, 15, 10};  // 总重56 > 50
    int c2 = 50;
    
    MaxLoadingPrior(w2, c2, n2);
    cout << "最大装载重量: " << bestw << endl;
    cout << "期望结果: 46 (选16+15+15)" << endl;
    cout << endl;
    
    reset();
    
    // 测试用例3: 恰好装满
    cout << "========== 测试用例3 ==========" << endl;
    cout << "物品重量: [10, 20, 30]" << endl;
    cout << "背包容量: 30" << endl;
    
    int n3 = 3;
    int w3[] = {0, 10, 20, 30};
    int c3 = 30;
    
    MaxLoadingPrior(w3, c3, n3);
    cout << "最大装载重量: " << bestw << endl;
    cout << "期望结果: 30 (选30 或 10+20)" << endl;
    cout << endl;
    
    reset();
    
    // 测试用例4: 所有物品都能装入
    cout << "========== 测试用例4 ==========" << endl;
    cout << "物品重量: [5, 10, 8, 7]" << endl;
    cout << "背包容量: 50" << endl;
    
    int n4 = 4;
    int w4[] = {0, 5, 10, 8, 7};  // 总重30 < 50
    int c4 = 50;
    
    MaxLoadingPrior(w4, c4, n4);
    cout << "最大装载重量: " << bestw << endl;
    cout << "期望结果: 30 (全部选择)" << endl;
    cout << endl;
    
    reset();
    
    // 测试用例5: 容量很小
    cout << "========== 测试用例5 ==========" << endl;
    cout << "物品重量: [25, 30, 40, 35]" << endl;
    cout << "背包容量: 50" << endl;
    
    int n5 = 4;
    int w5[] = {0, 25, 30, 40, 35};
    int c5 = 50;
    
    MaxLoadingPrior(w5, c5, n5);
    cout << "最大装载重量: " << bestw << endl;
    cout << "期望结果: 40 (只选40)" << endl;
    cout << endl;
    
    reset();
    
    // 测试用例6: 大规模测试
    cout << "========== 测试用例6 ==========" << endl;
    cout << "物品重量: [10, 20, 30, 40, 50, 60]" << endl;
    cout << "背包容量: 100" << endl;
    
    int n6 = 6;
    int w6[] = {0, 10, 20, 30, 40, 50, 60};
    int c6 = 100;
    
    MaxLoadingPrior(w6, c6, n6);
    cout << "最大装载重量: " << bestw << endl;
    cout << "期望结果: 100 (选10+30+60 或其他组合)" << endl;
    cout << endl;
    
    return 0;
}
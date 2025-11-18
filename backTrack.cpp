#include <iostream>
#include <math.h>

int n = 8;
int x[8];
int sum = 0;

bool check(int pos) {
    for (int i = 0; i <pos; i++) {
        if (abs(x[i] - x[pos]) == abs(i - pos) || x[i] == x[pos])
            return 0;
    }
    return 1;
}

void queen_backtrack(int t) {
    if (t == n) {
        for (int i = 0; i < n; i++)
            std::cout << x[i] << " ";
        std::cout << std::endl;
        sum++;
    }
    else {
        for (int i = 1; i <= n; i++) {
            x[t] = i;
            if (check(t))
                queen_backtrack(t + 1);
        }
    }
}

int main() {
    queen_backtrack(0);
    std::cout << sum << std::endl;
}
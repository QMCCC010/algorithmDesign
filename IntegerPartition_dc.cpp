#include <iostream>

int IntegerPartition(int n, int m) {
    if (n <= 0 || m <= 0)
        return 0;
    if (n == 1 || m == 1)
        return 1;
    if (n < m)
        return IntegerPartition(n, n);
    if (n == m)
        return IntegerPartition(n, m - 1) + 1;
    return IntegerPartition(n, m - 1) + IntegerPartition(n - m, m);
}

int main() {
    std::cout << IntegerPartition(6, 6);
}
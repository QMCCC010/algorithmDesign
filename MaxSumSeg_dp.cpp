#include <iostream>
#include <limits>
using namespace std;

#define MIN numeric_limits<int>::min();

int MaxSumSeg(int n, int* a) {
    int sum = MIN;
    int b = 0;
    for (int i = 1; i <= n; i++) {
        if (b > 0)
            b += a[i];
        else
            b = a[i];
        if (b > sum)
            sum = b;
    }
    return sum;
}
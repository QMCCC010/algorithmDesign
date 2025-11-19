#include <iostream>
using namespace std;

int mcount = 0;

template<typename Type>
void perm(Type list[], int k, int n) {
    if (k == n) {
        mcount++;
        for (int i = 0; i < n; i++)
            cout << list[i];
        cout << endl;
    }
    else {
        for (int i = k; i < n; i++) {
            swap(list[k], list[i]);
            perm(list, k + 1, n);
            swap(list[k], list[i]);
        }
    }
}

int main() {
    int list[] = {1, 2, 3, 4};
    perm(list, 0, 4);
    cout << mcount;
}
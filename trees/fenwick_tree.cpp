// template for binary indexed tree (points update range sum)
/*
time complexity: O(logN) for each operation
*/
#include <bits/stdc++.h>
#define MX 200000
using namespace std;

struct BIT {
    vector<int> tree;
    int size;

    BIT () {}
    BIT(int n) {
        size = n;
        tree.assign(n, 0);
    }

    int sum(int pos){
        int ans = 0;
        for (; pos >= 1; pos -= pos & -pos)
            ans += tree[pos];
        return ans;
    }

    void add(int pos, int value){
        for (; pos <= size; pos += pos & -pos)
            tree[pos] += value;
    }
};

int main() {
    return 0;
}

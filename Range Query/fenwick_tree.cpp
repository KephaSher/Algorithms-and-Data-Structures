// Template for Binary Indexed Tree (or Fenwick tree)
/*

|    
---|  |      |          |
---------|  ----| |     ----|  |       |    
---------------------|  ------------|  -----|  |  
-----------------------------------------------------
1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16 

example:
n = 13
bin(n) = 1101

(n & -n) gives the n without the last bit.

1. n - (n & -n) = 1100 = 12 (jump = 1)
2. n - (n & -n) = 1000 = 8 (jump = 4)
3. n - (n & -n) = 0000 = 0 (jump = 8)


Time complexity: O(logN) for each operation
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

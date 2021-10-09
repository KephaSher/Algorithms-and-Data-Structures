// template for sparse table, queries RMQs in O(1), setup takes O(N logN)
#include <bits/stdc++.h>
#define MX 100000
using namespace std;

int N;
int A[MX + 1];
int table[MX + 1][20];

int query(int a, int b) {
    // log the length of the range
    if (a > b) swap(a, b);
    int mid = (int) log2(b - a + 1);
    // b - (1 << mid) + 1 is because the range is inclusive, so without +1 you miss the last element
    // mid = 2, a = 1, b = 7 table[1][2] -> [1, 4], table[4][2] -> [4, 7].
    return min(table[a][mid], table[b - (1 << mid) + 1][mid]);
}

int main() {
    cin >> N;
    
    for (int i = 1; i <= N; i++)
        cin >> A[i], table[i][0] = A[i];

    for (int i = 1; (1 << i) <= N; i++) // size of the range (2^i, i >= 1)
        for (int j = 1; (j + (1 << i) - 1) <= N; j++) // starting position
            table[j][i] = min(table[j][i - 1], table[j + (1 << (i - 1))][i - 1]);

    cout << query(3, 5) << endl;
}

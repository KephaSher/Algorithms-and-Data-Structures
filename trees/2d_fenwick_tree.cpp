#include <bits/stdc++.h>
#define MX 1000
using namespace std;

int N, M, Q;
int bit[MX + 1][MX + 1];

void add(int x, int y, int val) {
    for (; x <= N; x += x & -x)
        for (int i = y; i <= M; i += i & -i)
            bit[x][i] += val;
}

int sum(int x, int y) {
    int sum = 0;
    for (; x >= 1; x -= x & -x)
        for (int i = y; i >= 1; i -= i & -i)
            sum += bit[x][i];
    return sum;
}

int query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x1 - 1, y1) - sum(x1, y1 - 1) + sum(x1 - 1, y1 - 1);
}

int main() {
    // cin >> N >> Q;
    N = 5, M = 5;

    int mat[5][5] = { {0, 0, 0, 0, 0},
                    {0, 1, 2, 3, 4},
                    {0, 2, 3, 4, 5},
                    {0, 3, 4, 5, 6},
                    {0, 4, 5, 6, 7} };

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            add(i, j, mat[i][j]);

    cout << query(1, 1, 3, 3) << endl;
    // 27
}

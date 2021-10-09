// 2D segment tree, memory: O(16NM), time: O(logN * logM)
#include <bits/stdc++.h>
using namespace std;

struct SegTree2D {
    int n = 1, m = 1;
    vector<vector<int>> sums;

    SegTree2D (int _n, int _m) {
        while (n < _n) n *= 2;
        while (m < _m) m *= 2;

        sums.assign(2 * n, vector<int> (2 * m, 0));
    }

    SegTree2D (vector<vector<int>> &A) {
        // A is 0 - based
        int _n = A.size();
        int _m = A[0].size();

        while (n < _n) n *= 2;
        while (m < _m) m *= 2;
        sums.assign(2 * n, vector<int> (2 * m, 0));

        for (int i = n; i < n + _n; i++) {
            for (int j = m; j < m + _m; j++)
                sums[i][j] = A[i - n][j - m];
            for (int j = m - 1; j >= 1; j--)
                sums[i][j] = sums[i][j * 2] + sums[i][j * 2 + 1];
        }

        for (int i = n - 1; i >= 1; i--)
            for (int j = 1; j <= 2 * m - 1; j++)
                sums[i][j] = sums[i * 2][j] + sums[i * 2 + 1][j];
    }

    void update(int x, int y, int v) {
        x += n - 1;
        y += m - 1;
        sums[x][y] = v;

        for (int i = y / 2; i >= 1; i /= 2) 
            sums[x][i] = sums[x][i * 2] + sums[x][i * 2 + 1];
        
        for (x /= 2; x >= 1; x /= 2)
            for (int i = y; i >= 1; i /= 2)
                sums[x][i] = sums[x * 2][i] + sums[x * 2 + 1][i];
    }

    int query(int x, int y1, int y2) {
        int ret = 0;
        while (y1 <= y2) {
            if (y1 % 2 == 1) ret += sums[x][y1++];
            if (y2 % 2 == 0) ret += sums[x][y2--];
            y1 /= 2, y2 /= 2;
        }
        return ret;
    }

    int query(int x1, int y1, int x2, int y2) {
        x1 += n - 1, x2 += n - 1;
        y1 += m - 1, y2 += m - 1;
        int ret = 0;

        while (x1 <= x2) {
            if (x1 % 2 == 1) ret += query(x1++, y1, y2);
            if (x2 % 2 == 0) ret += query(x2--, y1, y2);
            x1 /= 2, x2 /= 2;
        }

        return ret;
    }
};

int main() {
    vector<vector<int>> v = {{0, 3, 2, 1}, {6, 0, 4, 0}};
    SegTree2D S = SegTree2D(v);

    return 0;
}

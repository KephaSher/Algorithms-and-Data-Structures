// Lazy segment sums (range query range update)
#include <bits/stdc++.h>
#define MX 200000
using namespace std;

struct LazySegTree {
    int size;
    vector<int> sums, lazy; // sums is [0...2*size-1]

    LazySegTree() {}

    LazySegTree (int n) {
        size = 1;
        while (size < n) size *= 2;
        sums.assign(2 * size, 0);
        lazy.assign(2 * size, 0);
    }

    void propagate(int node, int curL, int curR, int val) {
        sums[node] += (curR - curL + 1) * val;
        if (curL != curR) {
            lazy[node * 2] += val;
            lazy[node * 2 + 1] += val;
        }
        lazy[node] = 0;
    }

    void update(int node, int curL, int curR, int L, int R, int value) {
        // propogate lazy value of node to children
        if (lazy[node] != 0)
            propagate(node, curL, curR, lazy[node]);

        // if out of bounds
        if (curR < L || curL > R || curL > curR)
            return;

        // if subtree is completely in [L, R]
        if (L <= curL && curR <= R) {
            propagate(node, curL, curR, value);
            return;
        }

        // if subtree is in part of [L, R]
        int mid = (curL + curR) / 2;
        update(node * 2, curL, mid, L, R, value);
        update(node * 2 + 1, mid + 1, curR, L, R, value);

        sums[node] = sums[node * 2] + sums[node * 2 + 1];
    } 

    void update(int L, int R, int V) {
        if (sums.size() == 0) { cout << "not initialized!\n"; abort(); }
        update(1, size, 2 * size - 1, L + size - 1, R + size - 1, V);
    }

    int query(int node, int curL, int curR, int L, int R) {
        // propogate to children
        if (lazy[node] != 0)
            propagate(node, curL, curR, lazy[node]);

        // out of bounds
        if (curR < L || curL > R || curL > curR) 
            return 0;

        // if completely in [A, B]
        if (L <= curL && curR <= R) 
            return sums[node];

        // if not completely in [A, B]
        int mid = (curL + curR) / 2;
        return query(node * 2, curL, mid, L, R) 
            + query(node * 2 + 1, mid + 1, curR, L, R);
    }

    int query(int L, int R) {
        return query(1, size, 2 * size - 1, L + size - 1, R + size - 1);
    }
};

int N, Q;
int A[MX + 1];
LazySegTree S;

int main() {
    cin >> N >> Q;

    S = LazySegTree(N);

    for (int i = 1; i <= N; i++) {
        int x; cin >> x;
        S.update(i, i, x);
    }

    for (int i = 1; i <= Q; i++) {
        int op; cin >> op;
        if (op == 1) {
            int a, b, c; cin >> a >> b >> c;
            S.update(a, b, c);
        } else {
            int a, b; cin >> a >> b;
            cout << S.query(a, b) << "\n";
        }
    }
    return 0;
}

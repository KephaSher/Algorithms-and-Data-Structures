#include <bits/stdc++.h>
#define MX 200000
using namespace std;

struct Node {
    Node *left, *right;
    int val;

    Node() {}

    Node (Node *l, Node *r, int v) {
        left = l, right = r, val = v;
    }
};

struct SparseSegTree {
    Node* root;

    SparseSegTree() {
        root = new Node(NULL, NULL, 0);
    }

    void update(Node* node, int L, int R, int pos, int v) {
        if (L == pos && R == pos) {
            node->val = v;
            return;
        }

        int mid = (L + R) / 2;
        if (pos <= mid) {
            if (!node->left) node->left = new Node(NULL, NULL, 0);
            update(node->left, L, mid, pos, v);
        } else {
            if (!node->right) node->right = new Node(NULL, NULL, 0);
            update(node->right, mid + 1, R, pos, v);
        }

        node->val = 0;
        if (node->left) node->val += node->left->val;
        if (node->right) node->val += node->right->val;
    }

    void update(int pos, int value) {
        update(root, 0, MX, pos, value);
    }

    int query(Node* node, int curL, int curR, int L, int R){
        if (R < curL || curR < L || curL > curR)
            return 0;

        if (L <= curL && curR <= R)
            return node->val;

        int mid = (curL + curR) / 2;

        int res = 0;
        if (node->left) res += query(node->left, curL, mid, L, R);
        if (node->right) res += query(node->right, mid + 1, curR, L, R);
        return res;
    }

    int query(int L, int R) {
        return query(root, 0, MX, L, R);
    }
};

int N, Q;
SparseSegTree S;

int main() {
    cin >> N >> Q;

    for (int i = 1; i <= N; i++) {
        int x; cin >> x;
        S.update(i, x);
    }

    for (int i = 1; i <= Q; i++) {
        int op; cin >> op;

        if (op == 1) {
            int a, b; cin >> a >> b;
            S.update(a, b);
        } else {
            int a, b; cin >> a >> b;
            cout << S.query(a, b) << "\n";
        }
    }

    return 0;
}

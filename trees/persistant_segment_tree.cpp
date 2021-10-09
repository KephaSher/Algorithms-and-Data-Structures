// persistent segment tree, O(N logN) time and space
#include <bits/stdc++.h>
#define MX 100000
using namespace std;

struct Node {
    int val;
    Node *left, *right;
    
    Node() {}
    
    Node (Node *l, Node *r, int v) {
        left = l, right = r, val = v;
    }
};

struct PersSegTree{
    int size;
    vector<int> arr;
    vector<Node*> version;

    PersSegTree (vector<int> _arr) {
        // arr is 1 - based
        arr = _arr;
        size = arr.size() - 1;

        Node* root = new Node(NULL, NULL, 0);
        build(root, 1, size);

        version.push_back(root);
    }

    void build (Node* n, int L, int R) {
        if (L == R) {
            n->val = arr[L];
            return;
        }

        int mid = (L + R) / 2;
        n->left = new Node(NULL, NULL, 0);
        n->right = new Node(NULL, NULL, 0);
        build(n->left, L, mid);
        build(n->right, mid + 1, R);
        n->val = n->left->val + n->right->val;
    }

    void update(Node *prev, Node *cur, int L, int R, int pos, int value) {
        if (pos > R || pos < L || L > R) return;

        if (L == R) {
            cur->val = value;
            return;
        }

        int mid = (L + R) / 2;
        if (pos <= mid) {
            cur->right = prev->right;
            cur->left = new Node(NULL, NULL, 0);
            update(prev->left, cur->left, L, mid, pos, value);
        } else {
            cur->left = prev->left;
            cur->right = new Node(NULL, NULL, 0);
            update(prev->right, cur->right, mid + 1, R, pos, value);
        }

        cur->val = cur->left->val + cur->right->val;
    }

    int query(Node *n, int curL, int curR, int L, int R) {
        if (curL > R || curR < L || curL > curR) return 0;
        if (L <= curL && curR <= R) return n->val;

        int mid = (curL + curR) / 2;
        return query(n->left, curL, mid, L, R) + 
            query(n->right, mid + 1, curR, L, R);
    }

    int query(int ver, int L, int R) {
        return query(version[ver], 1, size, L, R);
    }

    void newVersion(int pos, int value) {
        version.push_back(new Node(NULL, NULL, 0));
        int x = version.size() - 1;
        update(version[x - 1], version[x], 1, size, pos, value);
    }
};

int main() {
    vector<int> A = {0, 1, 2, 3, 4, 5};

    PersSegTree S = PersSegTree(A);

    S.newVersion(4, 2);

    cout << S.query(1, 1, 4) << endl;
}

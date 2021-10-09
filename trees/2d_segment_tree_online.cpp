// Online 2 segment tree with N ≤ 10^9
// Extremely slow because of constant factors, but overall O(N log^2N), O(N logN) space.
#include <bits/stdc++.h>
#include <chrono>
#define MX 200000
using namespace std;
using namespace chrono;

struct TNode {
    int key, L, R; // key of the BBST, pos for a segment tree (L, R) is the range of the keys
    int pri; // heap property
    int sum, val; // value of segment tree, sum of subtree
    TNode *left, *right;

    TNode (int _key, int _val) {        
        key = L = R = _key, pri = rand();
        left = right = NULL;
        sum = val = _val;
    }
};

struct Treap {
    TNode* root;

    Treap () {
       root = new TNode(0, 0);
    }

    TNode* upd(TNode* t) {
        TNode* res = t;
        res->L = res->R = res->key;
        res->sum = res->val;

        if (res->left) {
            res->sum += res->left->sum;
            res->L = min(res->L, res->left->L);
            res->R = max(res->R, res->left->R);
        }
        if (res->right) {
            res->sum += res->right->sum;
            res->L = min(res->L, res->right->L);
            res->R = max(res->R, res->right->R);
        }
        return res;
    }

    pair<TNode*, TNode*> split(TNode *t, int v) {
        // return left and right treaps containing lower and higher values, respectively
        // Tnodes with value >= v will go to the right
        if (!t) return {t, t};

        if (t->key >= v) { // our current Tnode will be in the right treap
            auto p = split(t->left, v);
            t->left = p.second;
            t = upd(t);
            return {p.first, t};
        } else { // our current Tnode will be in the left treap
            auto p = split(t->right, v);
            t->right = p.first;
            t = upd(t);
            return {t, p.second};
        }
    }

    // all v's in r is larger than l
    TNode* merge(TNode* l, TNode* r) {
        if (!l) return r;
        if (!r) return l;

        if (l->pri > r->pri) { // maintain heap property, l will be topmost Tnode of treap
            l->right = merge(l->right, r);
            l = upd(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            r = upd(r);
            return r;
        }
    }

    TNode* insert(TNode* x, int key, int val) { // insert value v
        auto p = split(x, key);
        return root = merge(merge(p.first, new TNode(key, val)), p.second);
    } TNode* insert(int key, int val) { return insert(root, key, val); }

    TNode* erase(TNode* x, int v) { // delete those equal to v
        auto a = split(x, v);
        auto b = split(a.second, v + 1);
        return root = merge(a.first, b.second);
    } TNode* erase(int v) { return erase(root, v); }

    // no need to insert before update
    void update(int pos, int value) {
        erase(pos);
        insert(pos, value);
    }

    int query(TNode* x, int L, int R) {
        if (L > x->R || R < x->L) 
            return 0;

        if (L <= x->L && x->R <= R) 
            return x->sum;

        int res = 0;
        if (L <= x->key && x->key <= R) res += x->val;
        if (x->left) res += query(x->left, L, R);
        if (x->right) res += query(x->right, L, R);
        return res;
    } int query(int L, int R) { return query(root, L, R); }
};

struct SNode {
    SNode *left, *right;
    Treap tr;

    SNode() {}

    SNode (SNode *l, SNode *r, Treap _tr) {
        left = l, right = r, tr = _tr;
    }
};

struct SparseSegTree {
    SNode* root;

    SparseSegTree() {
        root = new SNode(NULL, NULL, Treap());
    }

    void update(SNode* node, int L, int R, int x, int y, int v) {
        if (L == x && R == x) {
            node->tr.update(y, v);
            return;
        }

        int mid = (L + R) / 2;
        if (x <= mid) {
            if (!node->left) node->left = new SNode(NULL, NULL, Treap());
            update(node->left, L, mid, x, y, v);
        } else {
            if (!node->right) node->right = new SNode(NULL, NULL, Treap());
            update(node->right, mid + 1, R, x, y, v);
        }

        int res = 0;
        if (node->left) res += node->left->tr.query(y, y);
        if (node->right) res += node->right->tr.query(y, y);
        node->tr.update(y, res);
    }

    void update(int x, int y, int value) {
        update(root, 1, MX, x, y, value);
    }

    int query(SNode* node, int curL, int curR, int x1, int y1, int x2, int y2){
        if (x2 < curL || curR < x1 || curL > curR)
            return 0;

        if (x1 <= curL && curR <= x2)
            return node->tr.query(y1, y2);

        int mid = (curL + curR) / 2;

        int res = 0;
        if (node->left) res += query(node->left, curL, mid, x1, y1, x2, y2);
        if (node->right) res += query(node->right, mid + 1, curR, x1, y1, x2, y2);
        return res;
    }

    int query(int x1, int y1, int x2, int y2) {
        return query(root, 1, MX, x1, y1, x2, y2);
    }
};

int N, Q;
bool A[MX + 1][MX + 1];

int main() {
    auto start = high_resolution_clock::now();
    cin.tie(0)->sync_with_stdio(false);
    SparseSegTree st = SparseSegTree();
    
    cin >> N >> Q;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            char t; cin >> t;
            if (t == '*') A[i][j] = 1;
            else A[i][j] = 0;
            st.update(i, j, A[i][j]);
        }
    }

    for (int i = 1; i <= Q; i++) {
        int op; cin >> op;
        if (op == 1) {
            int a, b; cin >> a >> b;
            A[a][b] = !A[a][b];
            st.update(a, b, A[a][b]);
        } else {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            cout << st.query(x1, y1, x2, y2) << "\n";
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cerr << duration.count() << endl;
    return 0;
}

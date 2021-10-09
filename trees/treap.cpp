// Treap Implementation, BBST O(N logN) time, O(N) memory
// Because of constant factors, this is about 2x slower than normal SegTree
#include <bits/stdc++.h>
#define MX 100000
using namespace std;

struct Node {
    int key, L, R; // key of the BBST, pos for a segment tree (L, R) is the range of the keys
    int pri; // heap property
    int sum, val; // value of segment tree, sum of subtree
    Node *left, *right;

    Node (int _key, int _val) {        
        key = L = R = _key, pri = rand();
        left = right = NULL;
        sum = val = _val;
    }
};

struct Treap {
    Node* root;

    Treap () {
       root = new Node(0, 0);
    }

    Node* upd(Node* t) {
        Node* res = t;
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

    // return left and right treaps containing lower and higher values, respectively
    pair<Node*, Node*> split(Node *t, int v) {
        // nodes with value >= v will go to the right
        if (!t) return {t, t};

        if (t->key >= v) { // our current node will be in the right treap
            auto p = split(t->left, v);
            t->left = p.second;
            t = upd(t);
            return {p.first, t};
        } else { // our current node will be in the left treap
            auto p = split(t->right, v);
            t->right = p.first;
            t = upd(t);
            return {t, p.second};
        }
    }

    // all v's in r is larger than l
    Node* merge(Node* l, Node* r) {
        if (!l) return r;
        if (!r) return l;

        if (l->pri > r->pri) { // maintain heap property, l will be topmost node of treap
            l->right = merge(l->right, r);
            l = upd(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            r = upd(r);
            return r;
        }
    }

    Node* insert(Node* x, int key, int val) { // insert value v
        auto p = split(x, key);
        return root = merge(merge(p.first, new Node(key, val)), p.second);
    } Node* insert(int key, int val) { return insert(root, key, val); }

    Node* erase(Node* x, int v) { // delete those equal to v
        auto a = split(x, v);
        auto b = split(a.second, v + 1);
        return root = merge(a.first, b.second);
    } Node* erase(int v) { return erase(root, v); }

    Node* find(Node* x, int v) {
        if (!x) return NULL;
        if (x->key < v) return find(x->right, v);
        else if (x->key > v) return find(x->left, v);
        return x;
    }
    
    bool find(int v) {
        return find(root, v) != NULL;
    }
    
    // no need to insert before update
    void update(int pos, int value) {
        erase(pos);
        insert(pos, value);
    }

    int query(Node* x, int L, int R) {
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

void printTreap(Node* node) {
    if (node == NULL) return;
    cout << node->key << endl;
    printTreap(node->left);
    printTreap(node->right);
}

Treap tr;

int N, Q;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    cin >> N >> Q;

    for (int i = 1; i <= N; i++) {
        int x; cin >> x;
        tr.update(i, x);
    }

    for (int i = 1; i <= Q; i++) {
        int op; cin >> op;
        if (op == 1) {
            int k, u; cin >> k >> u;
            tr.update(k, u);
        } else {
            int a, b; cin >> a >> b;
            cout << tr.query(a, b) << "\n";
        }
    }

    return 0;
}

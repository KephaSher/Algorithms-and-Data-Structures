// template for segment tree (point update range sum) (without recursion)
#include <bits/stdc++.h>
using namespace std;

// int (*func) (int, int); // sum and addition could be used by func()
// void operation(int (*_func) (int, int)) {
//     func = _func;
// }

struct SegTree{
    const int VALUE = 0;
    int size, n;
    vector<int> sums; // sums is [0...2*size-1]

    void init(vector<int> &A) { // A is 0-based
        size = 1, n = A.size();
        while (size < n) size *= 2;
        sums.assign(2 * size, VALUE);

        for (int i = size; i < size + n; i++)
            sums[i] = A[i - size];

        for (int i = size - 1; i >= 1; i--)
            sums[i] = sums[i * 2] + sums[i * 2 + 1];
    }

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        sums.assign(2 * size, VALUE);
    }

    // gets sum in the range [a,b]
    int query(int a, int b) {
        if (a > b) swap(a, b);
        a += size - 1, b += size - 1;
        int ans = VALUE;
        while (a <= b) {
            if (a % 2 == 1) ans += sums[a++];
            if (b % 2 == 0) ans += sums[b--];
            a /= 2, b /= 2;
        }
        return ans;
    }

    // assumes pos is 1 - based
    void update(int pos, int value) {
        pos += size - 1;
        sums[pos] = value;
        for (pos /= 2; pos >= 1; pos /= 2)
            sums[pos] = sums[pos * 2] + sums[pos * 2 + 1];
    }
};

int N, Q;
SegTree S;

int main(){
    // freopen ("tmp", "r", stdin);
    cin >> N >> Q;

    vector<int> A(N);
    // input is one - based

    for (int i = 0; i < N; i++) cin >> A[i];
    S.init(A);

    for (int i = 1; i <= Q; i++){
        int op, a, b; cin >> op >> a >> b;
        if (op == 1) S.update(a, b);
        else cout << S.query(a, b) << endl;
    }

    // for (int i : S.sums) cout << i << " "; cout << endl;
    return 0;
}

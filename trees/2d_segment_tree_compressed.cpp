#include <bits/stdc++.h>
#define MX 100000
using namespace std;

struct SegTree2D {
    int Size;
    vector<int> actual_size, size, st, st2, lst, segtree, yrank;
    // st2 uses size, st uses actual_size

    SegTree2D (int n, vector<pair<int, int>> todo) {
        // first x in todo must be 1

        Size = up(n);
        lst.assign(2 * Size, -999);
        actual_size.assign(2 * Size, 0);
        size.assign(2 * Size, 0);
        st.assign(2 * Size, 0);
        st2.assign(2 * Size, 0);

        sort(todo.begin(), todo.end(), [](const pair<int, int> &a, const pair<int, int> &b){
            return a.second < b.second; });

        for (auto t : todo)
            for (int x = t.first + Size - 1; x >= 1; x /= 2)
                if (lst[x] != t.second)
                    lst[x] = t.second, size[x]++;
        
        for (int i = 1; i < 2 * Size; i++)
            actual_size[i] = 2 * up(size[i]) - 1;

        for (int i = 2; i < 2 * Size; i++)
            st[i] = st[i - 1] + actual_size[i - 1];
        
        int sum1 = st[2 * Size - 1] + actual_size[2 * Size - 1];

        for (int i = 1; i < 2 * Size; i++)
            st2[i] = st2[i - 1] + size[i];

        int sum2 = st2[2 * Size - 1];

        fill(lst.begin(), lst.end(), -999);
        
        yrank.resize(sum2); segtree.resize(sum1);
        reverse(todo.begin(), todo.end());
        
        for (auto t : todo)
            for (int x = t.first + Size - 1; x >= 1; x /= 2)
                if (lst[x] != t.second)
                    lst[x] = t.second, yrank[--st2[x]] = t.second;

        cout << "st[]:  ";
        for (int i = 1; i < 2 * Size; i++)
            cout << st[i] << " "; cout << endl;
        
        cout << "st2[]:  ";
        for (int i = 1; i < 2 * Size; i++)
            cout << st2[i] << " "; cout << endl;
    }

    void dbg(vector<int> A, string name) {
        cout << name << ":  ";
        for (int i : A) cout << i << " ";
        cout << endl;
    }

    int up(int x) {
        int ret = 1;
        while (ret < x) ret *= 2;
        return ret;
    }
    
    int Yrank(int y, int l, int r) {
        // no -1 because turns 0 based to 1 based
        return (int)(upper_bound(begin(yrank) + l, begin(yrank) + r, y) - begin(yrank) - l);
    }

    int Yrank2(int y, int l, int r) {
        int ret = (int)(upper_bound(begin(yrank) + l, begin(yrank) + r, y) - begin(yrank) - l);

        if (find(begin(yrank) + l, begin(yrank) + r, y) != begin(yrank) + r) 
            return ret;
        return ret + 1;
    }

    // query a single segtree
    int query(int seg, int y1, int y2) {
        int sz = actual_size[seg] / 2;
        // if y1, y2 is between y's then round up y1, round down y2

        y1 = Yrank2(y1, st2[seg], st2[seg] + size[seg]) + sz;
        y2 = Yrank(y2, st2[seg], st2[seg] + size[seg]) + sz;

        // if y1 is lower than all y's in segtree seg. if y is larger than all y's, its fine
        if (y1 == 0) y1++;

        int ret = 0;
        while (y1 <= y2) {
            if (y1 % 2 == 1) ret += segtree[st[seg] + y1 - 1], y1++;
            if (y2 % 2 == 0) ret += segtree[st[seg] + y2 - 1], y2--;
            y1 /= 2, y2 /= 2;
        }

        return ret;
    }

    // query 2D
    int query(int x1, int y1, int x2, int y2) {
        x1 += Size - 1, x2 += Size - 1;

        int ret = 0;
        while (x1 <= x2) {
            if (x1 % 2 == 1) {
                if (size[x1]) ret += query(x1, y1, y2);
                x1++;
            }
            if (x2 % 2 == 0) {
                if (size[x1]) ret += query(x2, y1, y2);
                x2--;
            }
            x1 /= 2, x2 /= 2;
        }

        return ret;
    }

    // 2D increment
    void update(int x, int y, int v) {
        x += Size - 1;
        for (; x >= 1; x /= 2) {
            int sz = actual_size[x] / 2;
            int yy = Yrank(y, st2[x], st2[x] + size[x]) + sz;

            // sums[x][y] = sums[x * 2][y1] + sums[x * 2 + 1][y2] can't get y1, y2 easily
            for (; yy >= 1; yy /= 2)
                segtree[st[x] + yy - 1] += v;
        }
    }
};

int main() {
    vector<pair<int, int>> todo = {{1, 3}, {2, 1}, {3, 2}, {4, 3}};

    SegTree2D seg = SegTree2D(4, todo);

    seg.update(1, 3, 3);
    seg.update(2, 1, 5);
    seg.update(3, 2, 2);
    seg.update(4, 3, 1);

    seg.dbg(seg.segtree, "segtree");

    return 0;
}

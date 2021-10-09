#include <bits/stdc++.h>
using namespace std;

struct BIT2D {
    int size;
    vector<int> cnt, st, lst;
    vector<int> yrank, BIT;

    BIT2D (int n, vector<pair<int, int>> todo) {
        size = n;
        // initially, lst[i] should be an impossbiel value, so if coordinates >= 0, 0 won't work
        lst.assign(size + 1, -999);
        st.assign(size + 1, 0);
        cnt.assign(size + 1, 0);

        sort(todo.begin(), todo.end(), [](const pair<int, int> &a, const pair<int, int> &b){
            return a.second < b.second; });
        
        for (auto t : todo)
            for (int x = t.first; x <= size; x += x & -x)
                if (lst[x] != t.second) 
                    lst[x] = t.second, cnt[x]++;
        
        for (int i = 1; i <= size; i++)
            st[i] = st[i - 1] + cnt[i];

        int sum = st[size];

        fill(lst.begin(), lst.end(), -999);
        
        yrank.resize(sum); BIT.resize(sum);
        reverse(todo.begin(), todo.end());
        
        for (auto t : todo)
            for (int x = t.first; x <= size; x += x&-x)
                if (lst[x] != t.second)
                    lst[x] = t.second, yrank[--st[x]] = t.second;
                    
        // yrank is 0 based, bit is 0 based
        // Instead of storing BITs in an 2D array, the 1D BIT we want is (st[x], st[x] + cnt[x])
    }

    // l, r just means the BIT
    int Yrank(int y, int l, int r) {
        // no -1 because turns 0 based to 1 based
        return (int)(upper_bound(begin(yrank) + l, begin(yrank) + r, y) - begin(yrank) - l);
    }

    void add(int x, int y, int v) {
        for (; x <= size; x += x & -x) {
            int yy = Yrank(y, st[x], st[x] + cnt[x]);
            // <= cnt[x] not < cnt[x] because yy is 1 based
            for (; yy <= cnt[x]; yy += yy & -yy) 
                // -1 because BIT is 0 based, st[x] is 0 based, yy is 1 based
                BIT[st[x] + yy - 1] += v;
        }
    }

    int sum(int x, int y) {
        int res = 0;
        for (; x >= 1; x -= x & -x) {
            int yy = Yrank(y, st[x], st[x] + cnt[x]);
            // if yy = 0, then the for loop would not run (it is possible that yy = 0)
            for (; yy >= 1; yy -= yy & -yy)
                res += BIT[st[x] + yy - 1];
        }
        return res;
    }
};

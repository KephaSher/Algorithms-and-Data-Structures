// Convex Hull using monotone chain or Andrew's algorithm, O(N logN)
#include <bits/stdc++.h>
using namespace std;

struct pt {
    int x, y;
    pt() {}
    pt(int _x, int _y) {
        x = _x, y = _y;
    }
    bool operator==(const pt& other) const {
        return x == other.x && y == other.y;
    }
};

bool cmp(pt a, pt b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull(vector<pt>& a) {
    sort(a.begin(), a.end(), &cmp);
    a.resize(unique(a.begin(), a.end()) - a.begin());

    if (a.size() == 1) return;

    pt p1 = a.front(), p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);

    for (int i = 1; i < (int)a.size(); i++) {
        // cw(p1, a[i], p2) means that a[i] is above the line (p1, p2)
        if (i == a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up.back(), a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down.back(), a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);

    // skip the last element and the first element
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}

int N;

int main() {
    cin.tie(0)->sync_with_stdio(false);

        cin >> N;

        vector<pt> pts(N);
        for (int i = 0; i < N; i++)
            cin >> pts[i].x >> pts[i].y;

        convex_hull(pts);

        cout << pts.size() << endl;
        for (auto& i : pts)
            cout << i.x << " " << i.y << endl;
    return 0;
}

// Template for Graham Scan, O(NlogN)
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define MX 100000
#define ll long long
#define pll pair<ll, ll>
#define f first
#define s second
using namespace std;

int N;

ll dist(const pll& p) {
    return p.f * p.f + p.s * p.s;
} // x^2 + y^2

// basic operations
pll operator-(const pll& l, const pll& r) {
	return pll(l.f - r.f, l.s - r.s);
}

ll cross(const pll& a, const pll& b) {
    return a.f * b.s - a.s * b.f;
} // cross product

ll cross(const pll& p, const pll& a, const pll& b) { // cross product
	return cross(a - p, b - p);
}

vector<int> hullInd(const vector<pll>& v) {
    // ind is the new origin
    int ind = -1; pll pts = {INF, INF};

    for (int i = 0; i < v.size(); i++)
        if (v[i] < pts)
            pts = v[i], ind = i;

	vector<int> cand, hull;
    hull.push_back(ind);

    for (int i = 0; i < v.size(); i++)
        if (v[i] != v[ind])
            cand.push_back(i);

	sort(cand.begin(), cand.end(),[&](int a, int b) {
		pll x = v[a] - v[ind], y = v[b] - v[ind];
		ll t = cross(x, y);

        // if x is below y, x comes first. If x and y are colinear, sort by distance.
		return t != 0 ? t > 0 : dist(x) < dist(y);
	});

    // after sorting, the last few points are the points that have the same x as v[ind]

	for (auto& c : cand) { // for every point
		while (hull.size() > 1 && cross(v[hull[hull.size() - 2]], v[hull.back()], v[c]) <= 0)
			hull.pop_back(); // pop until counterclockwise or size <= 1
		hull.push_back(c);
	}

	return hull;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

    cin >> N;
    vector<pll> pts(N);

    for (int i = 0; i < N; i++) {
        ll a, b;
        cin >> a >> b;
        pts[i] = pll(a, b);
    }

    vector<int> ret = hullInd(pts); // gets hull indices of convex hull

    cout << ret.size() << '\n';
    for (auto& a : ret)
        cout << pts[a].first << " " << pts[a].second << '\n';
}

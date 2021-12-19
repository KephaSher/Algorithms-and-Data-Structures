/* 
Template code for kruskal's MST algorithm

The idea of kruskal's MST algorithm is very simple -- we sort the edges and add them 
into the working tree one by one until the tree is completed.
We use DSU to maintain the components.

Time complexity is O(ElogE) due to the sorting.
*/
#include <bits/stdc++.h>
#define MX 100000
#define f first
#define s second
using namespace std;

int N, M;
pair<int, pair<int, int>> edges[MX + 5];
int parent[MX + 5];

int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

int kruskal() {
    int cnt = 0, comp = N;
    for (int i = 1; i <= M; i++) {
        int x = find(edges[i].s.f);
        int y = find(edges[i].s.s);
        if (parent[x] == parent[y])
            continue;

        cnt += edges[i].f;
        parent[x] = y;
        comp--;
    }

    // a MST of size N has N - 1 edges
    return comp == 1 ? cnt : -1;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        parent[i] = i;

    for (int i = 1; i <= M; i++)
        cin >> edges[i].s.f >> edges[i].s.s >> edges[i].f;

    sort(edges + 1, edges + 1 + M);

    int ans = kruskal();

    if (ans != -1)
        cout << ans << "\n";
    else
        cout << "IMPOSSIBLE\n";
    return 0;
}

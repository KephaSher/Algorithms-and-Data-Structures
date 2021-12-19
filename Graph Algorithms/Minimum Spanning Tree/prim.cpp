/* 
Template for prim's MST algorithm

This algorithm behaves extremely similar to dijkstra's shortest path algorithm.
dist[], pq, prev_node[] are all there
The difference being that dist[i] now stores the minimum cost needed to connect node i
to the working tree. 
We start with node 1 as the working tree with dist[1] = 0.

Time complexity is O(E logV)

Like dijkstra's algorithm, this could also be turned into O(V^2) for dense graphs.
*/

#include <bits/stdc++.h>
#define MX 1000
#define INF 0x3f3f3f3f
#define pii pair<int, int>
using namespace std;

int N, M;
vector<pii> edges[MX + 5];
priority_queue<pii, vector<pii>, greater<pii>> q;
bool visited[MX + 5];
int dist[MX + 5], prev_node[MX + 5];

int prim() {
    int cnt = 0;
    fill(dist + 1, dist + 1 + N, INF);
    dist[1] = 0;
    q.push({0, 1});

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (auto &e : edges[u]) {
            int v = e.first, w = e.second;
            if (!visited[v] && dist[v] > w) {
                dist[v] = w;
                q.push({dist[v], v});
                prev_node[v] = u;
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        if (dist[i] >= INF) return -1;
        cnt += dist[i];
    }

    return cnt;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[a].push_back(make_pair(b, c));
        edges[b].push_back(make_pair(a, c));
    }

    int ans = prim();

    if (ans != -1)
        cout << ans << "\n";
    else
        cout << "IMPOSSIBLE\n";
    
    return 0;
}

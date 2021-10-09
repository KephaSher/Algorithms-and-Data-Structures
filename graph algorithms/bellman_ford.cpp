// template for the bellman ford shortest path algorithm
/*
Used to find negative cycles
Time complexity: O(NM)
*/

#include <bits/stdc++.h>
#define MXN 300
#define MXM 300
#define INF 1000000000
using namespace std;

struct edge {
    int u, v, w;
};

int N, M; // N vertices, M edges
edge edges[MXM + 1];
int dist[MXN + 1];

int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    fill(dist + 1, dist + 1 + N, INF);
    dist[1] = 0;

    for (int i = 1; i <= N - 1; i++) {
        for (int j = 1; j <= M; j++) {
            int u = edges[j].u, v = edges[j].v, w = edges[j].w;
            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (int i = 1; i <= M; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cout << "contains negative edge\n";
            return 0;
        }
    }

    cout << "shortest path is from 1 to N is: " << dist[N] << "\n";
    return 0;
}

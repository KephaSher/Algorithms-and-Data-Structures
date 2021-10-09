// template for prim's MST.  TC: O((V + E)logV)
#include <bits/stdc++.h>
#define MAXN 100000
#define INF 2000000000
#define pii pair<int, int>
using namespace std;

int N, M;
vector<pii> edges[MAXN + 2];
priority_queue<pii, vector<pii>, greater<pii>> q;
bool visited[MAXN + 2];
int dist[MAXN + 2], parent[MAXN + 2];

int prim()
{
    int cnt = 0;
    fill(dist + 1, dist + 1 + N, INF);
    dist[1] = 0;
    q.push({0, 1});

    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();

        if (visited[u])
            continue;
        visited[u] = true;

        for (auto &e : edges[u])
        {
            int v = e.first, w = e.second;
            if (!visited[v] && dist[v] > w)
            {
                dist[v] = w;
                q.push({dist[v], v});
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i <= N; i++)
    {
        if (dist[i] >= INF)
            return -1;
        cnt += dist[i];
    }
    return cnt;
}

int main()
{
    cin >> N >> M;
    for (int i = 1; i <= M; i++)
    {
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
}

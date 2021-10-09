// Template for spfa in O(N), worst case O(NM)
#include <bits/stdc++.h>
#define MAXN 1000
#define INF 100000
using namespace std;

struct edge
{
    int nextnode, weight;
};

int N, M; // N vertices, M edges
vector<edge> edges[MAXN + 2];
int dist[MAXN + 2], visitcount[MAXN + 2];
bool inq[MAXN + 2];

void spfa(int node)
{
    memset(inq, 0, sizeof(inq));
    fill(dist + 1, dist + 1 + N, INF);
    queue<int> q;
    dist[1] = 0;
    inq[1] = true;
    q.push(1);

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        inq[cur] = false;

        /* for finding negative cycles.
        visitcount[cur]++;

        if (visitcount[cur] >= N) {
            cout << "negative cycle\n";
            return 0;
        }
        */

        for (int i = 0; i < edges[cur].size(); i++)
        {
            int n = edges[cur][i].nextnode;
            int w = edges[cur][i].weight;
            if (dist[n] > dist[cur] + w)
            {
                dist[n] = dist[cur] + w;
                if (!inq[n])
                {
                    inq[n] = true;
                    q.push(n);
                }
            }
        }
    }
}

int main()
{
    ifstream cin("tmp");
    cin >> N >> M;
    for (int i = 1; i <= M; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edge tmp;
        tmp.nextnode = b;
        tmp.weight = c;
        edges[a].push_back(tmp);
        tmp.nextnode = a;
        edges[b].push_back(tmp);
    }
    // shortest path from 1 to N
    spfa(1);
    cout << dist[N] << endl;
    return 0;
}

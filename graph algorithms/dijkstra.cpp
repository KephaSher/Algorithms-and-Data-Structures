// template for Dijkstra
#include <bits/stdc++.h>
#define MAXN 100000
#define INF 2000000000
using namespace std;

// O(V+ElogV)
struct edge
{
    int next, weight;
};

int N, M;
vector<edge> adj[MAXN + 2];
int dist[MAXN + 2];
bool visited[MAXN + 2];
priority_queue<pair<int, int>> q;
int prevn[MAXN + 2];

int main()
{
    cin >> N >> M;
    for (int i = 1; i <= M; i++)
    {
        int a, b, c; // value of a between vertices b and c
        cin >> a >> b >> c;
        edge tmp = {.next = b, .weight = c};
        adj[a].push_back(tmp);
        tmp.next = a;
        adj[b].push_back(tmp);
    }
    fill(dist + 1, dist + N + 1, INF);
    dist[1] = 0;
    q.push(make_pair(0, 1));

    while (!q.empty())
    {
        int node = q.top().second;
        q.pop();
        
        if (visited[node])
            continue;
        visited[node] = true;

        for (auto &e : adj[node])
        {
            if (dist[node] + e.weight < dist[e.next])
            {
                dist[e.next] = dist[node] + e.weight;
                prevn[e.next] = node;
                q.push(make_pair(-dist[e.next], e.next));
            }
        }
    }

    // finding the path
    stack<int> output;
    int cur = N;
    while (cur != 0)
    {
        output.push(cur);
        cur = prevn[cur];
    }
    // printing the path
    while (!output.empty())
    {
        cout << output.top() << (output.size() == 1 ? '\n' : ' ');
        output.pop();
    }
    // shortest distance from 1 to N
    cout << dist[N] << endl;
    return 0;
}

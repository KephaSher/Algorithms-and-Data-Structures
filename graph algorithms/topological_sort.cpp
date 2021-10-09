#include <bits/stdc++.h>
#define MAXN 100000
using namespace std;

int N, M;
int incoming[MAXN + 2];
vector<int> edges[MAXN + 2], output;
bool visited[MAXN + 2];
queue<int> q;

void dfs(int node)
{
    for (int edge : edges[node])
    {
        if (!visited[edge])
        {
            visited[edge] = true;
            dfs(edge);
        }
    }
    output.push_back(node);
}

bool computedfs()
{
    for (int i = 1; i <= N; i++)
    {
        if (!visited[i])
        {
            visited[i] = true;
            dfs(i);
        }
    }

    reverse(output.begin(), output.end());

    // check if sort is valid
    vector<int> ind(N + 1);
    for (int i = 0; i < N; i++)
        ind[output[i]] = i + 1;

    for (int i = 1; i <= N; i++)
        for (int j : edges[i])
            if (ind[j] <= ind[i])
                return false;
    return true;
}

bool computebfs()
{
    for (int i = 1; i <= N; i++)
        if (incoming[i] == 0)
            q.push(i);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        output.push_back(node);

        for (int edge : edges[node])
        {
            incoming[edge]--;
            if (incoming[edge] == 0)
                q.push(edge);
        }
    }
    // check is sort is valid
    if ((int)output.size() < N)
        return false;
    return true;
}

int main()
{
    cin >> N >> M;
    for (int i = 1; i <= M; i++)
    {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        incoming[b]++;
    }

    if (computedfs())
    {
        for (int i : output)
            cout << i << " ";
        cout << "\n";
    }
    else
        cout << "IMPOSSIBLE\n";

    return 0;
}

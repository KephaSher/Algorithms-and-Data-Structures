// template for floyd-warshall shortest path
#include <bits/stdc++.h>
#define INF 1000000000
#define MX 100
using namespace std;

int n, m;              // vertices, edges
int connect[MX + 5][MX + 5]; // conectivity matrix

int main()
{
    memset(connect, 0x3f, sizeof(connect));

    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        connect[a][b] = min(connect[a][b], c);
        connect[b][a] = min(connect[b][a], c);
    }

    // main algorithm (order is KIJ)
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                connect[i][j] = min(connect[i][j], connect[i][k] + connect[k][j]);

    cout << connect[1][n] << endl;
}

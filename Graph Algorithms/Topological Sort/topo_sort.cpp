#include <bits/stdc++.h>
#define MX 100000
using namespace std;

int N, M;
int incoming[MX + 2];
vector<int> edges[MX + 2], output;
bool visited[MX + 2];
queue<int> q;

int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        incoming[b]++;
    }
  
    for (int i = 1; i <= N; i++)
          if (incoming[i] == 0)
              q.push(i);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        output.push_back(node);

        for (int edge : edges[node]) {
            incoming[edge]--;
            if (incoming[edge] == 0)
                q.push(edge);
        }
    }
    
    for (int i : output) 
        cout << i << " ";
    cout << "\n";
}

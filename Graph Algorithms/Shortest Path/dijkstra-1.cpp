/**
 * Template code for Dijkstra's shortest path algorithm
 * 
 *   dist[i]: shortest distance from source to i
 *   
 * 1. Start with the source node
 * 2. Go through the adjacency list to find connected nodes
 * 3. If the distance from the current node to the next node is better, update
 * 
 * Time complexity: O(V logE)
 *   Where:
 *   V is the number of nodes, 
 *   E is the number of edges
 *
 * Verification: https://cses.fi/problemset/result/3255742/
 * 
 * Notes: 
 * 1. The code is written for indirected graphs, change the adj list to make it work for directed ones
 * 2. The verification roblem needs long long and is a directerd graph
*/
#include <bits/stdc++.h>
#define int long long
#define MX 200000
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;

// struct for the edges of the graph
struct Edge {
    int next, weight;
    Edge (int _n, int _w) {
        next = _n, weight = _w;
    }
};

int N, M;

// adjacency list for the graph
vector<Edge> adj[MX + 5];

// ordered by (-distance, node) so that the one with the shortest 
// distance gets popped first
priority_queue<pair<int, int>> pq; 

// our answer, dist[i] denotes the shortest distance from node 1 to i
int dist[MX + 5];

// visited array
bool visited[MX + 5];

// Stores the actual path, prev_node[i] denotes the last node visited in order 
// to get the shortest path to node i
int prev_node[MX + 5];

signed main() {
    cin >> N >> M;

    for (int i = 1; i <= M; i++) {
        int a, b, c; // edge from a to b with weight c
        cin >> a >> b >> c;
        // update the adjacency list
        adj[a].push_back(Edge(b, c));
        adj[b].push_back(Edge(a, c)); // remove this for directed graphs
    }

    // fill distance to infinity
    fill(dist + 1, dist + N + 1, INF);
    // set distance to node 1 to be 0
    dist[1] = 0;

    pq.push(make_pair(0, 1));

    while (!pq.empty()) {
        // pop our current node to process
        // note that once the node is popped from the queue, the answer for that node is set
        int node = pq.top().second;
        pq.pop();
        
        // update visited array
        if (visited[node]) continue;
        visited[node] = true;

        // go through the connected edges
        for (auto &edge : adj[node]) {
            if (dist[node] + edge.weight < dist[edge.next]) {
                // update the distance of the new node
                // we can be sure that the distance for the next node is minimum
                dist[edge.next] = dist[node] + edge.weight;

                // update the node used
                prev_node[edge.next] = node;

                pq.push(make_pair(-dist[edge.next], edge.next));
            }
        }
    }

    // finding the shortest path
    stack<int> output;
    int cur = N;
    while (cur != 0) {
        output.push(cur);
        cur = prev_node[cur];
    }

    for (int i = 1; i <= N; i++)
        cout << dist[i] << " ";
    cout << "\n";
    return 0;
}

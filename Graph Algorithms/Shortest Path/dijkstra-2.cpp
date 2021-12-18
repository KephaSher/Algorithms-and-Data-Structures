/**
 * Template code for Dijkstra's shortest path algorithm
 * 
 *   dist[i]: shortest distance from source to i
 *   
 * 1. Start with the source node
 * 2. Go through the all nodes that are visited to find the one with the 
 *    smallest distance by looping through all other nodes.
 * 3. Go through the adjcency matrix of the minimum node, update the distance of other nodes
 *    if the new distance is shorter 
 * 
 * Time complexity: O(V^2)
 *   Where:
 *   V is the number of nodes,
 * 
 * Verification: 
 * 
 * Notes: 
 * 1. The code is written for indirected graphs, change the adj matrix to make it work for directed ones
*/
#include <bits/stdc++.h>
#define MX 100
#define INF 0x3f3f3f3f
using namespace std;

int N, M;
int adj[MX + 5][MX + 5];
int dist[MX + 5];
bool visited[MX + 5];

int main() {
    cin >> N >> M;

    // fill adj[i][j] with -1, denoting that nodes i and j isn't connceted
    for (int i = 1; i <= N; i++)
        fill(adj[i] + 1, adj[i] + 1 + N, -1);

    for (int i = 1; i <= M; i++) {
        int a, b, c; // edge from a to b with weight c
        cin >> a >> b >> c;
        adj[a][b] = c;
        adj[b][a] = c; // remove this for directed graphs
    }

    fill(dist + 1, dist + N + 1, INF); // init distance to source node as infinity
    dist[1] = 0;              // set the dis from source node to itself to 0

    for (int i = 1; i <= N; i++) {
        int min_idx = 0, min_dist = INF;

        for (int j = 1; j <= N; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                // find the unvisited nodes
                // that have the smallest distance to the source node
                min_dist = dist[j];
                min_idx = j;
            }
        }

        visited[min_idx] = true; // mark the found node as visited

        for (int j = 1; j <= N; j++) {
            if (adj[min_idx][j] != -1 && adj[min_idx][j] + dist[min_idx] < dist[j]) {
                // that is connected to node mini, if the distance can be shorted by going through
                // node i, change dis[j].
                dist[j] = adj[min_idx][j] + dist[min_idx];
            }
        }
    }
    
    for (int i = 1; i <= N; i++)
        cout << dist[i] << " ";
    cout << "\n";

    return 0;
}

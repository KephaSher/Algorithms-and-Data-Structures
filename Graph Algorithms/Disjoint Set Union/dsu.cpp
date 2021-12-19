/*
Template code for union find algorithm.

parent[i] denotes the parent of node i.
find(x) returns the node that represents the component node x is in.
merge(x, y) merges the 2 components that x, y is in. Returns false if they are in the same component.
*/
#include <bits/stdc++.h>
#define MX 100000
using namespace std;

int N, M;
int parent[MX + 5];

int find(int x) {
    if (x == parent[x]) return x;
    return parent[x] = find(parent[x]);
}

bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    parent[x] = y;
    return true;
}

int main() {
    cin >> N >> M;

    for (int i = 1; i <= N; i++)
        parent[i] = i;

}

#include <bits/stdc++.h>
using namespace std;

void bfs(int start, vector<int> adj[], vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> adj[n + 1]; 

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int start;
    cout << "Enter starting node ";
    cin >> start;

    vector<bool> visited(n + 1, false);
    bfs(start, adj, visited);

    return 0;
}

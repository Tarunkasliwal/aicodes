#include <iostream>
#include <vector>
using namespace std;

// Function to check if it's safe to color vertex v with color c
bool isSafe(int v, vector<vector<int>>& graph, vector<int>& color, int c, int V) {
    for (int i = 0; i < V; ++i) {
        if (graph[v][i] && color[i] == c)
            return false;
    }
    return true;
}

// Backtracking function to solve graph coloring
bool graphColoringUtil(vector<vector<int>>& graph, int m, vector<int>& color, int v, int V) {
    if (v == V)
        return true;

    for (int c = 1; c <= m; ++c) {
        if (isSafe(v, graph, color, c, V)) {
            color[v] = c;

            if (graphColoringUtil(graph, m, color, v + 1, V))
                return true;

            color[v] = 0; // backtrack
        }
    }

    return false;
}

// Function to print the result
void printSolution(vector<int>& color, int V) {
    cout << "Solution Found:\n";
    for (int i = 0; i < V; ++i)
        cout << "Vertex " << i << " ---> Color " << color[i] << endl;
}

// Main function
int main() {
    int V, m;
    cout << "Enter the number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));
    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            cin >> graph[i][j];

    cout << "Enter the number of colors: ";
    cin >> m;

    vector<int> color(V, 0);

    if (!graphColoringUtil(graph, m, color, 0, V))
        cout << "No solution exists with " << m << " colors.\n";
    else
        printSolution(color, V);

    return 0;
}
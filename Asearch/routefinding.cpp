#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <climits> 

using namespace std;

struct Node {
    int x, y;
    int gCost = INT_MAX;
    int hCost = 0;
    int fCost = 0;
    Node* parent = nullptr;

    Node(int x, int y) : x(x), y(y) {}

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }

    bool operator>(const Node& other) const {
        return fCost > other.fCost;
    }
};

// Hash function for Node pointer for unordered_set
struct NodeHasher {
    size_t operator()(const Node* node) const {
        return hash<int>()(node->x * 31 + node->y);
    }
};

// Comparison for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->fCost > b->fCost;
    }
};

const int ROWS = 5;
const int COLS = 5;

int grid[ROWS][COLS] = {
    { 0, 1, 0, 0, 0 },
    { 0, 1, 0, 1, 0 },
    { 0, 0, 0, 1, 0 },
    { 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }
};

vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < ROWS && y < COLS;
}

int heuristic(Node* a, Node* b) {
    return abs(a->x - b->x) + abs(a->y - b->y);
}

vector<Node*> reconstructPath(Node* current) {
    vector<Node*> path;
    while (current != nullptr) {
        path.push_back(current);
        current = current->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<Node*> findPath(Node* start, Node* goal) {
    priority_queue<Node*, vector<Node*>, Compare> openList;
    bool closedList[ROWS][COLS] = {false};

    start->gCost = 0;
    start->hCost = heuristic(start, goal);
    start->fCost = start->gCost + start->hCost;
    openList.push(start);

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current->x == goal->x && current->y == goal->y) {
            return reconstructPath(current);
        }

        closedList[current->x][current->y] = true;

        for (auto dir : directions) {
            int newX = current->x + dir.first;
            int newY = current->y + dir.second;

            if (!isValid(newX, newY) || grid[newX][newY] == 1 || closedList[newX][newY]) {
                continue;
            }

            Node* neighbor = new Node(newX, newY);
            int tentativeG = current->gCost + 1;

            if (tentativeG < neighbor->gCost) {
                neighbor->gCost = tentativeG;
                neighbor->hCost = heuristic(neighbor, goal);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                neighbor->parent = current;

                openList.push(neighbor);
            }
        }
    }
    return {}; // No path found
}

int main() {
    Node* start = new Node(0, 0);
    Node* goal = new Node(4, 4);

    vector<Node*> path = findPath(start, goal);

    if (!path.empty()) {
        cout << "Path found:\n";
        for (Node* node : path) {
            cout << "(" << node->x << ", " << node->y << ")\n";
        }
    } else {
        cout << "No path found.\n";
    }

    return 0;
}

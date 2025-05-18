#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Cell {
    int x, y;
    int heuristic;
    Cell* parent;

    Cell(int x, int y, int h, Cell* p) : x(x), y(y), heuristic(h), parent(p) {}

    // For priority_queue, we invert comparison because it is a max-heap by default
    bool operator>(const Cell& other) const {
        return heuristic > other.heuristic;
    }
};

const vector<pair<int,int>> directions = { {0,1}, {1,0}, {0,-1}, {-1,0} };

int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool isValid(int x, int y, int rows, int cols, const vector<vector<int>>& grid, const vector<vector<bool>>& visited) {
    return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0 && !visited[x][y];
}

void printPath(Cell* goal) {
    vector<Cell*> path;
    while (goal != nullptr) {
        path.push_back(goal);
        goal = goal->parent;
    }
    reverse(path.begin(), path.end());

    for (auto cell : path) {
        cout << "(" << cell->x << ", " << cell->y << ")" << endl;
    }
}

void bestFirstSearch(const vector<vector<int>>& grid, int sx, int sy, int gx, int gy) {
    int rows = (int)grid.size();
    int cols = (int)grid[0].size();

    // Min-heap priority queue for Cell using heuristic
    priority_queue<Cell, vector<Cell>, greater<Cell>> openList;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    Cell start(sx, sy, manhattan(sx, sy, gx, gy), nullptr);
    openList.push(start);
    visited[sx][sy] = true;

    // To manage parent pointers without memory leaks, we store allocated Cells here
    vector<Cell> allCells;
    allCells.push_back(start);
    Cell* goalCell = nullptr;

    while (!openList.empty()) {
        Cell current = openList.top();
        openList.pop();

        if (current.x == gx && current.y == gy) {
            // We must find the Cell* in allCells corresponding to current to get parent links
            for (auto& cell : allCells) {
                if (cell.x == current.x && cell.y == current.y && cell.heuristic == current.heuristic) {
                    goalCell = &cell;
                    break;
                }
            }
            cout << "Goal reached!" << endl;
            printPath(goalCell);
            return;
        }

        for (auto& dir : directions) {
            int newX = current.x + dir.first;
            int newY = current.y + dir.second;

            if (isValid(newX, newY, rows, cols, grid, visited)) {
                visited[newX][newY] = true;
                int h = manhattan(newX, newY, gx, gy);
                // Parent pointer to current Cell in allCells, find it
                Cell* parentPtr = nullptr;
                for (auto& cell : allCells) {
                    if (cell.x == current.x && cell.y == current.y && cell.heuristic == current.heuristic) {
                        parentPtr = &cell;
                        break;
                    }
                }
                allCells.emplace_back(newX, newY, h, parentPtr);
                openList.push(allCells.back());
            }
        }
    }
    cout << "No path found." << endl;
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };

    int startX = 0, startY = 0;
    int goalX = 4, goalY = 3;

    bestFirstSearch(grid, startX, startY, goalX, goalY);

    return 0;
}


#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <tuple>

using namespace std;

struct State {
    int M_left, C_left, boat; // boat: 0 = left, 1 = right

    State(int m, int c, int b) : M_left(m), C_left(c), boat(b) {}

    bool operator==(const State& other) const {
        return M_left == other.M_left && C_left == other.C_left && boat == other.boat;
    }

    bool operator<(const State& other) const {
        return tie(M_left, C_left, boat) < tie(other.M_left, other.C_left, other.boat);
    }

    string toString() const {
        return "(M_left: " + to_string(M_left) + ", C_left: " + to_string(C_left) +
               ", Boat: " + (boat == 0 ? "Left" : "Right") + ")";
    }
};

int M_total, C_total, boat_capacity;

bool isValidState(int M_left, int C_left) {
    int M_right = M_total - M_left;
    int C_right = C_total - C_left;

    if (M_left < 0 || C_left < 0 || M_left > M_total || C_left > C_total) return false;
    if (M_left > 0 && M_left < C_left) return false;
    if (M_right > 0 && M_right < C_right) return false;

    return true;
}

vector<pair<int, int>> generateMoves(int capacity) {
    vector<pair<int, int>> moves;
    for (int m = 0; m <= capacity; ++m) {
        for (int c = 0; c <= capacity; ++c) {
            int total = m + c;
            if (total >= 1 && total <= capacity) {
                moves.emplace_back(m, c);
            }
        }
    }
    return moves;
}

vector<State> getNextStates(const State& s, const vector<pair<int, int>>& moves) {
    vector<State> nextStates;
    for (auto& move : moves) {
        int M_move = move.first;
        int C_move = move.second;
        State newState = s;

        if (s.boat == 0) { // Boat on left going right
            newState = State(s.M_left - M_move, s.C_left - C_move, 1);
        } else { // Boat on right going left
            newState = State(s.M_left + M_move, s.C_left + C_move, 0);
        }

        if (isValidState(newState.M_left, newState.C_left)) {
            nextStates.push_back(newState);
        }
    }
    return nextStates;
}

void printPath(const vector<State>& path) {
    int step = 0;
    for (const auto& s : path) {
        cout << "Step " << step++ << ": " << s.toString() << endl;
    }
}

vector<State> dfs() {
    State start(M_total, C_total, 0);
    State goal(0, 0, 1);
    vector<pair<int, int>> moves = generateMoves(boat_capacity);

    stack<vector<State>> stk;
    set<State> visited;

    stk.push({start});

    while (!stk.empty()) {
        vector<State> path = stk.top();
        stk.pop();

        State current = path.back();

        if (current == goal) {
            return path;
        }

        if (visited.find(current) != visited.end()) {
            continue;
        }
        visited.insert(current);

        for (auto& next : getNextStates(current, moves)) {
            if (visited.find(next) == visited.end()) {
                vector<State> newPath = path;
                newPath.push_back(next);
                stk.push(newPath);
            }
        }
    }

    return {};
}

int main() {
    cout << "Enter number of missionaries: ";
    cin >> M_total;
    cout << "Enter number of cannibals: ";
    cin >> C_total;
    cout << "Enter boat capacity: ";
    cin >> boat_capacity;

    vector<State> solution = dfs();
    if (!solution.empty()) {
        cout << "\nSolution found (DFS):\n";
        printPath(solution);
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}
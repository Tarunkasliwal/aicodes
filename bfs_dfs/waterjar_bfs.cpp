#include <iostream>
#include <queue>
#include <set>
#include <tuple> 

using namespace std;

// special structure ffor this problem
struct State {
    int four, three;

    bool operator<(const State& other) const {
        return tie(four, three) < tie(other.four, other.three);
    }
};

void bfsWaterJug() {
    queue<State> q;
    set<State> visited;

    q.push({0, 0}); // Initial state (0,0)

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (visited.count(current)) continue;//count function 
        visited.insert(current);

        cout << "(" << current.four << ", " << current.three << ")\n";

        // Goal condition
        if (current.four == 2) {
            cout << "Solution found!\n";
            return;
        }

        // Possible moves:
        vector<State> nextMoves = {
            {4, current.three}, // Fill 4L
            {current.four, 3},  // Fill 3L
            {0, current.three}, // Empty 4L
            {current.four, 0},  // Empty 3L
            {max(0, current.four - (3 - current.three)), min(3, current.three + current.four)}, // Pour 4L -> 3L
            {min(4, current.four + current.three), max(0, current.three - (4 - current.four))}  // Pour 3L -> 4L
        };

        for (auto next : nextMoves) {
            if (!visited.count(next)) q.push(next);
        }
    }

    cout << "No solution found.\n";
}

int main() {
    bfsWaterJug();
    return 0;
}
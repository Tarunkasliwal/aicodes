#include <iostream>
#include <vector>
using namespace std;

bool isValid(int s, int e, int n, int d, int m, int o, int r, int y) {
    int send = s * 1000 + e * 100 + n * 10 + d;
    int more = m * 1000 + o * 100 + r * 10 + e;
    int money = m * 10000 + o * 1000 + n * 100 + e * 10 + y;

    return (send + more == money);
}

bool isUnique(const vector<int>& values) {
    vector<bool> used(10, false);
    for (int val : values) {
        if (used[val]) return false;
        used[val] = true;
    }
    return true;
}

// Letters: S, E, N, D, M, O, R, Y
// We'll assign digits to letters in order using backtracking.
bool solveCryptarithmetic(vector<int>& assigned, vector<bool>& used, int pos, int& count) {
    if (pos == 8) {
        // All letters assigned: S E N D M O R Y = assigned[0..7]
        int s = assigned[0], e = assigned[1], n = assigned[2], d = assigned[3];
        int m = assigned[4], o = assigned[5], r = assigned[6], y = assigned[7];

        // Leading digits S and M can't be zero
        if (s == 0 || m == 0)
            return false;

        if (isValid(s, e, n, d, m, o, r, y)) {
            count++;
            cout << "Solution " << count << ":\n";
            cout << "S=" << s << " E=" << e << " N=" << n << " D=" << d
                 << " M=" << m << " O=" << o << " R=" << r << " Y=" << y << endl << endl;
            return true; // to find all solutions, do not return here, but continue
        }
        return false;
    }

    bool foundSolution = false;
    for (int digit = 0; digit <= 9; digit++) {
        if (!used[digit]) {
            assigned[pos] = digit;
            used[digit] = true;

            if (solveCryptarithmetic(assigned, used, pos + 1, count))
                foundSolution = true;

            used[digit] = false; // backtrack
        }
    }
    return foundSolution;
}

int main() {
    vector<int> assigned(8, -1); // S E N D M O R Y
    vector<bool> used(10, false);
    int count = 0;

    if (!solveCryptarithmetic(assigned, used, 0, count))
        cout << "No solution found.\n";

    return 0;
}


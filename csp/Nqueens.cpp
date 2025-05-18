#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class NQueens {
private:
    int N;

    // Check if placing a queen at board[row][col] is safe
    bool isSafe(const vector<int>& board, int row, int col) {
        for (int i = 0; i < row; i++) {
            if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
                return false; // Column or diagonal conflict
            }
        }
        return true;
    }

    // Recursive backtracking solver
    bool solveNQueens(vector<int>& board, int row, bool findAll) {
        if (row == N) {
            printSolution(board);
            return !findAll; // If only one solution needed, return true to stop
        }

        bool res = false;
        for (int col = 0; col < N; col++) {
            if (isSafe(board, row, col)) {
                board[row] = col;  // Place queen
                bool solved = solveNQueens(board, row + 1, findAll);
                res = res || solved;
                board[row] = -1;  // Backtrack
                if (solved && !findAll) {
                    // If only one solution requested, stop recursion
                    return true;
                }
            }
        }
        return res;
    }

    // Print board solution
    void printSolution(const vector<int>& board) {
        cout << "Solution:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i] == j) {
                    cout << " Q ";
                } else {
                    cout << " . ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

public:
    NQueens(int n) : N(n) {}

    void solve(bool findAll) {
        vector<int> board(N, -1);
        if (!solveNQueens(board, 0, findAll)) {
            cout << "No solution exists for N = " << N << endl;
        }
    }
};

int main() {
    int N;
    cout << "Enter the number of queens (N): ";
    cin >> N;

    if (N <= 0) {
        cout << "Invalid input! N must be positive." << endl;
        return 1;
    }

    cout << "Do you want to find all solutions? (y/n): ";
    char choice;
    cin >> choice;

    bool findAll = (choice == 'y' || choice == 'Y');

    NQueens nq(N);
    nq.solve(findAll);

    return 0;
}

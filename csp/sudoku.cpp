#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<char>> ans;

    bool isValid(vector<vector<char>>& board, int row, int col, char digit) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == digit || board[i][col] == digit)
                return false;
        }

        int smr = row / 3 * 3;
        int smc = col / 3 * 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[smr + i][smc + j] == digit)
                    return false;
            }
        }

        return true;
    }

    void solve(vector<vector<char>>& board, int row, int col) {
        if (row == 9) {
            ans = board;
            return;
        }

        int nr = (col == 8) ? row + 1 : row;
        int nc = (col == 8) ? 0 : col + 1;

        if (board[row][col] != '.') {
            solve(board, nr, nc);
        } else {
            for (char digit = '1'; digit <= '9'; digit++) {
                if (isValid(board, row, col, digit)) {
                    board[row][col] = digit;
                    solve(board, nr, nc);
                    board[row][col] = '.';
                }
            }
        }
    }

    void solveSudoku(vector<vector<char>>& board) {
        ans = vector<vector<char>>(9, vector<char>(9));
        solve(board, 0, 0);
        board = ans;
    }
};

// Helper function to print the board
void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char c : row)
            cout << c << ' ';
        cout << endl;
    }
}

// Main function
int main() {
    vector<vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    Solution solver;
    solver.solveSudoku(board);

    cout << "Solved Sudoku:" << endl;
    printBoard(board);

    return 0;
}
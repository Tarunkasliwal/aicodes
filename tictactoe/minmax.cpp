#include <iostream>
#include <limits>
using namespace std;

#define SIZE 3
#define EMPTY ' '

char USER, AI;
const char MAX_PLAYER = 'X';
const char MIN_PLAYER = 'O';

void printBoard(char board[SIZE][SIZE]) {
    cout << "\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << " " << board[i][j];
            if (j < SIZE - 1) cout << " |";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool isGameOver(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
            (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[1][i] == board[2][i]))
            return true;
    }

    if ((board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0]))
        return true;

    return false;
}

int cal(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0] == AI ? 10 : -10;
        if (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i] == AI ? 10 : -10;
    }

    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0] == AI ? 10 : -10;
    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2] == AI ? 10 : -10;

    return 0;
}

bool isMovesLeft(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == EMPTY)
                return true;
    return false;
}

int minimax(char board[SIZE][SIZE], int depth, bool isMaximizing) {
    int score = cal(board);
    if (score == 10 || score == -10)
        return score - depth; // Encourage faster win or delayed loss
    if (!isMovesLeft(board))
        return 0;

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                if (board[i][j] == EMPTY) {
                    board[i][j] = USER;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
        return best;
    }
}

void aiMove(char board[SIZE][SIZE], int ply) {
    int bestVal = -1000;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;

                cout << "Evaluated AI move (" << i << ", " << j << ") => Heuristic: " << moveVal << "\n";

                if (moveVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }

    board[bestRow][bestCol] = AI;
    cout << "AI chooses move (" << bestRow << ", " << bestCol << ") with heuristic " << bestVal << "\n";
}

void userMove(char board[SIZE][SIZE]) {
    int row, col;
    while (true) {
        cout << "Enter your move (row and column 0-2): ";
        cin >> row >> col;
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == EMPTY) {
            board[row][col] = USER;
            break;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
}

int main() {
    char board[SIZE][SIZE] = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };

    cout << "Choose your symbol (X or O): ";
    cin >> USER;
    USER = toupper(USER);
    AI = (USER == 'X') ? 'O' : 'X';

    int ply;
    cout << "Enter search depth (ply): ";
    cin >> ply;

    printBoard(board);
    bool isUserTurn = (USER == 'X');
    while (true) {
        if (isUserTurn) {
            userMove(board);
        } else {
            aiMove(board, ply);
        }

        printBoard(board);

        int score = cal(board);
        if (score == 10 || score == -10) {
            if ((score > 0 && AI == MAX_PLAYER) || (score < 0 && AI == MIN_PLAYER))
                cout << "AI wins!\n";
            else
                cout << "You win!\n";
            break;
        } else if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }

        isUserTurn = !isUserTurn;
    }

    return 0;
}

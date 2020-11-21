#include "sudoku.h"


int canPlace(int **, int, int, int);
int solveRecursively(int **, int, int);


void solve(int **board) {
	for (int index = 0; index < 81; ++index) {
		int i = index / 9;
		int j = index % 9;
		if (board[i][j] == 0) {
			solveRecursively(board, i, j);
			break;
		}
	}
}


int canPlace(int **board, int i, int j, int value) {
    for (int m = 0; m < 9; ++m) {
        if (m != j && board[i][m] != 0 && board[i][m] == value) return 0;
        if (m != i && board[m][j] != 0 && board[m][j] == value) return 0;
    }

    int squareI = (i/3) * 3;
    int squareJ = (j/3) * 3;
    for (int m = squareI; m < squareI + 3; ++m) {
        for (int n = squareJ; n < squareJ + 3; ++n) {
            if (board[m][n] != 0 && board[m][n] == value) return 0;
        }
    }

    return 1;
}


int solveRecursively(int **board, int i, int j) {
    int value;
    for (value = 1; value <= 9; ++value) {
        if (canPlace(board, i, j, value) == 1) {
            board[i][j] = value;
            int index1d = i * 9 + j;
            int last = 1;
            for (int index = index1d + 1; index < 81; ++index) {
                int m = index / 9;
                int n = index % 9;
                if (board[m][n] == 0) {
                    last = 0;
                    if (solveRecursively(board, m, n) == 1) return 1;
                    else break;
                }
            }
            if (last == 1) return 1;
        }
    }

    if (value == 10) {
        board[i][j] = 0;
        return 0;
    }
    else return 1;
}

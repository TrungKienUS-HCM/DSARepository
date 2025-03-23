#include <iostream>
using namespace std;
const int N = 8;
int board[N][N] = { 0 };
int solution = 0;

// The function used to check if the position of board[row][col] is safe to place a queen
bool isSafe(int row, int col) {
	for (int i = 0; i < row; ++i) {
		// Check the column
		if (board[i][col]) return false;
		// Check the left diagonal
		if (col - (row - i) >= 0 and board[i][col - (row - i)]) return false;
		// Check the right diagonal
		if (col + (row - i) < N and board[i][col + (row - i)]) return false;
	}
	return true;
}

void solveNQueens(int row) {
	// When all queens are placed successfully in each row
	if (row == N) {
		solution++;
		return;
	}
	// Searching through all elements of a row to find a safe position to place a queen
	for (int i = 0; i < N; ++i) {
		if (isSafe(row, i)) {
			// Place a queen
			board[row][i] = 1;
			// Recursive call to the next row (continously find a safe place in the next row to place a queen)
			solveNQueens(row + 1);
			// Backtrack to remove the placed queen after considering its position
			board[row][i] = 0;
		}
	}
}

int main() {
	solveNQueens(0);
	cout << solution << endl;
}
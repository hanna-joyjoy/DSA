#include <iostream>
using namespace std;
const int N = 8; 
int board[N][N] = { 0 }; 
int solutions = 0; 
bool isSafe(int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		if (board[i][col] == 1)
			return false; 
		if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1)
			return false; 
		if (col + (row - i) < N && board[i][col + (row - i)] == 1)
			return false; 
	}
	return true;}void solveNQueens(int row)
{
	if (row == N)
	{ 
		solutions++;
		return;
	}
	for (int col = 0; col < N; col++)
	{
		if (isSafe(row, col))
		{
			board[row][col] = 1;
			solveNQueens(row + 1);
			board[row][col] = 0; 
		}
	}
}

int main()
{
	solveNQueens(0);
	cout << solutions << endl;
	return 0;
}
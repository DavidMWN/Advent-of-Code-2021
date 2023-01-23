#pragma once

class BingoBoard
{
private:
	int board[5][5];
	bool marks[5][5];
	bool hasWon;

public:
	BingoBoard();
	void FillBoard(int row, int columns[]);
	void MarkNumber(int number);
	bool CheckForBingo();
	int BoardScore(int numberCalled);
	bool GetHasWon();
};
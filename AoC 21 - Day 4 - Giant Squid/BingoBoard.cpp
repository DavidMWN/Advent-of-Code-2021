#include "BingoBoard.h"

BingoBoard::BingoBoard()
{
	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			board[row][col] = 0;
			marks[row][col] = false;
		}
	}

	hasWon = false;
}

void BingoBoard::FillBoard(int row, int columns[])
{
	for (int i = 0; i < 5; i++)
	{
		board[row][i] = columns[i];
	}
}

void BingoBoard::MarkNumber(int number)
{
	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			if (board[row][col] == number)
			{
				marks[row][col] = true;
				return;
			}
		}
	}
}

bool BingoBoard::CheckForBingo()
{
	// Check rows
	for (int row = 0; row < 5; row++)
	{
		int marked = 0;

		for (int col = 0; col < 5; col++)
		{
			if (!marks[row][col])
				break;

			marked++;

			if (marked == 5)
			{
				return true;
			}
		}
	}

	// Check columns
	for (int col = 0; col < 5; col++)
	{
		int marked = 0;

		for (int row = 0; row < 5; row++)
		{
			if (!marks[row][col])
				break;

			marked++;

			if (marked == 5)
			{
				return true;
			}
		}
	}

	return false;
}

int BingoBoard::BoardScore(int numberCalled)
{
	hasWon = true;

	int unmarkedSum = 0;

	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			if (!marks[row][col])
			{
				unmarkedSum += board[row][col];
			}
		}
	}

	return unmarkedSum * numberCalled;
}

bool BingoBoard::GetHasWon()
{
	return hasWon;
}
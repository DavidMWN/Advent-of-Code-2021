#include "VentGrid.h"

VentGrid::VentGrid(int xSize, int ySize, bool diagonalAllowed)
{
	for (int i = 0; i < ySize; i++)
		grid.push_back(std::vector<int>(xSize, 0));

	allowDiagonal = diagonalAllowed;
}

void VentGrid::MarkVentLine(int xStart, int yStart, int xEnd, int yEnd)
{
	if (CheckIfHorizontalLine(yStart, yEnd) && CheckIfVerticalLine(xStart, xEnd))
	{
		grid[yStart][xStart]++;
		return;
	}

	if (CheckIfHorizontalLine(yStart, yEnd))
	{
		if (xEnd > xStart)
		{
			for (int x = xStart; x <= xEnd; x++)
				grid[yStart][x]++;

			return;
		}
		else if (xEnd < xStart)
		{
			for (int x = xStart; x >= xEnd; x--)
				grid[yStart][x]++;

			return;
		}
	}
		
	if (CheckIfVerticalLine(xStart, xEnd))
	{
		if (yEnd > yStart)
		{
			for (int y = yStart; y <= yEnd; y++)
				grid[y][xStart]++;

			return;
		}
		else if (yEnd < yStart)
		{
			for (int y = yStart; y >= yEnd; y--)
				grid[y][xStart]++;

			return;
		}
	}

	if (!allowDiagonal)
		return;

	if (xEnd > xStart)
	{
		int xMod = 0;

		if (yEnd > yStart)
		{
			for (int y = yStart; y <= yEnd; y++)
			{
				grid[y][xStart + xMod]++;
				xMod++;
			}

			return;
		}

		if (yEnd < yStart)
		{
			for (int y = yStart; y >= yEnd; y--)
			{
				grid[y][xStart + xMod]++;
				xMod++;
			}

			return;
		}
	}

	if (xEnd < xStart)
	{
		int xMod = 0;

		if (yEnd > yStart)
		{
			for (int y = yStart; y <= yEnd; y++)
			{
				grid[y][xStart - xMod]++;
				xMod++;
			}

			return;
		}

		if (yEnd < yStart)
		{
			for (int y = yStart; y >= yEnd; y--)
			{
				grid[y][xStart - xMod]++;
				xMod++;
			}

			return;
		}
	}
}

bool VentGrid::CheckIfHorizontalLine(int yStart, int yEnd)
{
	if (yStart == yEnd)
		return true;

	return false;
}

bool VentGrid::CheckIfVerticalLine(int xStart, int xEnd)
{
	if (xStart == xEnd)
		return true;

	return false;
}

void VentGrid::TestPrint()
{
	for (int y = 0; y < grid.size(); y++)
	{
		for (int x = 0; x < grid[y].size(); x++)
			std::cout << grid[y][x] << " ";

		std::cout << std::endl;
	}
}

int VentGrid::FindOverlapCount()
{
	int overlapCount = 0;

	for (int y = 0; y < grid.size(); y++)
	{
		for (int x = 0; x < grid[y].size(); x++)
		{
			if (grid[y][x] > 1)
				overlapCount++;
		}
	}

	return overlapCount;
}
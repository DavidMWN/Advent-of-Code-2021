#pragma once
#include <vector>
#include <iostream>

class VentGrid
{
private:
	std::vector< std::vector<int> > grid;
	bool allowDiagonal;
	
	bool CheckIfHorizontalLine(int xStart, int xEnd);
	bool CheckIfVerticalLine(int yStart, int yEnd);

public:
	VentGrid(int xSize, int ySize, bool diagonalAllowed);
	void MarkVentLine(int xStart, int yStart, int xEnd, int yEnd);
	void TestPrint();
	int FindOverlapCount();
};
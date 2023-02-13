#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

void PrintPaper(std::vector<std::vector<char>> paper)
{
	for (int p = 0; p < paper.size(); p++)
	{
		for (int q = 0; q < paper[p].size(); q++)
			std::cout << paper[p][q];

		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;
}

void OneFold(std::vector<std::vector<char>>& paper, char foldAxis, int foldLine)
{
	if (foldAxis == 'y')
	{
		for (int y = paper.size() - 1; y >= foldLine; y--)
		{
			int distanceFromFoldY = abs(y - foldLine);

			for (int x = 0; x < paper[y].size(); x++)
			{
				if (paper[y][x] == '#')
				{
					paper[abs(foldLine - distanceFromFoldY)][x] = '#';
				}
			}

			paper.pop_back();
		}

		return;
	}

	for (int y = 0; y < paper.size(); y++)
	{
		for (int x = paper[y].size() - 1; x >= foldLine; x--)
		{
			int distanceFromFoldX = abs(x - foldLine);

			if (paper[y][x] == '#')
			{
				paper[y][abs(foldLine - distanceFromFoldX)] = '#';
			}

			paper[y].pop_back();
		}
	}

	return;
}

int main()
{
	std::ifstream file("InstructionInput.txt");
	std::string str;
	std::vector<std::string> coordinateLines;
	std::vector<std::string> instructionLines;

	while (std::getline(file, str))
	{
		if (str == "")
			continue;

		if (isdigit(str[0]))
		{
			coordinateLines.push_back(str);
			continue;
		}

		instructionLines.push_back(str);
	}

	// Extract coordinates

	std::vector<int> xCoordinates;
	std::vector<int> yCoordinates;

	for (int i = 0; i < coordinateLines.size(); i++)
	{
		std::vector<std::string> temp;

		std::stringstream s_stream(coordinateLines[i]);

		while (s_stream.good())
		{
			std::string substr;
			std::getline(s_stream, substr, ',');
			temp.push_back(substr);
		}

		xCoordinates.push_back(std::stoi(temp[0]));
		yCoordinates.push_back(std::stoi(temp[1]));
	}

	// Create coordinate plane

	int maxX = *max_element(xCoordinates.begin(), xCoordinates.end());
	int maxY = *max_element(yCoordinates.begin(), yCoordinates.end());

	std::vector<std::vector<char>> coordinatePaper;

	for (int y = 0; y <= maxY; y++)
	{
		std::vector<char> tempCoord;

		for (int x = 0; x <= maxX; x++)
		{
			tempCoord.push_back('.');
		}

		coordinatePaper.push_back(tempCoord);
	}

	// Populate coordinate plane

	for (int i = 0; i < xCoordinates.size(); i++)
	{
		coordinatePaper[yCoordinates[i]][xCoordinates[i]] = '#';
	}

	//PrintPaper(coordinatePaper);

	// Extract fold instructions

	std::vector<char> foldAxisList;
	std::vector<int> foldLineList;

	for (int i = 0; i < instructionLines.size(); i++)
	{
		std::vector<std::string> temp;

		std::stringstream s_stream(instructionLines[i]);

		while (s_stream.good())
		{
			std::string substr;
			std::getline(s_stream, substr, '=');
			temp.push_back(substr);
		}

		foldAxisList.push_back(temp[0][temp[0].size() - 1]);
		foldLineList.push_back(std::stoi(temp[1]));
	}

	// Part 1 - Just the first fold

	OneFold(coordinatePaper, foldAxisList[0], foldLineList[0]);

	//PrintPaper(coordinatePaper);

	int dotCount = 0;

	for (int y = 0; y < coordinatePaper.size(); y++)
	{
		for (int x = 0; x < coordinatePaper[y].size(); x++)
		{
			if (coordinatePaper[y][x] == '#')
				dotCount++;
		}
	}

	std::cout << dotCount << std::endl << std::endl;

	// Part 2 - Complete the folds

	for (int f = 1; f < foldAxisList.size(); f++)
	{
		OneFold(coordinatePaper, foldAxisList[f], foldLineList[f]);
	}

	PrintPaper(coordinatePaper);
}
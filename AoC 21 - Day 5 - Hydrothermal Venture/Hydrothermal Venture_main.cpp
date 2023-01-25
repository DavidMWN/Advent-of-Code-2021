#include <fstream>
#include <string>
#include <sstream>
#include "VentGrid.h"

int main()
{
	std::ifstream file("VentLineInput.txt");
	std::string str;
	std::vector<std::string> ventLines;

	while (std::getline(file, str))
	{
		ventLines.push_back(str);
	}

	// Part 1

	VentGrid ventGrid(1000, 1000, false);

	for (int i = 0; i < ventLines.size(); i++)
	{
		std::vector<std::string> ventPath;
		std::vector<int> lineStart;
		std::vector<int> lineEnd;

		std::stringstream s_stream(ventLines[i]);
		
		while (s_stream.good())
		{
			std::string substr;
			std::getline(s_stream, substr, ' ');
			ventPath.push_back(substr);
		}

		for (int j = 0; j < ventPath.size(); j += 2)
		{
			std::stringstream s_stream2(ventPath[j]);

			while (s_stream2.good())
			{
				std::string substr;
				std::getline(s_stream2, substr, ',');

				if (j == 0)
					lineStart.push_back(stoi(substr));
				if (j == 2)
					lineEnd.push_back(stoi(substr));
			}
		}

		ventGrid.MarkVentLine(lineStart[0], lineStart[1], lineEnd[0], lineEnd[1]);
	}

	//ventGrid.TestPrint();

	std::cout << ventGrid.FindOverlapCount() << std::endl << std::endl;

	// Part 2

	VentGrid ventGrid2(1000, 1000, true);

	for (int i = 0; i < ventLines.size(); i++)
	{
		std::vector<std::string> ventPath;
		std::vector<int> lineStart;
		std::vector<int> lineEnd;

		std::stringstream s_stream(ventLines[i]);

		while (s_stream.good())
		{
			std::string substr;
			std::getline(s_stream, substr, ' ');
			ventPath.push_back(substr);
		}

		for (int j = 0; j < ventPath.size(); j += 2)
		{
			std::stringstream s_stream2(ventPath[j]);

			while (s_stream2.good())
			{
				std::string substr;
				std::getline(s_stream2, substr, ',');

				if (j == 0)
					lineStart.push_back(stoi(substr));
				if (j == 2)
					lineEnd.push_back(stoi(substr));
			}
		}

		ventGrid2.MarkVentLine(lineStart[0], lineStart[1], lineEnd[0], lineEnd[1]);
	}

	//ventGrid2.TestPrint();

	std::cout << ventGrid2.FindOverlapCount() << std::endl << std::endl;
}
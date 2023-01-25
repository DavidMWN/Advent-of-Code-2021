#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>

int main()
{
	std::ifstream file("CrabInput.txt");
	std::string crabInput;

	std::getline(file, crabInput);

	std::vector<int> crabPositions;

	std::stringstream s_stream(crabInput);

	while (s_stream.good())
	{
		std::string substr;
		std::getline(s_stream, substr, ',');
		crabPositions.push_back(stoi(substr));
	}

	// Part 1

	std::list<int> fuelCosts;

	for (int i = 0; i < crabPositions.size(); i++)
	{
		int tempFuelCost = 0;

		for (int f = 0; f < crabPositions.size(); f++)
		{
			tempFuelCost += (abs(crabPositions[f] - crabPositions[i]));
		}

		fuelCosts.push_back(tempFuelCost);
	}

	fuelCosts.sort();

	std::cout << fuelCosts.front() << std::endl << std::endl;

	// Part 2

	std::list<int64_t> fuelCostsAdjusted;

	int minPos = *std::min_element(crabPositions.begin(), crabPositions.end());
	int maxPos = *std::max_element(crabPositions.begin(), crabPositions.end());

	for (int i = minPos; i <= maxPos; i++)
	{
		int64_t tempFuelCost = 0;

		for (int f = 0; f < crabPositions.size(); f++)
		{
			int temp = (abs(crabPositions[f] - i));

			for (int t = 1; t <= temp; t++)
				tempFuelCost += t;
		}

		fuelCostsAdjusted.push_back(tempFuelCost);
	}

	fuelCostsAdjusted.sort();

	std::cout << fuelCostsAdjusted.front() << std::endl << std::endl;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <sstream>

int main()
{
    std::ifstream file("LanternfishInput.txt");
    std::string lanternfishInput;

    std::getline(file, lanternfishInput);

    std::vector<int> lanternfishStart;

    std::stringstream s_stream(lanternfishInput);

    while (s_stream.good())
    {
        std::string substr;
        std::getline(s_stream, substr, ',');
        lanternfishStart.push_back(stoi(substr));
    }

    // Part 1

    std::array<int, 9> fishAges = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    for (int i = 0; i < lanternfishStart.size(); i++)
        fishAges[lanternfishStart[i]]++;

    for (int i = 0; i < 80; i++)
    {
        std::array<int, 9> fishTemp = fishAges;

        for (int a = 7; a >= 0; a--)
        {
            fishAges[a] = fishTemp[a + 1];
        }

        fishAges[6] += fishTemp[0];
        fishAges[8] = fishTemp[0];
    }

    int fishSum = 0;

    for (int i = 0; i < fishAges.size(); i++)
    {
        fishSum += fishAges[i];
    }

    std::cout << fishSum << std::endl << std::endl;

    // Part 2

    std::array<int64_t, 9> fishAges2 = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    for (int i = 0; i < lanternfishStart.size(); i++)
        fishAges2[lanternfishStart[i]]++;

    for (int i = 0; i < 256; i++)
    {
        std::array<int64_t, 9> fishTemp = fishAges2;

        for (int a = 7; a >= 0; a--)
        {
            fishAges2[a] = fishTemp[a + 1];
        }

        fishAges2[6] += fishTemp[0];
        fishAges2[8] = fishTemp[0];
    }

    int64_t fishSum2 = 0;

    for (int i = 0; i < fishAges2.size(); i++)
    {
        fishSum2 += fishAges2[i];
    }

    std::cout << fishSum2 << std::endl << std::endl;
}
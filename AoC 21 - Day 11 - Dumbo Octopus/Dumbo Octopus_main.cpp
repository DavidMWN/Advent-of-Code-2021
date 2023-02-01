#include <iostream>
#include <fstream>
#include "OctoField.h"

int main()
{
    std::ifstream file("OctopusInput.txt");
    std::string octoLines;

    std::vector<std::string> octoInput;

    while (std::getline(file, octoLines))
        octoInput.push_back(octoLines);

    // Part 1
    OctoField octoField(octoInput);

    for (int i = 0; i < 100; i++)
    {
        octoField.Step();
    }

    int flashCount = octoField.GetTotalFlashCount();

    std::cout << flashCount << std::endl << std::endl;

    // Part 2
    OctoField octoFieldSimultaneousFlash(octoInput);

    while (!octoFieldSimultaneousFlash.GetSimultaneousFlash())
    {
        octoFieldSimultaneousFlash.Step();
    }

    int simultaneousFlashStep = octoFieldSimultaneousFlash.GetStepCount();

    std::cout << simultaneousFlashStep << std::endl << std::endl;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include "CaveNode.h"

void SearchCaveNodes(std::vector<std::string>& path, const std::vector<CaveNode>& caveSystem, const CaveNode& currentNode, std::vector<std::vector<std::string>>& completePaths)
{
    std::vector<std::string> tempPath = path;

    if (islower(currentNode.GetCaveName()[0]))
    {
        if (std::find(tempPath.begin(), tempPath.end(), currentNode.GetCaveName()) != tempPath.end())
            return;
    }

    tempPath.push_back(currentNode.GetCaveName());

    if (currentNode.GetCaveName() == "end")
    {
        completePaths.push_back(tempPath);
        return;
    }

    for (int i = 0; i < currentNode.GetConnectedCaves().size(); i++)
    {
        std::string caveName = currentNode.GetConnectedCaves()[i];
        auto findCave = (std::find_if(caveSystem.begin(), caveSystem.end(), [&caveName](const CaveNode& cave) {return cave.GetCaveName() == caveName; }));

        if (findCave != caveSystem.end())
        {
            int nextCaveIndex = std::distance(caveSystem.begin(), findCave);
            SearchCaveNodes(tempPath, caveSystem, caveSystem[nextCaveIndex], completePaths);
        }
    }
}

void SearchCaveNodesMore(std::vector<std::string>& path, const std::vector<CaveNode>& caveSystem, const CaveNode& currentNode, std::vector<std::vector<std::string>>& completePaths, bool smallCaveTwice)
{
    bool canVisitSmallCaveAgain = smallCaveTwice;

    std::vector<std::string> tempPath = path;

    if (islower(currentNode.GetCaveName()[0]))
    {
        if (std::find(tempPath.begin(), tempPath.end(), currentNode.GetCaveName()) != tempPath.end())
        {
            if (currentNode.GetCaveName() == "start")
                return;

            if (!canVisitSmallCaveAgain)
                return;
            else
                canVisitSmallCaveAgain = false;
        }
    }

    tempPath.push_back(currentNode.GetCaveName());

    if (currentNode.GetCaveName() == "end")
    {
        completePaths.push_back(tempPath);
        return;
    }

    for (int i = 0; i < currentNode.GetConnectedCaves().size(); i++)
    {
        std::string caveName = currentNode.GetConnectedCaves()[i];
        auto findCave = (std::find_if(caveSystem.begin(), caveSystem.end(), [&caveName](const CaveNode& cave) {return cave.GetCaveName() == caveName; }));

        if (findCave != caveSystem.end())
        {
            int nextCaveIndex = std::distance(caveSystem.begin(), findCave);
            SearchCaveNodesMore(tempPath, caveSystem, caveSystem[nextCaveIndex], completePaths, canVisitSmallCaveAgain);
        }
    }
}

int main()
{
    std::ifstream file("CaveInput.txt");
    std::string str;
    std::vector<std::string> caveLines;

    while (std::getline(file, str))
    {
        caveLines.push_back(str);
    }

    std::vector<CaveNode> caveSystem;

    for (int i = 0; i < caveLines.size(); i++)
    {
        std::stringstream s_stream(caveLines[i]);
        std::vector<std::string> inputCaves;

        while (s_stream.good())
        {
            std::string substr;
            std::getline(s_stream, substr, '-');
            inputCaves.push_back(substr);
        }

        // Adding caves to caveSystem if they are not already added
        for (int c = 0; c < inputCaves.size(); c++)
        {
            std::string caveName = inputCaves[c];
            auto findCave = (std::find_if(caveSystem.begin(), caveSystem.end(), [&caveName](const CaveNode& cave) {return cave.GetCaveName() == caveName; }));

            if (findCave != caveSystem.end())
                continue;
            else
                caveSystem.push_back(CaveNode(inputCaves[c]));
        }

        // Adding connecting caves to each cave in cave system
        for (int c = 0; c < inputCaves.size(); c++)
        {
            for (int x = 0; x < caveSystem.size(); x++)
            {
                if (caveSystem[x].GetCaveName() == inputCaves[c])
                {
                    for (int y = 0; y < inputCaves.size(); y++)
                    {
                        caveSystem[x].AddConnectedCave(inputCaves[y]);
                    }
                }
            }
        }
    }

    std::vector<std::string> path;

    // Part 1
    std::vector<std::vector<std::string>> completePaths;

    for (int i = 0; i < caveSystem.size(); i++)
    {
        if (caveSystem[i].GetCaveName() == "start")
            SearchCaveNodes(path, caveSystem, caveSystem[i], completePaths);
    }

    int pathCount = completePaths.size();

    std::cout << pathCount << std::endl << std::endl;

    // Part 2

    // Takes a minute or two to run the main input data, but it gets the right answer
    std::vector<std::vector<std::string>> moreCompletePaths;
    for (int i = 0; i < caveSystem.size(); i++)
    {
        if (caveSystem[i].GetCaveName() == "start")
            SearchCaveNodesMore(path, caveSystem, caveSystem[i], moreCompletePaths, true);
    }

    int morePathCount = moreCompletePaths.size();

    std::cout << morePathCount << std::endl << std::endl;
}
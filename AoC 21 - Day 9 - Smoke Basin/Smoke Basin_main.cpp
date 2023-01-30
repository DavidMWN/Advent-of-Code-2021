#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int basinSizeFinder(std::vector<std::vector<int>> map, int startY, int startX)
{
    std::vector<int> yQueue;
    std::vector<int> xQueue;

    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size()));
    for (int y = 0; y < visited.size(); y++)
    {
        for (int x = 0; x < visited[y].size(); x++)
            visited[y][x] = false;
    }

    yQueue.push_back(startY);
    xQueue.push_back(startX);
    visited[startY][startX] = true;

    while (!yQueue.empty())
    {
        // Check up
        if (yQueue[0] - 1 >= 0)
        {
            if (map[yQueue[0] - 1][xQueue[0]] < 9)
            {
                if (visited[yQueue[0] - 1][xQueue[0]] == false)
                {
                    yQueue.push_back(yQueue[0] - 1);
                    xQueue.push_back(xQueue[0]);
                    visited[yQueue[0] - 1][xQueue[0]] = true;
                }
            }                
        }

        // Check down
        if (yQueue[0] + 1 < map.size())
        {
            if (map[yQueue[0] + 1][xQueue[0]] < 9)
            {
                if (visited[yQueue[0] + 1][xQueue[0]] == false)
                {
                    yQueue.push_back(yQueue[0] + 1);
                    xQueue.push_back(xQueue[0]);
                    visited[yQueue[0] + 1][xQueue[0]] = true;
                }
            }
        }

        // Check left
        if (xQueue[0] - 1 >= 0)
        {
            if (map[yQueue[0]][xQueue[0] - 1] < 9)
            {
                if (visited[yQueue[0]][xQueue[0] - 1] == false)
                {
                    yQueue.push_back(yQueue[0]);
                    xQueue.push_back(xQueue[0] - 1);
                    visited[yQueue[0]][xQueue[0] - 1] = true;
                }
            }
                
        }

        // Check right
        if (xQueue[0] + 1 < map[0].size())
        {
            if (map[yQueue[0]][xQueue[0] + 1] < 9)
            {
                if (visited[yQueue[0]][xQueue[0] + 1] == false)
                {
                    yQueue.push_back(yQueue[0]);
                    xQueue.push_back(xQueue[0] + 1);
                    visited[yQueue[0]][xQueue[0] + 1] = true;
                }
            }
        }

        yQueue.erase(yQueue.begin() + 0);
        xQueue.erase(xQueue.begin() + 0);
    }

    int basinCount = 0;
    
    for (int y = 0; y < visited.size(); y++)
    {
        for (int x = 0; x < visited[y].size(); x++)
        {
            if (visited[y][x])
                basinCount++;
        }
    }

    return basinCount;
}

int main()
{
    std::ifstream file("HeightMapInput.txt");
    std::string heightMapInput;
        
    std::vector<std::vector<int>> heightMap;

    while (std::getline(file, heightMapInput))
    {       
        std::vector<int> temp;

        for (int i = 0; i < heightMapInput.size(); i++)
        {
            temp.push_back(heightMapInput[i] - '0');
        }

        heightMap.push_back(temp);
    }

    std::vector<int> lowPoints;
    std::vector<int> basinCounts;

    for (int y = 0; y < heightMap.size(); y++)
    {
        for (int x = 0; x < heightMap[y].size(); x++)
        {
            // Check up
            if (y - 1 >= 0)
            {
                if (heightMap[y][x] >= heightMap[y - 1][x])
                    continue;
            }

            // Check down
            if (y + 1 < heightMap.size())
            {
                if (heightMap[y][x] >= heightMap[y + 1][x])
                    continue;
            }

            // Check left
            if (x - 1 >= 0)
            {
                if (heightMap[y][x] >= heightMap[y][x - 1])
                    continue;
            }

            // Check right
            if (x + 1 < heightMap[y].size())
            {
                if (heightMap[y][x] >= heightMap[y][x + 1])
                    continue;
            }

            lowPoints.push_back(heightMap[y][x]);
            basinCounts.push_back(basinSizeFinder(heightMap, y, x));
        }
    }

    int riskLevelSum = 0;

    for (int i = 0; i < lowPoints.size(); i++)
        riskLevelSum += (lowPoints[i] + 1);

    std::cout << riskLevelSum << std::endl << std::endl;

    std::sort(basinCounts.begin(), basinCounts.end(), std::greater<>());

    int largestBasinProduct = basinCounts[0] * basinCounts[1] * basinCounts[2];

    std::cout << largestBasinProduct << std::endl << std::endl;
}
#include "OctoField.h"

OctoField::OctoField(std::vector<std::string> octoInput)
{
    totalOctos = 0;

	for (int y = 0; y < octoInput.size(); y++)
	{
		std::vector<int> tempInt;
		std::vector<bool> tempBool;

		for (int x = 0; x < octoInput[y].size(); x++)
		{
			tempInt.push_back((octoInput[y][x]) - '0');
			tempBool.push_back(false);
            totalOctos++;
		}

		octoGrid.push_back(tempInt);
		flashGrid.push_back(tempBool);
	}

	totalFlashCount = 0;

    simultaneousFlash = false;
}

void OctoField::AddOneEnergyAll()
{
	for (int y = 0; y < octoGrid.size(); y++)
	{
		for (int x = 0; x < octoGrid[y].size(); x++)
		{
			octoGrid[y][x]++;
		}
	}
}

void OctoField::AddOneEnergySurrounding(int yPoint, int xPoint)
{
    // Check Up-Left
    if (yPoint - 1 >= 0 && xPoint - 1 >= 0)
    {
        octoGrid[yPoint - 1][xPoint - 1]++;

        if (octoGrid[yPoint - 1][xPoint - 1] > 9 && !flashGrid[yPoint - 1][xPoint - 1])
        {
            flashQueueY.push_back(yPoint - 1);
            flashQueueX.push_back(xPoint - 1);
        }
    }

    // Check Up
    if (yPoint - 1 >= 0)
    {
        octoGrid[yPoint - 1][xPoint]++;

        if (octoGrid[yPoint - 1][xPoint] > 9 && !flashGrid[yPoint - 1][xPoint])
        {
            flashQueueY.push_back(yPoint - 1);
            flashQueueX.push_back(xPoint);
        }
    }

    // Check Up-Right
    if (yPoint - 1 >= 0 && xPoint + 1 < octoGrid[yPoint].size())
    {
        octoGrid[yPoint - 1][xPoint + 1]++;

        if (octoGrid[yPoint - 1][xPoint + 1] > 9 && !flashGrid[yPoint - 1][xPoint + 1])
        {
            flashQueueY.push_back(yPoint - 1);
            flashQueueX.push_back(xPoint + 1);
        }
    }

    // Check Left
    if (xPoint - 1 >= 0)
    {
        octoGrid[yPoint][xPoint - 1]++;

        if (octoGrid[yPoint][xPoint - 1] > 9 && !flashGrid[yPoint][xPoint - 1])
        {
            flashQueueY.push_back(yPoint);
            flashQueueX.push_back(xPoint - 1);
        }
    }

    // Check Right
    if (xPoint + 1 < octoGrid[yPoint].size())
    {
        octoGrid[yPoint][xPoint + 1]++;

        if (octoGrid[yPoint][xPoint + 1] > 9 && !flashGrid[yPoint][xPoint + 1])
        {
            flashQueueY.push_back(yPoint);
            flashQueueX.push_back(xPoint + 1);
        }
    }

    // Check Down-Left
    if (yPoint + 1 < octoGrid.size() && xPoint - 1 >= 0)
    {
        octoGrid[yPoint + 1][xPoint - 1]++;

        if (octoGrid[yPoint + 1][xPoint - 1] > 9 && !flashGrid[yPoint + 1][xPoint - 1])
        {
            flashQueueY.push_back(yPoint + 1);
            flashQueueX.push_back(xPoint - 1);
        }
    }

    // Check Down
    if (yPoint + 1 < octoGrid.size())
    {
        octoGrid[yPoint + 1][xPoint]++;

        if (octoGrid[yPoint + 1][xPoint] > 9 && !flashGrid[yPoint + 1][xPoint])
        {
            flashQueueY.push_back(yPoint + 1);
            flashQueueX.push_back(xPoint);
        }
    }

    // Check Down-Right
    if (yPoint + 1 < octoGrid.size() && xPoint + 1 < octoGrid[yPoint].size())
    {
        octoGrid[yPoint + 1][xPoint + 1]++;

        if (octoGrid[yPoint + 1][xPoint + 1] > 9 && !flashGrid[yPoint + 1][xPoint + 1])
        {
            flashQueueY.push_back(yPoint + 1);
            flashQueueX.push_back(xPoint + 1);
        }
    }    
}

void OctoField::LoadFlashQueue()
{
	for (int y = 0; y < octoGrid.size(); y++)
	{
		for (int x = 0; x < octoGrid[y].size(); x++)
		{
			if (octoGrid[y][x] > 9 && !flashGrid[y][x])
			{
				flashQueueY.push_back(y);
				flashQueueX.push_back(x);
			}
		}
	}
}

void OctoField::Flash()
{
	while (!flashQueueY.empty())
	{
        if (!flashGrid[flashQueueY[0]][flashQueueX[0]])
        {
            flashGrid[flashQueueY[0]][flashQueueX[0]] = true;
            AddOneEnergySurrounding(flashQueueY[0], flashQueueX[0]);
        }

		flashQueueY.erase(flashQueueY.begin() + 0);
		flashQueueX.erase(flashQueueX.begin() + 0);
	}
}

void OctoField::CountFlashes()
{
    int stepFlashCount = 0;

    for (int y = 0; y < flashGrid.size(); y++)
    {
        for (int x = 0; x < flashGrid[y].size(); x++)
        {
            if (flashGrid[y][x])
            {
                totalFlashCount++;
                stepFlashCount++;
            }
        }
    }

    if (stepFlashCount == totalOctos)
        simultaneousFlash = true;
}

void OctoField::ResetFlashedOctos()
{
    for (int y = 0; y < octoGrid.size(); y++)
    {
        for (int x = 0; x < octoGrid[y].size(); x++)
        {
            if (octoGrid[y][x] > 9)
            {
                octoGrid[y][x] = 0;
                flashGrid[y][x] = false;
            }
        }
    }
}

void OctoField::Step()
{
    stepCount++;
    AddOneEnergyAll();
    LoadFlashQueue();
    Flash();
    CountFlashes();
    ResetFlashedOctos();
}

int OctoField::GetTotalFlashCount()
{
	return totalFlashCount;
}

bool OctoField::GetSimultaneousFlash()
{
    return simultaneousFlash;
}

int OctoField::GetStepCount()
{
    return stepCount;
}
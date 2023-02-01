#pragma once
#include <vector>
#include <string>
#include <iostream>

class OctoField 
{
private:
	std::vector<std::vector<int>> octoGrid;
	std::vector<std::vector<bool>> flashGrid;
	std::vector<int> flashQueueY;
	std::vector<int> flashQueueX;
	int totalFlashCount;
	int stepCount;
	int totalOctos;
	bool simultaneousFlash;

	void AddOneEnergyAll();
	void AddOneEnergySurrounding(int yPoint, int xPoint);
	void LoadFlashQueue();
	void Flash();
	void CountFlashes();
	void ResetFlashedOctos();

public:
	OctoField(std::vector<std::string> octoInput);
	void Step();
	int GetTotalFlashCount();
	bool GetSimultaneousFlash();
	int GetStepCount();
};
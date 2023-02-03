#pragma once
#include <string>
#include <vector>
#include <algorithm>

class CaveNode
{
private:
	std::string caveName;
	//enum CAVETYPE { BIG, SMALL, END };
	//CAVETYPE caveType;
	std::vector<std::string> connectedCaves; // Possibly should be a vector of CaveNode?

public:
	CaveNode(std::string name);
	std::string GetCaveName() const;
	//CAVETYPE GetCaveType() const;
	std::vector<std::string> GetConnectedCaves() const;
	void AddConnectedCave(std::string newCaveName);
};
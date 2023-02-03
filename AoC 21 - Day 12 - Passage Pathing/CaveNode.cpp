#include "CaveNode.h"

CaveNode::CaveNode(std::string name)
{
	caveName = name;

	/*if (isupper(name[0]))
		caveType = BIG;
	else if (name == "end")
		caveType = END;
	else
		caveType = SMALL;*/
}

std::string CaveNode::GetCaveName() const
{
	return caveName;
}

//CaveNode::CAVETYPE CaveNode::GetCaveType() const
//{
//	return caveType;
//}

std::vector<std::string> CaveNode::GetConnectedCaves() const
{
	return connectedCaves;
}

void CaveNode::AddConnectedCave(std::string newCaveConnection)
{
	if (std::find(connectedCaves.begin(), connectedCaves.end(), newCaveConnection) != connectedCaves.end())
		return;
	else
	{
		if (newCaveConnection != caveName)
			connectedCaves.push_back(newCaveConnection);
	}
}

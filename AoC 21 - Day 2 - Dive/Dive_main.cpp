#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

int main()
{
	enum Direction
	{
		FORWARD,
		UP,
		DOWN
	};

	std::ifstream file("CommandInput.txt");

	std::string str;
	std::vector<std::string> commandLines;
	
	while (std::getline(file, str))
	{
		commandLines.push_back(str);
	}

	// Part 1

	int horizontalPosition = 0;
	int depthPosition = 0;
	std::vector<std::string> command;
	Direction direction;
	int steps;

	for (int i = 0; i < commandLines.size(); i++)
	{
		std::stringstream s_stream(commandLines[i]);

		while (s_stream.good())
		{
			std::string substr;
			std::getline(s_stream, substr, ' ');
			command.push_back(substr);
		}

		if (command[0] == "forward")
			direction = Direction::FORWARD;
		else if (command[0] == "up")
			direction = Direction::UP;
		else if (command[0] == "down")
			direction = Direction::DOWN;

		steps = stoi(command[1]);

		command.clear();
		
		switch (direction)
		{
		case FORWARD:
			horizontalPosition += steps;
			break;
		case UP:
			depthPosition -= steps;
			break;
		case DOWN:
			depthPosition += steps;
			break;
		}
	}

	std::cout << (horizontalPosition * depthPosition) << std::endl << std::endl;

	// Part 2

	int horizontal2 = 0;
	int depth2 = 0;
	int aim = 0;
	int units;

	for (int i = 0; i < commandLines.size(); i++)
	{
		std::stringstream s_stream(commandLines[i]);

		while (s_stream.good())
		{
			std::string substr;
			std::getline(s_stream, substr, ' ');
			command.push_back(substr);
		}

		if (command[0] == "forward")
			direction = Direction::FORWARD;
		else if (command[0] == "up")
			direction = Direction::UP;
		else if (command[0] == "down")
			direction = Direction::DOWN;

		units = stoi(command[1]);

		command.clear();

		switch (direction)
		{
		case FORWARD:
			horizontal2 += units;
			depth2 += (aim * units);
			break;
		case UP:
			aim -= units;
			break;
		case DOWN:
			aim += units;
			break;
		}
	}

	std::cout << (horizontal2 * depth2) << std::endl << std::endl;
}
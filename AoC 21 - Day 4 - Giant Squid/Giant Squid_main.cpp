#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "BingoBoard.h"

int main()
{
    std::ifstream file("BingoInput.txt");
    std::string str;
    std::vector<std::string> bingoLines;

    while (std::getline(file, str))
    {
        bingoLines.push_back(str);
    }

    // Part 1

    std::vector<BingoBoard> allBoards;
    int boardCount = 0;

    for (int i = 2; i < bingoLines.size(); i += 6)
    {
        allBoards.push_back(BingoBoard());
               
        std::vector<std::string> cardRow;
        int cardNumbers[5];

        for (int row = 0; row < 5; row++)
        {
            std::stringstream s_stream(bingoLines[i + row]);

            while (s_stream.good())
            {
                std::string substr;
                std::getline(s_stream, substr, ' ');
                if (substr != "")
                    cardRow.push_back(substr);
            }

            for (int x = 0; x < 5; x++)
            {
                cardNumbers[x] = stoi(cardRow[x]);
            }

            allBoards[boardCount].FillBoard(row, cardNumbers);

            cardRow.clear();
        }

        boardCount++;
    }

    std::vector<int> numbersCalled;

    {
        std::stringstream s_stream(bingoLines[0]);

        while (s_stream.good())
        {
            std::string substr;
            std::getline(s_stream, substr, ',');
            numbersCalled.push_back(stoi(substr));
        }
    }

    int winningScore = 0;
    int part2StartIndex = 0;
    int part2StartBoard = 0;

    for (int i = 0; i < numbersCalled.size(); i++)
    {
        for (int b = 0; b < allBoards.size(); b++)
        {
            allBoards[b].MarkNumber(numbersCalled[i]);
        }

        if (i < 4)
            continue;

        for (int b = 0; b < allBoards.size(); b++)
        {
            if (allBoards[b].CheckForBingo())
            {
                winningScore = allBoards[b].BoardScore(numbersCalled[i]);
                part2StartIndex = i + 1;
                part2StartBoard = b;
                break;
            }
        }

        if (winningScore > 0)
            break;
    }

    std::cout << winningScore << std::endl << std::endl;

    // Part 2

    int lastWinningScore = 0;

    for (int b = part2StartBoard; b < allBoards.size(); b++)
    {
        if (allBoards[b].CheckForBingo())
        {
            lastWinningScore = allBoards[b].BoardScore(numbersCalled[part2StartIndex - 1]);
        }
    }

    for (int i = part2StartIndex; i < numbersCalled.size(); i++)
    {
        for (int b = 0; b < allBoards.size(); b++)
        {
            allBoards[b].MarkNumber(numbersCalled[i]);
        }

        for (int b = 0; b < allBoards.size(); b++)
        {
            if (allBoards[b].CheckForBingo() && !allBoards[b].GetHasWon())
            {
                lastWinningScore = allBoards[b].BoardScore(numbersCalled[i]);
            }
        }
    }

    std::cout << lastWinningScore << std::endl << std::endl;
}

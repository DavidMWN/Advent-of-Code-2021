#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

bool checkOpening(char ch)
{
    switch (ch)
    {
    case '(':
        return true;
    case '[':
        return true;
    case '{':
        return true;
    case '<':
        return true;
    default:
        return false;
    }
}

bool checkClosing(char opening, char closing)
{
    switch (opening)
    {
    case '(':
        if (closing == ')')
            return true;
        else
            return false;
    case '[':
        if (closing == ']')
            return true;
        else
            return false;
    case '{':
        if (closing == '}')
            return true;
        else
            return false;
    case '<':
        if (closing == '>')
            return true;
        else
            return false;
    default:
        return false;
    }
}

int illegalCharScore(char illegalChar)
{
    switch (illegalChar)
    {
    case ')':
        return 3;
    case ']':
        return 57;
    case '}':
        return 1197;
    case '>':
        return 25137;
    default:
        return -1;
    }
}

char getClosing(char openingChar)
{
    switch (openingChar)
    {
    case '(':
        return ')';
    case '[':
        return ']';
    case '{':
        return '}';
    case '<':
        return '>';
    default:
        return '*';
    }
}

int64_t addedCharScore(std::string addedChars)
{
    int64_t score = 0;

    for (int c = 0; c < addedChars.size(); c++)
    {
        score *= 5;

        switch (addedChars[c])
        {
        case ')':
            score += 1;
            break;
        case ']':
            score += 2;
            break;
        case '}':
            score += 3;
            break;
        case '>':
            score += 4;
            break;
        default:
            return -1;
        }
    }

    return score;
}

int main()
{
    std::ifstream file("SyntaxInput.txt");
    std::string syntaxLines;

    std::vector<std::string> syntaxInput;

    while (std::getline(file, syntaxLines))
    {
        syntaxInput.push_back(syntaxLines);
    }

    // Part 1

    std::vector<char> openingQueue;
    std::vector<char> illegalChars;

    for (int i = 0; i < syntaxInput.size(); i++)
    {
        if (!openingQueue.empty())
            openingQueue.clear();

        for (int c = 0; c < syntaxInput[i].size(); c++)
        {
            if (checkOpening(syntaxInput[i][c]))
            {
                openingQueue.push_back(syntaxInput[i][c]);
            }
            else if (checkClosing(openingQueue[openingQueue.size() - 1], syntaxInput[i][c]))
            {
                openingQueue.pop_back();
            }
            else
            {
                illegalChars.push_back(syntaxInput[i][c]);
                break;
            }
        }
    }

    int syntaxErrorScore = 0;

    for (int i = 0; i < illegalChars.size(); i++)
    {
        syntaxErrorScore += illegalCharScore(illegalChars[i]);
    }

    std::cout << syntaxErrorScore << std::endl << std::endl;

    // Part 2

    std::vector<std::string> addedChars;

    for (int i = 0; i < syntaxInput.size(); i++)
    {
        if (!openingQueue.empty())
            openingQueue.clear();

        for (int c = 0; c < syntaxInput[i].size(); c++)
        {
            if (checkOpening(syntaxInput[i][c]))
            {
                openingQueue.push_back(syntaxInput[i][c]);
            }
            else if (checkClosing(openingQueue[openingQueue.size() - 1], syntaxInput[i][c]))
            {
                openingQueue.pop_back();
            }
            else
            {           
                openingQueue.clear();
                break;
            }
        }

        if (!openingQueue.empty())
        {
            std::string tempCharHolder;

            while (!openingQueue.empty())
            {
                tempCharHolder += getClosing(openingQueue[openingQueue.size() - 1]);
                openingQueue.pop_back();
            }

            addedChars.push_back(tempCharHolder);
        }
    }

    std::vector<int64_t> autoCompleteScores;

    for (int i = 0; i < addedChars.size(); i++)
    {
        autoCompleteScores.push_back(addedCharScore(addedChars[i]));
    }

    std::sort(autoCompleteScores.begin(), autoCompleteScores.end());

    std::cout << autoCompleteScores[autoCompleteScores.size() / 2] << std::endl << std::endl;
}
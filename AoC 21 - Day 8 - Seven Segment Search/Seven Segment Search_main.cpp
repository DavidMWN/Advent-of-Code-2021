#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>

int main()
{
    std::ifstream file("DigitInput.txt");
    std::string str;
    std::vector<std::string> digitLines;

    while (std::getline(file, str))
    {
        digitLines.push_back(str);
    }

    // Part 1

    int uniqueSegmentCount = 0;

    for (int i = 0; i < digitLines.size(); i++)
    {
        std::vector<std::string> inputSections;

        std::stringstream s_stream(digitLines[i]);

        while (s_stream.good())
        {
            std::string substr;
            std::getline(s_stream, substr, '|');
            inputSections.push_back(substr);
        }

        std::vector<std::string> outputValues;

        std::stringstream s_stream2(inputSections[1]);

        while (s_stream2.good())
        {
            std::string substr;
            std::getline(s_stream2, substr, ' ');
            if (substr != "")
                outputValues.push_back(substr);
        }

        for (int s = 0; s < outputValues.size(); s++)
        {
            if (outputValues[s].size() == 2)
            {
                uniqueSegmentCount++;
                continue;
            }

            if (outputValues[s].size() == 4)
            {
                uniqueSegmentCount++;
                continue;
            }

            if (outputValues[s].size() == 3)
            {
                uniqueSegmentCount++;
                continue;
            }

            if (outputValues[s].size() == 7)
            {
                uniqueSegmentCount++;
                continue;
            }
        }
    }

    std::cout << uniqueSegmentCount << std::endl << std::endl;

    // Part 2       

    int outputSum = 0;

    for (int i = 0; i < digitLines.size(); i++)
    {
        std::array<std::string, 10> digitCodes;

        std::vector<std::string> inputSections;

        std::stringstream s_stream(digitLines[i]);

        while (s_stream.good())
        {
            std::string substr;
            std::getline(s_stream, substr, '|');
            inputSections.push_back(substr);
        }

        std::vector<std::string> inputValues;

        std::stringstream s_stream2(inputSections[0]);

        while (s_stream2.good())
        {
            std::string substr;
            std::getline(s_stream2, substr, ' ');
            if (substr != "")
                inputValues.push_back(substr);
        }

        std::string fourdiff;

        for (int s = 0; s < inputValues.size(); s++)
        {
            if (inputValues[s].size() == 2)
            {
                digitCodes[1] = inputValues[s];
                continue;
            }

            if (inputValues[s].size() == 4)
            {
                digitCodes[4] = inputValues[s];
                continue;
            }

            if (inputValues[s].size() == 3)
            {
                digitCodes[7] = inputValues[s];
                continue;
            }

            if (inputValues[s].size() == 7)
            {
                digitCodes[8] = inputValues[s];
                continue;
            }
        }

        for (int c = 0; c < digitCodes[4].size(); c++)
        {
            if (std::find(digitCodes[1].begin(), digitCodes[1].end(), digitCodes[4][c]) != digitCodes[1].end())
                continue;
            else
                fourdiff += digitCodes[4][c];
        }

        for (int s = 0; s < inputValues.size(); s++)
        {
            if (inputValues[s].size() == 5)
            {
                if (std::find(inputValues[s].begin(), inputValues[s].end(), digitCodes[1][0]) != inputValues[s].end()
                    && std::find(inputValues[s].begin(), inputValues[s].end(), digitCodes[1][1]) != inputValues[s].end())
                {
                    digitCodes[3] = inputValues[s];
                    continue;
                }

                if (std::find(inputValues[s].begin(), inputValues[s].end(), fourdiff[0]) != inputValues[s].end()
                    && std::find(inputValues[s].begin(), inputValues[s].end(), fourdiff[1]) != inputValues[s].end())
                {
                    digitCodes[5] = inputValues[s];
                    continue;
                }

                digitCodes[2] = inputValues[s];
                continue;
            }

            if (inputValues[s].size() == 6)
            {
                if (std::find(inputValues[s].begin(), inputValues[s].end(), digitCodes[4][0]) != inputValues[s].end()
                    && std::find(inputValues[s].begin(), inputValues[s].end(), digitCodes[4][1]) != inputValues[s].end()
                    && std::find(inputValues[s].begin(), inputValues[s].end(), digitCodes[4][2]) != inputValues[s].end()
                    && std::find(inputValues[s].begin(), inputValues[s].end(), digitCodes[4][3]) != inputValues[s].end())
                {
                    digitCodes[9] = inputValues[s];
                    continue;
                }

                if (std::find(inputValues[s].begin(), inputValues[s].end(), fourdiff[0]) != inputValues[s].end()
                    && std::find(inputValues[s].begin(), inputValues[s].end(), fourdiff[1]) != inputValues[s].end())
                {
                    digitCodes[6] = inputValues[s];
                    continue;
                }

                digitCodes[0] = inputValues[s];
            }
        }               

        std::vector<std::string> outputValues;
        std::stringstream s_stream3(inputSections[1]);

        while (s_stream3.good())
        {
            std::string substr;
            std::getline(s_stream3, substr, ' ');
            if (substr != "")
                outputValues.push_back(substr);
        }

        for (int x = 0; x < digitCodes.size(); x++)
            std::sort(digitCodes[x].begin(), digitCodes[x].end());

        std::string digitOutput;

        for (int o = 0; o < outputValues.size(); o++)
        {
            std::sort(outputValues[o].begin(), outputValues[o].end());

            for (int d = 0; d < digitCodes.size(); d++)
            {
                if (outputValues[o] == digitCodes[d])
                {
                    char temp = '0' + d;
                    digitOutput += temp;
                }
            }
        }

        outputSum += stoi(digitOutput);
    }

    std::cout << outputSum << std::endl << std::endl;
}
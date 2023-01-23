#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{
    std::ifstream file("DiagnosticInput.txt");

    std::string str;
    std::vector<std::string> diagnosticLines;

    while (std::getline(file, str))
        diagnosticLines.push_back(str);

    // Part 1

    std::vector<int> count0;
    std::vector<int> count1;

    for (int i = 0; i < diagnosticLines[0].size(); i++)
    {
        count0.push_back(0);
        count1.push_back(0);
    }

    for (int i = 0; i < diagnosticLines.size(); i++)
    {
        for (int x = 0; x < diagnosticLines[i].size(); x++)
        {
            if (diagnosticLines[i][x] == '0')
                count0[x]++;
            else
                count1[x]++;
        }
    }

    std::string gammaRateBinary = "";
    std::string epsilonRateBinary = "";

    for (int i = 0; i < count0.size(); i++)
    {
        if (count0[i] > count1[i])
        {
            gammaRateBinary += "0";
            epsilonRateBinary += "1";
        }
        else
        {
            gammaRateBinary += "1";
            epsilonRateBinary += "0";
        }
    }

    int gammaRateDecimal = stoi(gammaRateBinary, 0, 2);
    int epsilonRateDecimal = stoi(epsilonRateBinary, 0, 2);

    int powerConsumption = gammaRateDecimal * epsilonRateDecimal;

    std::cout << powerConsumption << std::endl << std::endl;

    // Part 2

    int count0part2;
    int count1part2;

    std::vector<std::string> oxygenGenCandidates;
    std::vector<std::string> co2scrubCandidates;

    for (int i = 0; i < diagnosticLines.size(); i++)
    {
        oxygenGenCandidates.push_back(diagnosticLines[i]);
        co2scrubCandidates.push_back(diagnosticLines[i]);
    }

    for (int i = 0; i < oxygenGenCandidates[0].size(); i++)
    {
        count0part2 = 0;
        count1part2 = 0;

        for (int c = 0; c < oxygenGenCandidates.size(); c++)
        {
            if (oxygenGenCandidates[c][i] == '0')
                count0part2++;
            else
                count1part2++;
        }

        for (int x = oxygenGenCandidates.size() - 1; x > -1; x--)
        {
            if (oxygenGenCandidates[x][i] == '0')
            {
                if (count0part2 <= count1part2)
                    oxygenGenCandidates.erase(oxygenGenCandidates.begin() + x);
            }
            else if (oxygenGenCandidates[x][i] == '1')
            {
                if (count1part2 < count0part2)
                    oxygenGenCandidates.erase(oxygenGenCandidates.begin() + x);
            }
        }

        if (oxygenGenCandidates.size() == 1)
            break;
    }

    for (int i = 0; i < co2scrubCandidates[0].size(); i++)
    {
        count0part2 = 0;
        count1part2 = 0;

        for (int c = 0; c < co2scrubCandidates.size(); c++)
        {
            if (co2scrubCandidates[c][i] == '0')
                count0part2++;
            else
                count1part2++;
        }

        for (int x = co2scrubCandidates.size() - 1; x > -1; x--)
        {
            if (co2scrubCandidates[x][i] == '0')
            {
                if (count0part2 > count1part2)
                    co2scrubCandidates.erase(co2scrubCandidates.begin() + x);
            }
            else if (co2scrubCandidates[x][i] == '1')
            {
                if (count1part2 >= count0part2)
                    co2scrubCandidates.erase(co2scrubCandidates.begin() + x);
            }
        }

        if (co2scrubCandidates.size() == 1)
            break;
    }

    int oxygenGenRating = stoi(oxygenGenCandidates[0], 0, 2);
    int co2scrubRating = stoi(co2scrubCandidates[0], 0, 2);

    int lifeSupportRating = oxygenGenRating * co2scrubRating;

    std::cout << lifeSupportRating << std::endl << std::endl;
}
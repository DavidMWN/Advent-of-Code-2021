#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    ifstream file("SweepInput.txt");

    if (file.fail())
    {
        cout << "Error: count not open file." << endl;
        return 0;
    }

    string str;
    vector<int> sweepLines;

    while (getline(file, str))
    {
        sweepLines.push_back(stoi(str));
    }

    // Part 1

    int increases = 0;

    for (int i = 1; i < sweepLines.size(); i++)
    {
        if (sweepLines[i] > sweepLines[i - 1])
            increases++;
    }

    cout << increases << endl << endl;

    // Part 2

    int windowSumA;
    int windowSumB;
    int windowSumIncreases = 0;    

    for (int i = 2; i < sweepLines.size() - 1; i++)
    {
        windowSumA = sweepLines[i] + sweepLines[i - 1] + sweepLines[i - 2];
        windowSumB = sweepLines[i + 1] + sweepLines[i] + sweepLines[i - 1];

        if (windowSumB > windowSumA)
            windowSumIncreases++;
    }

    cout << windowSumIncreases << endl << endl;
}
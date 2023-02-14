#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int64_t> InsertionStep(std::vector<std::string> pairs, std::vector<char> insert, std::vector<int64_t> counts)
{
    std::vector<int64_t> tempCounts;

    for (int i = 0; i < counts.size(); i++)
        tempCounts.push_back(0);

    for (int c = 0; c < counts.size(); c++)
    {
        if (counts[c] > 0)
        {
            std::string newPair1 = "";
            std::string newPair2 = "";

            newPair1.push_back(pairs[c][0]);
            newPair1.push_back(insert[c]);

            newPair2.push_back(insert[c]);
            newPair2.push_back(pairs[c][1]);

            int pairIndex1 = find(pairs.begin(), pairs.end(), newPair1) - pairs.begin();
            int pairIndex2 = find(pairs.begin(), pairs.end(), newPair2) - pairs.begin();

            tempCounts[pairIndex1] += counts[c];
            tempCounts[pairIndex2] += counts[c];
        }
    }

    return tempCounts;
}

std::vector<int64_t> CountElements(std::vector<std::string> pairs, std::vector<char> elements, std::vector<int64_t> pairCounts, std::vector<int64_t> elementCounts)
{
    for (int p = 0; p < pairs.size(); p++)
    {
        if (pairCounts[p] > 0)
        {            
            int elementIndex = find(elements.begin(), elements.end(), pairs[p][0]) - elements.begin();

            elementCounts[elementIndex] += pairCounts[p];
        }
    }

    return elementCounts;
}

int main()
{
    std::ifstream file("PolymerInput.txt");
    std::string str;
    std::vector<std::string> inputLines;

    while (std::getline(file, str))
    {
        inputLines.push_back(str);
    }

    // Extract template and pair insertion rules

    std::string polymerTemplate = inputLines[0];

    std::vector<std::string> pairList;
    std::vector<char> insertList;

    for (int i = 2; i < inputLines.size(); i++)
    {
        std::vector<std::string> temp;
        std::stringstream s_stream(inputLines[i]);

        while (s_stream.good())
        {
            std::string substr;
            std::getline(s_stream, substr, ' ');
            temp.push_back(substr);
        }

        pairList.push_back(temp[0]);
        insertList.push_back(temp[2][0]);
    }
    
    // Initialize pair count

    std::vector<int64_t> pairCount;

    for (int p = 0; p < pairList.size(); p++)
        pairCount.push_back(0);

    for (int e = 0; e < polymerTemplate.size() - 1; e++)
    {
        std::string temp = "";            
        temp.push_back(polymerTemplate[e]);
        temp.push_back(polymerTemplate[e + 1]);

        int pairIndex = find(pairList.begin(), pairList.end(), temp) - pairList.begin();

        pairCount[pairIndex]++;
    }

    // Initilize list of all elements used and element count

    std::vector<char> elementList;

    for (int p = 0; p < pairList.size(); p++)
    {
        for (int e = 0; e < pairList[p].size(); e++)
        {
            if (find(elementList.begin(), elementList.end(), pairList[p][e]) != elementList.end())
                continue;
            else
                elementList.push_back(pairList[p][e]);
        }
    }

    std::vector<int64_t> elementCount;

    for (int e = 0; e < elementList.size(); e++)
        elementCount.push_back(0);

    // Part 1 - 10 steps

    for (int s = 1; s <= 10; s++)
    {
        pairCount = InsertionStep(pairList, insertList, pairCount);
    }    
    
    elementCount = CountElements(pairList, elementList, pairCount, elementCount);

    // Count last element in the sequence
    
    int lastElementIndex = find(elementList.begin(), elementList.end(), polymerTemplate[polymerTemplate.size() - 1]) - elementList.begin();
    elementCount[lastElementIndex]++;

    int64_t maxElementCount = *max_element(elementCount.begin(), elementCount.end());
    int64_t minElementCount = *min_element(elementCount.begin(), elementCount.end());

    int64_t result = maxElementCount - minElementCount;

    std::cout << result << std::endl << std::endl;

    /***************************************/

    // Reset pair count

    for (int i = 0; i < pairCount.size(); i++)
        pairCount[i] = 0;

    for (int e = 0; e < polymerTemplate.size() - 1; e++)
    {
        std::string temp = "";
        temp.push_back(polymerTemplate[e]);
        temp.push_back(polymerTemplate[e + 1]);

        int pairIndex = find(pairList.begin(), pairList.end(), temp) - pairList.begin();

        pairCount[pairIndex]++;
    }

    // Reset element count

    for (int i = 0; i < elementCount.size(); i++)
        elementCount[i] = 0;

    // Part 2 - 40 steps

    for (int s = 1; s <= 40; s++)
        pairCount = InsertionStep(pairList, insertList, pairCount);    

    elementCount = CountElements(pairList, elementList, pairCount, elementCount);
    elementCount[lastElementIndex]++;

    maxElementCount = *max_element(elementCount.begin(), elementCount.end());
    minElementCount = *min_element(elementCount.begin(), elementCount.end());

    result = maxElementCount - minElementCount;

    std::cout << result << std::endl << std::endl;
}
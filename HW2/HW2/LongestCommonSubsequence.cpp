#include <iostream>
#include <vector>
#include <algorithm>


void ReadSequence(std::vector<int> * sequence)
{
    int sequenceLength;
    std::cin >> sequenceLength;
    for (int i = 0; i < sequenceLength; ++i)
    {
        int number;
        std::cin >> number;
        sequence->push_back(number);
    }
}


int Solve(std::vector<int> & firstSequence, std::vector<int> & secondSequence)
{
    int firstLength = static_cast<int>(firstSequence.size());
    int secondLength = static_cast<int>(secondSequence.size());

    std::vector<std::vector<int>> maxSubsequences;
    for (int i = 0; i < firstLength; ++i)
    {
        maxSubsequences.push_back(std::vector<int>());
        maxSubsequences[i].push_back(firstSequence[i] == secondSequence[0] ? 1 : 0);
        if (i > 0)
            maxSubsequences[i][0] = std::max(maxSubsequences[i][0], maxSubsequences[i - 1][0]);
    }

    for (int i = 1; i < secondLength; ++i)
    {
        maxSubsequences[0].push_back(secondSequence[i] == firstSequence[0] ? 1 : 0);
        maxSubsequences[0][i] = std::max(maxSubsequences[0][i], maxSubsequences[0][i - 1]);
    }

    for (int i = 1; i < firstLength; ++i)
    {
        for (int j = 1; j < secondLength; ++j)
        {
            maxSubsequences[i].push_back(
                std::max(maxSubsequences[i][j - 1], maxSubsequences[i - 1][j]));
            if (firstSequence[i] == secondSequence[j] && 
                maxSubsequences[i][j] <= maxSubsequences[i - 1][j - 1])
            {
                maxSubsequences[i][j] = maxSubsequences[i - 1][j - 1] + 1;
            }
        }
    }

    int maxValue = 0;
    for (int i = 0; i < firstLength; ++i)
    {
        for (int j = 0; j < secondLength; ++j)
        {
            maxValue = std::max(maxValue, maxSubsequences[i][j]);
        }
    }

    return maxValue;
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> firstSequence;
    std::vector<int> secondSequence;

    ReadSequence(&firstSequence);
    ReadSequence(&secondSequence);

    int answer = Solve(firstSequence, secondSequence);
    std::cout << answer;
    return 0;
}

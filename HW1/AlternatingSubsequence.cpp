#include <iostream>
#include <algorithm>
#include <vector>


void Input(std::vector<int> * numbers)
{
    int numbersCount;
    std::cin >> numbersCount;
    for (int i = 0; i < numbersCount; ++i)
    {
        int number;
        std::cin >> number;
        numbers->push_back(number);
    }
}


void CountDP(std::vector<int> & numbers,
    std::vector<int> * maxIncreasing,
    std::vector<int> * maxDecreasing,
    std::vector<int> * previousIncreasing,
    std::vector<int> * previousDecreasing)
{
    int numbersCount = static_cast<int>(numbers.size());
    for (int currentPosition = 0; currentPosition < numbersCount; ++currentPosition)
    {
        for (int previousPosition = 0; previousPosition < currentPosition; ++previousPosition)
        {
            if (numbers[currentPosition] > numbers[previousPosition] &&
                (*maxIncreasing)[currentPosition] <= (*maxDecreasing)[previousPosition])
            {
                (*maxIncreasing)[currentPosition] = (*maxDecreasing)[previousPosition] + 1;
                (*previousIncreasing)[currentPosition] = previousPosition;
            }
            if (numbers[currentPosition] < numbers[previousPosition] &&
                (*maxDecreasing)[currentPosition] <= (*maxIncreasing)[previousPosition])
            {
                (*maxDecreasing)[currentPosition] = (*maxIncreasing)[previousPosition] + 1;
                (*previousDecreasing)[currentPosition] = previousPosition;
            }
        }
    }
}


bool less(std::vector<int> & first, std::vector<int> & second)
{
    for (int i = 0; i < static_cast<int>(first.size()); ++i)
    {
        if (first[i] != second[i])
            return first[i] < second[i];
    }
    return false;
}


void getSubsequence(
    std::vector<int> & previousIncreasing,
    std::vector<int> & previousDecreasing,
    std::vector<int> * subsequence, int currentPosition, bool increases)
{
    while (currentPosition != -1)
    {
        subsequence->push_back(currentPosition);
        if (increases)
        {
            currentPosition = previousIncreasing[currentPosition];
        }
        else
        {
            currentPosition = previousDecreasing[currentPosition];
        }
        increases = !increases;
    }
    std::reverse(subsequence->begin(), subsequence->end());
}


void Solve(std::vector<int> & numbers, std::vector<int> * solution)
{
    int numbersCount = static_cast<int>(numbers.size());
    std::vector<int> maxIncreasing(numbersCount, 1);
    std::vector<int> maxDecreasing(numbersCount, 1);
    std::vector<int> previousIncreasing(numbersCount, -1);
    std::vector<int> previousDecreasing(numbersCount, -1);

    CountDP(numbers, &maxIncreasing, &maxDecreasing, &previousIncreasing, &previousDecreasing);

    std::vector<int> longestMinimalSequence;
    std::vector<int> currentSubsequence;

    for (int position = 0; position < numbersCount; ++position)
    {
        for (int j = 0; j < 2; ++j)
        {
            currentSubsequence.clear();
            getSubsequence(previousIncreasing, previousDecreasing, 
                &currentSubsequence, position, j == 0);
            if (currentSubsequence.size() < longestMinimalSequence.size())
                continue;
            if (currentSubsequence.size() > longestMinimalSequence.size() ||
                less(currentSubsequence, longestMinimalSequence))
            {
                std::swap(longestMinimalSequence, currentSubsequence);
            }
        }
    }

    for (int i = 0; i < static_cast<int>(longestMinimalSequence.size()); ++i) {
        solution->push_back(numbers[longestMinimalSequence[i]]);
    }
}


void Output(std::vector<int> & solution)
{
    for (int i = 0; i < static_cast<int>(solution.size()); ++i)
    {
        std::cout << solution[i] << " ";
    }
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> numbers;
    Input(&numbers);

    std::vector<int> solution;
    Solve(numbers, &solution);

    Output(solution);

    return 0;
}

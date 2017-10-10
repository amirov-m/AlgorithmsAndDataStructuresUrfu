#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


void Input(std::vector<long long> * input)
{
    int inputSize;
    std::cin >> inputSize;
    for (int i = 0; i < inputSize; ++i)
    {
        long long number;
        std::cin >> number;
        input->push_back(number);
    }
}

template <typename T>
void merge(
    const std::vector<T> & first,
    const std::vector<T> & second,
    std::vector<T> * result)
{
    unsigned int firstPos = 0;
    unsigned int secondPos = 0;

    while (firstPos != first.size() || secondPos != second.size())
    {
        if (firstPos == first.size())
            result->push_back(second[secondPos++]);
        else if (secondPos == second.size())
            result->push_back(first[firstPos++]);
        else if (first[firstPos] < second[secondPos])
            result->push_back(first[firstPos++]);
        else
            result->push_back(second[secondPos++]);
    }
}

template <typename T>
void merge_sort(std::vector<T> * elements)
{
    if (elements->size() <= 1)
        return;
    if (elements->size() == 2)
    {
        if ((*elements)[0] > (*elements)[1])
        {
            std::swap((*elements)[0], (*elements)[1]);
        }
    }

    int middle = elements->size() / 2;
    std::vector<T> first_part = std::vector<T>(elements->begin(), elements->begin() + middle);
    std::vector<T> second_part = std::vector<T>(elements->begin() + middle, elements->end());
    merge_sort(&first_part);
    merge_sort(&second_part);
    elements->clear();
    merge(first_part, second_part, elements);
}


long long Solve(std::vector<long long> & input, std::vector<int> * positions)
{
    std::vector<std::pair<long long, int>> inputWithPosition;
    for (int i = 0; i < static_cast<int>(input.size()); ++i)
    {
        inputWithPosition.push_back(std::make_pair(input[i], i));
    }
    merge_sort(&inputWithPosition);

    long long maxEffect = inputWithPosition[0].first;
    int maxEffectLeftInclusive = 0;
    int maxEffectRightInclusive = 0;

    int leftPointer = 0;
    int rightPointer = 0;
    long long currentEffect = maxEffect;
    do
    {
        if (input.size() == 1)
            break;
        currentEffect += inputWithPosition[++rightPointer].first;
        while (rightPointer - leftPointer >= 2
            && inputWithPosition[leftPointer].first + inputWithPosition[leftPointer + 1].first <
            inputWithPosition[rightPointer].first)
        {
            currentEffect -= inputWithPosition[leftPointer++].first;
        }

        if (currentEffect > maxEffect)
        {
            maxEffectLeftInclusive = leftPointer;
            maxEffectRightInclusive = rightPointer;
            maxEffect = currentEffect;
        }
    }
    while (rightPointer != static_cast<int>(inputWithPosition.size()) - 1);

    for (int i = maxEffectLeftInclusive; i <= maxEffectRightInclusive; ++i)
    {
        positions->push_back(inputWithPosition[i].second);
    }
    merge_sort(positions);
    return maxEffect;
}


void Output(long long maxEffect, std::vector<int> & solutionPositions) 
{
    std::cout << maxEffect << std::endl;
    for (int i = 0; i < static_cast<int>(solutionPositions.size()); ++i)
    {
        std::cout << solutionPositions[i] + 1 << " ";
    }
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<long long> input;
    std::vector<int> solutionPositions;
    
    Input(&input);
    long long maxEffect = Solve(input, &solutionPositions);
    Output(maxEffect, solutionPositions);
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>


void Input(std::vector<int> * numbers)
{
    int numbersCount;
    std::cin >> numbersCount;
    for (int i = 0; i < numbersCount; ++i)
    {
        int currentNumber;
        std::cin >> currentNumber;
        numbers->push_back(currentNumber);
    }
}


void getExtremumsPositions(std::vector<int> & numbers, std::vector<int> * extremums)
{
    std::vector<std::pair<int, int>> numbersWithouthRepeats;
    for (int i = 0; i < numbers.size(); ++i)
    {
        if (numbersWithouthRepeats.size() == 0 ||
            numbersWithouthRepeats.back().first != numbers[i])
        {
            numbersWithouthRepeats.push_back(std::make_pair(numbers[i], i));
        }
    }

    for (int i = 0; i < static_cast<int>(numbersWithouthRepeats.size()); ++i)
    {
        if (i == 0 || i == numbersWithouthRepeats.size() - 1 ||
            (numbersWithouthRepeats[i - 1].first < numbersWithouthRepeats[i].first &&
                numbersWithouthRepeats[i].first > numbersWithouthRepeats[i + 1].first) ||
            numbersWithouthRepeats[i - 1].first > numbersWithouthRepeats[i].first &&
            numbersWithouthRepeats[i].first < numbersWithouthRepeats[i + 1].first)
        {
            extremums->push_back(numbersWithouthRepeats[i].second);
        }
    }
}


bool middleIsExtremum(int left, int middle, int right)
{
    return left < middle && middle > right || left > middle && middle < right;
}


void Solve(std::vector<int> & numbers, std::vector<int> * answer)
{
    std::vector<int> extremumPositions;
    getExtremumsPositions(numbers, &extremumPositions);

    if (extremumPositions.size() == 1)
    {
        answer->push_back(numbers[extremumPositions[0]]);
        return;
    }

    std::vector<int> subsequencePositions;
    subsequencePositions.push_back(0);

    for (int curExtremum = 1;
        curExtremum < static_cast<int>(extremumPositions.size()) - 1;
        ++curExtremum)
    {
        for (int j = subsequencePositions.back() + 1; j <= extremumPositions[curExtremum]; ++j)
        {
            if (numbers[subsequencePositions.back()] < numbers[j] &&
                numbers[j] > numbers[extremumPositions[curExtremum + 1]] &&
                numbers[extremumPositions[curExtremum]] > numbers[subsequencePositions.back()] ||
                numbers[subsequencePositions.back()] > numbers[j] &&
                numbers[j] < numbers[extremumPositions[curExtremum + 1]] &&
                numbers[extremumPositions[curExtremum]] < numbers[subsequencePositions.back()])
            {
                subsequencePositions.push_back(j);
                break;
            }
        }
    }



    for (int i = extremumPositions[extremumPositions.size() - 2] + 1; i < numbers.size(); ++i)
    {
        if (numbers[i] == numbers[i - 1])
            continue;
        if (subsequencePositions.size() == 1 ||
            middleIsExtremum(numbers[subsequencePositions[subsequencePositions.size() - 2]],
                numbers[subsequencePositions.back()], numbers[i]))
        {
            subsequencePositions.push_back(i);
            break;
        }
    }

    for (int i = 0; i < static_cast<int>(subsequencePositions.size()); ++i)
    {
        answer->push_back(numbers[subsequencePositions[i]]);
    }
}


void Output(std::vector<int> & answer)
{
    for (int i = 0; i < static_cast<int>(answer.size()); ++i)
    {
        std::cout << answer[i] << " ";
    }
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> numbers;
    std::vector<int> answer;

    Input(&numbers);
    Solve(numbers, &answer);
    Output(answer);

}

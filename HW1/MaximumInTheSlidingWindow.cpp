#include <iostream>
#include <vector>
#include <algorithm>


int const MinValue = -1000 * 1000 * 1000 - 17;


class StackWithMax
{
private:
    std::vector<int> numbers;
    std::vector<int> currentMax;

public:
    void push(int number)
    {
        numbers.push_back(number);
        if (numbers.size() == 1)
            currentMax.push_back(number);
        else
            currentMax.push_back(std::max(number, currentMax.back()));
    }

    int getMax() const
    {
        return any() ? currentMax.back() : MinValue;
    }

    int back() const
    {
        return numbers.back();
    }

    int pop()
    {
        int numberToReturn = numbers.back();
        numbers.pop_back();
        currentMax.pop_back();
        return numberToReturn;
    }

    int size() const
    {
        return static_cast<int>(numbers.size());
    }

    bool any() const 
    {
        return size() > 0;
    }
};


class QueueWithMax
{
private:
    StackWithMax firstStack;
    StackWithMax secondStack;

    void moveElementsToSecondStack()
    {
        while (firstStack.any())
        {
            secondStack.push(firstStack.pop());
        }
    }

public:
    void push(int number)
    {
        firstStack.push(number);
    }
    
    int pop()
    {
        if (!secondStack.any())
        {
            moveElementsToSecondStack();
        }
        return secondStack.pop();
    }

    int size()
    {
        return firstStack.size() + secondStack.size();
    }

    int getMax()
    {
        return std::max(firstStack.getMax(), secondStack.getMax());
    }
};


void Input(std::vector<int> * numbers, std::vector<int> * bordersMoves)
{
    int numbersCount;
    std::cin >> numbersCount;
    for (int i = 0; i < numbersCount; ++i)
    {
        int nextNumber;
        std::cin >> nextNumber;
        numbers->push_back(nextNumber);
    }

    int movesCount;
    std::cin >> movesCount;
    for (int i = 0; i < movesCount; ++i)
    {
        char nextMove;
        std::cin >> nextMove;
        bordersMoves->push_back(nextMove == 'L' ? -1 : 1);
    }
}


void Solve(std::vector<int>& numbers, std::vector<int>& bordersMoves, std::vector<int> * maxValues)
{
    QueueWithMax queue;
    int leftBorder = 0, rightBorder = 0;
    queue.push(numbers[rightBorder++]);
    for (int i = 0; i < static_cast<int>(bordersMoves.size()); ++i)
    {
        if (bordersMoves[i] == -1)
        {
            queue.pop();
            leftBorder++;
        }
        else
        {
            queue.push(numbers[rightBorder++]);
        }
        maxValues->push_back(queue.getMax());
    }
}


void Output(std::vector<int> & maxValues)
{
    int maxValuesCount = static_cast<int>(maxValues.size());
    for (int i = 0; i < maxValuesCount; ++i)
    {
        std::cout << maxValues[i] << " ";
    }
}


int mainD()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> numbers;
    std::vector<int> bordersMoves;
    std::vector<int> maxValues;
    
    Input(&numbers, &bordersMoves);
    Solve(numbers, bordersMoves, &maxValues);
    Output(maxValues);
    return 0;
}

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


class pairs_min_heap
{
private:
    std::vector<std::pair<int, int>> heap;

    bool in_range(int position)
    {
        return static_cast<int>(heap.size()) > position;
    }

    int get_position_of_minimum(std::vector<int> positions)
    {
        if (positions.empty())
            return -1;
        int currentPosition = positions[0];
        for (int i = 0; i < static_cast<int>(positions.size()); ++i)
        {
            if (in_range(positions[i]) && heap[currentPosition] > heap[positions[i]]) {
                currentPosition = positions[i];
            }
        }
        if (in_range(currentPosition)) {
            return currentPosition;
        }
        return -1;
    }

public:
    void add(std::pair<int, int> next)
    {
        int currentPosition = static_cast<int>(heap.size());
        heap.push_back(next);

        while (1 > 0)
        {
            int nextPosition = (currentPosition - 1) / 2;
            if (heap[currentPosition] < heap[nextPosition])
            {
                std::swap(heap[nextPosition], heap[currentPosition]);
                currentPosition = nextPosition;
            }
            else
            {
                break;
            }
        }
    }

    std::pair<int, int> popMin()
    {
        std::pair<int, int> toReturn = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        int currentPosition = 0;

        while (1 > 0)
        {
            int left = 2 * currentPosition + 1;
            int right = 2 * currentPosition + 2;
            
            int minPosition = get_position_of_minimum(std::vector<int> {left, right});

            if (minPosition == -1 || heap[currentPosition] <= heap[minPosition])
                break;

            std::swap(heap[currentPosition], heap[minPosition]);
            currentPosition = minPosition;
        }

        return toReturn;
    }

    bool empty()
    {
        return heap.empty();
    }

    int size()
    {
        return static_cast<int>(heap.size());
    }
};


void Input(std::vector<std::vector<int>> * input)
{
    int sequencesCount, sequencesLength;
    std::cin >> sequencesCount >> sequencesLength;

    for (int i = 0; i < sequencesCount; ++i)
    {
        input->push_back(std::vector<int>());
        for (int j = 0; j < sequencesLength; ++j)
        {
            int number;
            std::cin >> number;
            input->operator[](i).push_back(number);
        }
    }
}


void Solve(const std::vector<std::vector<int>> & input, std::vector<int> * solution)
{
    int sequencesCount = input.size();
    int sequencesLength = input[0].size();
    pairs_min_heap heap;

    std::vector<int> sequencesPositions = std::vector<int>(sequencesCount, 1);
    for (int i = 0; i < sequencesCount; ++i)
    {
        heap.add(std::make_pair(input[i][0], i));
    }

    while (!heap.empty())
    {
        std::pair<int, int> nextValue = heap.popMin();
        solution->push_back(nextValue.first);
        int sequence = nextValue.second;
        if (sequencesPositions[sequence] < sequencesLength)
        {
            heap.add(std::make_pair(input[sequence][sequencesPositions[sequence]], sequence));
            sequencesPositions[sequence]++;
        }
    }
}


void Output(std::vector<int> &solution)
{
    for (int i = 0; i < solution.size(); ++i)
    {
        std::cout << solution[i] << " ";
    }
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<int>> input;
    std::vector<int> solution;
    
    Input(&input);
    Solve(input, &solution);
    Output(solution);

    return 0;
}

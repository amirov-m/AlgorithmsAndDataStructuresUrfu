#include <iostream>
#include <vector>
#include <algorithm>


void SwapIfBigger(int & first, int & second)
{
    if (first > second)
        std::swap(first, second);
}


struct Cube
{
    int dimensions[3];

    void read()
    {
        for (int i = 0; i < 3; ++i)
        {
            std::cin >> dimensions[i];
        }
    }

    void sortDimensions()
    {
        SwapIfBigger(dimensions[0], dimensions[1]);
        SwapIfBigger(dimensions[1], dimensions[2]);
        SwapIfBigger(dimensions[0], dimensions[1]);
    }

    bool operator<(Cube & that)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (this->dimensions[i] >= that.dimensions[i])
            {
                return false;
            }
        }
        return true;
    }
};


void Input(std::vector<Cube> * cubes)
{
    int cubesNumber;
    std::cin >> cubesNumber;
    for (int i = 0; i < cubesNumber; ++i)
    {
        cubes->push_back(Cube());
        cubes->operator[](i).read();
    }
}


void sortCubes(std::vector<Cube> * cubes)
{
    int cubesCount = static_cast<int>(cubes->size());
    for (int i = 0; i < cubesCount; ++i)
    {
        for (int j = 0; j < cubesCount - 1; ++j)
        {
            if (cubes->operator[](j + 1) < cubes->operator[](j))
            {
                std::swap(cubes[j], cubes[j + 1]);
            }
        }
    }
}


int Solve(std::vector<Cube> & cubes)
{
    int cubesCount = static_cast<int>(cubes.size());
    sortCubes(&cubes);

    int * maxLens = new int[cubesCount];
    std::fill_n(maxLens, cubesCount, 1);

    for (int i = 0; i < cubesCount; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (cubes[j] < cubes[i] && maxLens[i] <= maxLens[j])
            {
                maxLens[i] = maxLens[j] + 1;
            }
        }
    }

    int maxLen = *std::max_element(maxLens, maxLens + cubesCount);
    delete[] maxLens;
    return maxLen;
}


int mainC()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<Cube> cubes;

    Input(&cubes);
    int maxSequenceLen = Solve(cubes);
    std::cout << maxSequenceLen;
    return 0;
}

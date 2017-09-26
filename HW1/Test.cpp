#include <algorithm>
#include <iostream>
#include <vector>


class Cube
{
    std::vector<int> coordinates;

public:

    Cube(int first, int second, int third)
    {
        coordinates.push_back(first);
        coordinates.push_back(second);
        coordinates.push_back(third);

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                if (coordinates[j] > coordinates[j + 1])
                {
                    std::swap(coordinates[j], coordinates[j + 1]);
                }
            }
        }
    }

    bool operator<(Cube other) {
        return coordinates[0] < other.coordinates[0] &&
            coordinates[1] < other.coordinates[1] &&
            coordinates[2] < other.coordinates[2];
    }
};


void Input(std::vector<Cube> * cubesList)
{
    int quantity;
    std::cin >> quantity;
    for (int i = 0; i < quantity; ++i)
    {
        int first, second, third;
        std::cin >> first >> second >> third;
        Cube cube = Cube(first, second, third);
        cubesList->push_back(cube);
    }
}


int Solve(std::vector<Cube> * cubes)
{
    for (int i = 0; i < cubes->size(); ++i)
    {
        for (int j = 0; j < static_cast<int>(cubes->size()) - 1; ++j)
        {
            if (cubes->operator[](j + 1) < cubes->operator[](j))
            {
                std::swap(cubes->operator[](j + 1), cubes->operator[](j));
            }
        }
    }

    std::vector<int> maxLength;
    for (int le = 0; le < cubes->size(); ++le)
    {
        maxLength.push_back(1);
    }
    for (int inn = 0; inn < maxLength.size(); ++inn)
    {
        for (int j = 0; j < inn; ++j)
        {
            if (cubes->operator[](j) < cubes->operator[](inn) && maxLength[j] >= maxLength[inn])
            {
                maxLength[inn] = 1 + maxLength[j];
            }
        }
    }

    int maximum = 0;
    for (int x = 0; x < maxLength.size(); ++x)
    {
        if (maxLength[x] > maximum)
        {
            maximum = maxLength[x];
        }
    }
    return maximum;
}


int mainT() {
    std::vector<Cube>cubesList;
    Input(&cubesList);
    int maximum = Solve(&cubesList);
    std::cout << maximum;
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <iomanip>


bool equal(double first, double second)
{
    return fabs(first - second) < 1e-10;
}


bool less_or_equal(double first, double second)
{
    return first < second || equal(first, second);
}


bool less(double first, double second)
{
    return first < second && !equal(first, second);
}


double sqr(double number)
{
    return number * number;
}

template <typename T>
class heap
{
    std::vector<T> items;

public:
    int size() const
    {
        return static_cast<int>(items.size());
    }

    void add(T item)
    {
        items.push_back(item);
        int current_position = static_cast<int>(items.size()) - 1;
        while (current_position > 0 && items[current_position / 2] > items[current_position])
        {
            std::swap(items[current_position], items[current_position / 2]);
        }
    }

    T pop_min()
    {
        T to_return = items[0];
        items[0] = items.back();
        items.pop_back();

        int current_position = 0;
        std::vector<int> next_positions;
        // while (true)  is blocked
        while (1 > 0)
        {
            next_positions.clear();
            if (2 * current_position + 1 < size())
            {
                next_positions.push_back(2 * current_position + 1);
            }
            if (2 * current_position + 2 < size())
            {
                next_positions.push_back(2 * current_position + 2);
            }
            if (next_positions.empty())
                break;
            int minimum_next_position = 0;
            if (next_positions.size() > 1
                && items[next_positions.back()] < items[next_positions[0]])
            {
                minimum_next_position = 1;
            }
            std::swap(items[current_position], items[next_positions[minimum_next_position]]);
            current_position = next_positions[minimum_next_position];
        }
        return to_return;
    }

    bool empty() const
    {
        return size() == 0;
    }
};


struct point
{
    double coor_x, coor_y;

    point() : coor_x(0), coor_y(0) {}

    point(double _x, double _y)
    {
        coor_x = _x, coor_y = _y;
    }

    void read()
    {
        std::cin >> coor_x >> coor_y;
    }

    double length(point & that)
    {
        return sqrt(sqr(that.coor_x - coor_x) + sqr(that.coor_y - coor_y));
    }
};


void input(int & coverageMinimum, std::vector<point> * points)
{
    int pointsCount;
    std::cin >> pointsCount >> coverageMinimum;
    for (int i = 0; i < pointsCount; ++i)
    {
        points->push_back(point());
        (*points)[i].read();
    }
}


double get_max_coverage(double radius, std::vector<point> & points)
{
    std::vector<std::pair<double, int>> scanline_heap;
    for (auto point : points)
    {
        if (less(-fabs(point.coor_y), -radius))
            continue;
        double delta_before_covering = sqrt(sqr(radius) - sqr(point.coor_y));
        scanline_heap.push_back(std::make_pair(point.coor_x - delta_before_covering, -1));
        scanline_heap.push_back(std::make_pair(point.coor_x + delta_before_covering, 1));
    }
    std::sort(scanline_heap.begin(), scanline_heap.end());
    int points_count = 0;
    int max_points_count = 0;
    for (auto event: scanline_heap)
    {
        points_count += event.second * -1;
        max_points_count = std::max(max_points_count, points_count);
    }
    return max_points_count;
}


double solve(int coverage_minimum, std::vector<point> & points)
{
    double upper_bound = 10000, lower_bound = 0;
    while (!equal(lower_bound, upper_bound))
    {
        double middle = (upper_bound + lower_bound) / 2;
        int current_coverage = get_max_coverage(middle, points);
        if (current_coverage >= coverage_minimum)
        {
            upper_bound = middle;
        }
        else
        {
            lower_bound = middle;
        }
    }
    return upper_bound;
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int coverageMinimum;
    std::vector<point> points;

    input(coverageMinimum, &points);
    double minimumRadius = solve(coverageMinimum, points);
    std::cout << std::setprecision(6) << std::fixed << minimumRadius;
}

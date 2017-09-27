//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//
//struct sequence_element {
//    int index;
//    int value;
//
//    sequence_element()
//    {
//        index = rand();
//        value = rand();
//    }
//
//    sequence_element(const int index, const int value) {
//        this->index = index;
//        this->value = value;
//    }
//};
//
//void fill_sequence(const int sequence_lenght, std::vector<int>* sequence) {
//    for (auto i = 0; i < sequence_lenght; ++i) {
//        int number;
//        std::cin >> number;
//        sequence->push_back(number);
//    }
//}
//
//void print_vector(const std::vector<int>& sequence) {
//    for (auto i = 0; i < sequence.size(); ++i) {
//        std::cout << sequence[i] << ' ';
//    }
//}
//
//
//bool middleIsExtremum(int left, int middle, int right)
//{
//    return left < middle && middle > right || left > middle && middle < right;
//}
//
//
//bool is_element_in_alternate_sequence(const std::vector<sequence_element>& sequence,
//    const int index) {
//    return sequence[index - 1].value < sequence[index].value &&
//        sequence[index].value > sequence[index + 1].value ||
//        sequence[index - 1].value > sequence[index].value &&
//        sequence[index].value < sequence[index + 1].value;
//}
//
//
//void find_extremums_indexes(const std::vector<sequence_element>& sequence,
//    std::vector<int>* extremum_indexes) {
//    extremum_indexes->push_back(0);
//    for (auto i = 1; i < sequence.size() - 1; ++i) {
//        if (is_element_in_alternate_sequence(sequence, i)) {
//            extremum_indexes->push_back(sequence[i].index);
//        }
//    }
//    extremum_indexes->push_back(sequence.back().index);
//}
//
//int get_optimized_extremum(const std::vector<int>& sequence,
//    const bool is_infinum,
//    const int left_edge,
//    const int right_edge,
//    const int limit) {
//    for (auto i = left_edge; i < right_edge; ++i) {
//        if (is_infinum) {
//            if (sequence[i] > limit && sequence[i] < sequence[right_edge]) {
//                return i;
//            }
//        }
//        else {
//            if (sequence[i] < limit && sequence[i] > sequence[right_edge]) {
//                return i;
//            }
//        }
//    }
//}
//
//void optimize_extremums(const std::vector<int>& sequence, std::vector<int>* extremum_indexes) {
//    for (auto iterator = 0; iterator < extremum_indexes->size() - 1; ++iterator) {
//        auto left_edge_index = extremum_indexes->at(iterator);
//        auto right_edge_index = extremum_indexes->at(iterator + 1);
//        auto is_infinum = sequence[left_edge_index] < sequence[right_edge_index];
//        auto next_extremum_index = iterator < extremum_indexes->size() - 2
//            ? extremum_indexes->at(iterator + 2)
//            : left_edge_index;
//        auto limit = is_infinum
//            ? std::max(sequence[left_edge_index], sequence[next_extremum_index])
//            : std::min(sequence[left_edge_index], sequence[next_extremum_index]);
//        auto new_extremum_index = get_optimized_extremum(sequence,
//            is_infinum,
//            left_edge_index,
//            right_edge_index,
//            limit);
//        extremum_indexes->at(iterator + 1) = new_extremum_index;
//    }
//}
//
//std::vector<int> create_subsequence(const std::vector<int>& subsequence_indexes,
//    const std::vector<int>& sequence) {
//    auto subsequence = std::vector<int>();
//    for (auto i = 0; i < subsequence_indexes.size(); ++i) {
//        subsequence.push_back(sequence[subsequence_indexes[i]]);
//    }
//    return subsequence;
//}
//
//std::vector<int> generate_longest_subsequence(const std::vector<sequence_element>& sequence,
//    const std::vector<int>& original_sequence) {
//    if (sequence.size() == 1) {
//        auto new_vector = std::vector<int>();
//        new_vector.push_back(sequence[0].value);
//        return new_vector;
//    }
//    auto extremum_indexes = std::vector<int>();
//    find_extremums_indexes(sequence, &extremum_indexes);
//    optimize_extremums(original_sequence, &extremum_indexes);
//    return create_subsequence(extremum_indexes, original_sequence);
//}
//
//std::vector<sequence_element> get_shrinked_sequence(const std::vector<int>& sequence) {
//    auto shrinked_sequence = std::vector<sequence_element>();
//    shrinked_sequence.push_back(sequence_element(0, sequence[0]));
//    for (auto i = 1; i < sequence.size(); ++i) {
//        if (sequence[i] != sequence[i - 1]) {
//            shrinked_sequence.push_back(sequence_element(i, sequence[i]));
//        }
//    }
//    return shrinked_sequence;
//}
//
//
//bool nextIsBetter(std::vector<int> & previous, std::vector<int> & next)
//{
//    if (next.size() != previous.size())
//        return next.size() > previous.size();
//    for (int i = 0; i < previous.size(); ++i)
//        if (previous[i] != next[i])
//            return next[i] < previous[i];
//    return false;
//}
//
//
//bool isAlternating(std::vector<int> numbers, std::vector<int> positions)
//{
//    for (int i = 0; i < static_cast<int>(positions.size()) - 1; ++i)
//        if (numbers[positions[i]] == numbers[positions[i + 1]])
//            return false;
//    for (int i = 1; i < static_cast<int>(positions.size()) - 1; ++i)
//        if (!middleIsExtremum(numbers[positions[i - 1]],
//            numbers[positions[i]], numbers[positions[i + 1]]))
//            return false;
//    return true;
//}
//
//
//void getBfSolution(std::vector<int> & numbers, std::vector<int> * solution)
//{
//    int numbersCount = numbers.size();
//    int allCount = 1 << numbersCount;
//    std::vector<int> solutionPositions;
//    for (int i = 0; i < allCount; ++i)
//    {
//        std::vector<int> currentPos;
//        for (int j = 0; j < numbersCount; ++j) {
//            if ((1 << j) == ((1 << j) & i))
//                currentPos.push_back(j);
//        }
//        if (isAlternating(numbers, currentPos) && nextIsBetter(solutionPositions, currentPos))
//            solutionPositions = currentPos;
//    }
//
//    for (int i = 0; i < static_cast<int>(solutionPositions.size()); ++i)
//        solution->push_back(numbers[solutionPositions[i]]);
//}
//
//
//bool equals(std::vector<int> & first, std::vector<int> & second)
//{
//    if (first.size() != second.size())
//        return false;
//    for (int i = 0; i < first.size(); ++i)
//        if (first[i] != second[i])
//            return false;
//    return true;
//}
//
//
//int main() {
//    //int lenght;
//    //std::cin >> lenght;
//    //fill_sequence(lenght, &sequence);
//    //std::vector<int> sequence;
//    
//    //print_vector(subsequence);
//
//
//    int count = 0;
//    while (true)
//    {
//        count++;
//        if (count % 1000 == 0)
//            std::cout << count << std::endl;
//
//        std::vector<int> numbers;
//        for (int i = 0; i < 5; ++i)
//            numbers.push_back(rand() % 10);
//
//        std::vector<int> bfSolution;
//
//        auto shrinked_sequence = get_shrinked_sequence(numbers);
//        auto mySolution = generate_longest_subsequence(shrinked_sequence, numbers);
//        getBfSolution(numbers, &bfSolution);
//
//        if (!equals(bfSolution, mySolution))
//        {
//            print_vector(numbers);
//
//            std::cout << std::endl;
//
//            print_vector(mySolution);
//
//            std::cout << std::endl;
//
//            print_vector(bfSolution);
//            break;
//        }
//    }
//
//    return 0;
//}
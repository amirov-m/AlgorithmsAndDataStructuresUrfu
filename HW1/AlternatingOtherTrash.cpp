#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct sequence_element {
    int index;
    int value;

    sequence_element() {
        index = 0;
        value = 0;
    }/*

     sequence_element(sequence_element & other)
     {
     index = other.index;
     value = other.value;
     }*/

    sequence_element(int index, int value) {
        this->index = index;
        this->value = value;
    }
};

void fill_sequence(int sequence_lenght, std::vector<int>* sequence) {
    for (int i = 0; i < sequence_lenght; ++i) {
        int number;
        std::cin >> number;
        sequence->push_back(number);
    }
}

void print_vector(std::vector<int>& sequence) {
    for (int i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
}

bool is_element_in_alternate_sequence(std::vector<sequence_element>& sequence,
    int index) {
    return sequence[index - 1].value < sequence[index].value &&
        sequence[index].value > sequence[index + 1].value ||
        sequence[index - 1].value > sequence[index].value &&
        sequence[index].value < sequence[index + 1].value;
}


void find_extremums_indexes(std::vector<sequence_element>& sequence,
    std::vector<int>* extremum_indexes) {
    extremum_indexes->push_back(0);
    for (int i = 1; i < sequence.size() - 1; ++i) {
        if (is_element_in_alternate_sequence(sequence, i)) {
            extremum_indexes->push_back(sequence[i].index);
        }
    }
    extremum_indexes->push_back(sequence.back().index);
}

int get_optimized_extremum(std::vector<int>& sequence,
    bool is_infinum,
    int left_edge,
    int right_edge,
    int limit) {
    for (int i = left_edge; i < right_edge; ++i) {
        if (is_infinum) {
            if (sequence[i] > limit && sequence[i] < sequence[right_edge]) {
                return i;
            }
        }
        else {
            if (sequence[i] < limit && sequence[i] > sequence[right_edge]) {
                return i;
            }
        }
    }
}

void optimize_extremums(std::vector<int>& sequence, std::vector<int>* extremum_indexes) {
    for (int iterator = 0; iterator < extremum_indexes->size() - 1; ++iterator) {
        int left_edge_index = extremum_indexes->operator[](iterator);
        int right_edge_index = extremum_indexes->operator[](iterator + 1);
        bool is_infinum = sequence[left_edge_index] < sequence[right_edge_index];
        int next_extremum_index = iterator < extremum_indexes->size() - 2
            ? extremum_indexes->operator[](iterator + 2)
            : left_edge_index;
        int limit = is_infinum
            ? std::max(sequence[left_edge_index], sequence[next_extremum_index])
            : std::min(sequence[left_edge_index], sequence[next_extremum_index]);
        int new_extremum_index = get_optimized_extremum(sequence,
            is_infinum,
            left_edge_index,
            right_edge_index,
            limit);
        extremum_indexes->operator[](iterator + 1) = new_extremum_index;
    }
}

std::vector<int> create_subsequence(std::vector<int>& subsequence_indexes,
    std::vector<int>& sequence) {
    std::vector<int> subsequence;
    for (int i = 0; i < subsequence_indexes.size(); ++i) {
        subsequence.push_back(sequence[subsequence_indexes[i]]);
    }
    return subsequence;
}

std::vector<int> generate_longest_subsequence(std::vector<sequence_element>& sequence,
    std::vector<int>& original_sequence) {
    if (sequence.size() == 1) {
        std::vector<int> new_vector;
        new_vector.push_back(sequence[0].value);
        return new_vector;
    }
    std::vector<int> extremum_indexes;
    find_extremums_indexes(sequence, &extremum_indexes);
    optimize_extremums(original_sequence, &extremum_indexes);
    return create_subsequence(extremum_indexes, original_sequence);
}

std::vector<sequence_element> get_shrinked_sequence(std::vector<int>& sequence) {
    std::vector<sequence_element> shrinked_sequence;
    shrinked_sequence.push_back(sequence_element(0, sequence[0]));
    for (int i = 1; i < sequence.size(); ++i) {
        if (sequence[i] != sequence[i - 1]) {
            shrinked_sequence.push_back(sequence_element(i, sequence[i]));
        }
    }
    return shrinked_sequence;
}

int mainTrash() {
    int lenght;
    std::cin >> lenght;
    std::vector<int> sequence;

    fill_sequence(lenght, &sequence);

    std::vector<sequence_element> shrinked_sequence = get_shrinked_sequence(sequence);
    for (int i = 0; i < shrinked_sequence.size(); ++i) {
        std::cout << shrinked_sequence[i].index << " " << shrinked_sequence[i].value << std::endl;
    }
    std::vector<int> subsequence = generate_longest_subsequence(shrinked_sequence, sequence);
    print_vector(subsequence);

    return 0;
}

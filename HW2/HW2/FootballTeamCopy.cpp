//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//
//struct Footballer {
//    int index;
//    long long skill_level;
//
//    Footballer() {}
//
//    Footballer(const int index, const int skill_level) {
//        this->index = index;
//        this->skill_level = skill_level;
//    }
//};
//
//
//bool operator<(const Footballer& first, const Footballer& second) {
//    return first.skill_level < second.skill_level;
//}
//
//
//void fill_vector(const int count, std::vector<Footballer>* footballers) {
//    for (auto i = 0; i < count; ++i) {
//        int skill_level;
//        std::cin >> skill_level;
//        footballers->push_back(Footballer(i + 1, skill_level));
//    }
//}
//
//template <typename T>
//void merge_vectors(const std::vector<T>& left,
//    const std::vector<T>& right,
//    std::vector<T>* merged) {
//    auto it_left = left.begin();
//    auto it_right = right.begin();
//    while (it_left != left.end() && it_right != right.end()) {
//        if (*it_left < *it_right) {
//            merged->push_back(*it_left);
//            ++it_left;
//        }
//        else {
//            merged->push_back(*it_right);
//            ++it_right;
//        }
//    }
//    while (it_left != left.end()) {
//        merged->push_back(*it_left);
//        ++it_left;
//    }
//    while (it_right != right.end()) {
//        merged->push_back(*it_right);
//        ++it_right;
//    }
//}
//
//template <typename T>
//void sort(std::vector<T>* vector) {
//    const int size = vector->size();
//    if (size <= 1) {
//        return;
//    }
//    std::vector<T> left(vector->begin(), vector->begin() + size / 2);
//    std::vector<T> right(vector->begin() + size / 2, vector->end());
//    sort(&left);
//    sort(&right);
//    std::vector<T> merged_vector;
//    merge_vectors(left, right, &merged_vector);
//    *vector = merged_vector;
//}
//
//std::vector<Footballer> select_team(std::vector<Footballer>& footballers) {
//    if (footballers.size() < 3) {
//        return footballers;
//    }
//    auto left_edge = 0;
//    auto right_edge = 2;
//    auto wekest_member_index = 0;
//    auto strongest_member_index = 2;
//    auto max_sum = footballers[0].skill_level + footballers[1].skill_level;
//    auto current_sum = max_sum;
//    while (right_edge < footballers.size()) {
//        current_sum += footballers[right_edge].skill_level;
//        while (footballers[right_edge].skill_level > footballers[left_edge].skill_level
//            + footballers[left_edge + 1].skill_level) {
//            current_sum -= footballers[left_edge].skill_level;
//            ++left_edge;
//        }
//        if (current_sum > max_sum) {
//            max_sum = current_sum;
//            wekest_member_index = left_edge;
//            strongest_member_index = right_edge;
//        }
//        ++right_edge;
//    }
//    std::vector<Footballer> team_members(footballers.begin() + wekest_member_index,
//        footballers.begin() + strongest_member_index + 1);
//    return team_members;
//}
//
//template <typename T>
//void print_vector(const std::vector<T>& vector) {
//    for (auto it = vector.begin(); it < vector.end(); ++it) {
//        std::cout << *it << ' ';
//    }
//}
//
//long long count_force(std::vector<Footballer>& team_members) {
//    long long force = 0;
//    for (auto i = team_members.begin(); i < team_members.end(); ++i) {
//        force += i->skill_level;
//    }
//    return force;
//}
//
//void get_indeces(std::vector<Footballer>& team_members, std::vector<int>* indeces) {
//    for (auto i = team_members.begin(); i < team_members.end(); ++i) {
//        indeces->push_back(i->index);
//    }
//}
//
//void print_team_information(std::vector<Footballer>& team_members) {
//    auto const force = count_force(team_members);
//    std::cout << force << std::endl;
//    std::vector<int> indeces;
//    get_indeces(team_members, &indeces);
//    sort(&indeces);
//    print_vector(indeces);
//}
//
//int main() {
//    int count;
//    std::cin >> count;
//    std::vector<Footballer> footballers;
//    fill_vector(count, &footballers);
//    sort(&footballers);
//    auto team_members = select_team(footballers);
//    print_team_information(team_members);
//    return 0;
//}
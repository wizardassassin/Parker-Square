#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

std::string checkEdges(int a, int b, int c, int d, int x, int y) {
    int v_1 = a + b - c - d;
    bool vert_1 = v_1 == x - y;
    int h_1 = a + c - b - d;
    bool hori_1 = h_1 == x - y;
    return std::to_string(int(vert_1)) + std::to_string(int(hori_1));
}

void findCombinations(std::vector<std::pair<long long, long long>> arr) {
    bool printed = false;
    size_t arr_len = arr.size();
    for (size_t i = 0; i < arr_len; i++) {
        for (size_t j = i + 1; j < arr_len; j++) {
            auto val1 = arr[i];
            auto val2 = arr[j];
            auto a = val1.first;
            auto d = val1.second;
            auto b = val2.first;
            auto c = val2.second;
            std::vector<std::pair<std::pair<long long, long long>, std::string>>
                arr3;
            for (size_t i2 = 0; i2 < arr_len; i2++) {
                auto val3 = arr[i2];
                if (val3 == val1 || val3 == val2) {
                    continue;
                }
                auto x1 = val3.first;
                auto y1 = val3.second;
                auto com1 = checkEdges(a, b, c, d, x1, y1);
                if (com1 == "00") {
                    continue;
                }
                arr3.push_back(std::pair(val3, com1));
            }
            if (arr3.size() > 0) {
                printed = true;
                std::cout << "\n(" << val1.first << ", " << val1.second << ") "
                          << val2.first << ", " << val2.second << ") | ";
                for (auto& v : arr3) {
                    std::cout << "(" << v.first.first << ", " << v.first.second
                              << ", '" << v.second << "')";
                }
            }
        }
    }
    if (printed) {
        std::cout << "\n";
    }
}

std::unordered_map<long long, std::vector<std::pair<long long, long long>>>
    dict;
int max_val = 5000;
int main() {
    long long lastPrint = -1;
    for (size_t i = 0; i < max_val; i++) {
        if ((long long)(i * 100 / max_val) > lastPrint) {
            lastPrint = i * 100 / max_val;
            std::cout << "\r" << std::right << std::setw(3) << lastPrint << "%"
                      << std::flush;
        }
        for (size_t j = i + 1; j < max_val; j++) {
            auto a = i * i + j * j;
            auto pt = dict.find(a);
            if (pt == dict.end()) {
                std::vector<std::pair<long long, long long>> vect{
                    std::pair(i * i, j * j)};
                dict.insert(std::pair(a, vect));
                continue;
            }
            pt->second.push_back(std::pair(i * i, j * j));
        }
    }
    std::cout << "\r100%\n";
    lastPrint = -1;
    size_t dict_size = dict.size();
    size_t i = 0;
    for (auto const& [key, arr] : dict) {
        if ((long long)(i * 100 / dict_size) > lastPrint) {
            lastPrint = i * 100 / dict_size;
            std::cout << "\r" << std::right << std::setw(3) << lastPrint << "%"
                      << std::flush;
        }
        i++;
        if (arr.size() < 4) {
            continue;
        }
        findCombinations(arr);
    }
    std::cout << "\r100%\n";
}

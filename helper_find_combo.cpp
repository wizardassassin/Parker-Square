#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "helper_defs.cpp"

namespace findCombo {
std::string checkEdges2(ll a, ll b, ll c, ll d, ll x, ll y) {
    ll v_1 = a + b - c - d;
    bool v_2 = v_1 == x - y;
    bool v_3 = v_1 == y - x;
    std::string vert_1 = "0";
    if (v_2 && v_3) {
        vert_1 = "3";
    } else if (v_2) {
        vert_1 = "1";

    } else if (v_3) {
        vert_1 = "2";
    }
    ll h_1 = a + c - b - d;
    bool h_2 = h_1 == x - y;
    bool h_3 = h_1 == y - x;
    std::string hori_1 = "0";
    if (h_2 && h_3) {
        hori_1 = "3";
    } else if (h_2) {
        hori_1 = "1";

    } else if (h_3) {
        hori_1 = "2";
    }
    return vert_1 + hori_1;
}

bool findCombinations2(std::vector<pll> arr) {
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
            std::vector<std::pair<pll, psl>> arr3;
            for (size_t i2 = 0; i2 < arr_len; i2++) {
                auto val3 = arr[i2];
                if (val3 == val1 || val3 == val2) {
                    continue;
                }
                auto x1 = val3.first;
                auto y1 = val3.second;
                auto com1 = checkEdges2(a, b, c, d, x1, y1);
                if (com1 == "00") {
                    continue;
                }
                arr3.push_back(std::pair(val3, std::pair(com1, i2)));
            }
            if (arr3.size() > 0) {
                printed = true;
                std::cout << i << "(" << std::sqrt(val1.first) << ", "
                          << std::sqrt(val1.second) << ") " << j << "("
                          << std::sqrt(val2.first) << ", "
                          << std::sqrt(val2.second) << ") | ";
                for (auto& v : arr3) {
                    std::cout << v.second.second << "("
                              << std::sqrt(v.first.first) << ", "
                              << std::sqrt(v.first.second) << ", '"
                              << v.second.first << "') ";
                }
                std::cout << std::endl;
            }
        }
    }
    return printed;
}

std::string checkEdges(int a, int b, int c, int d, int x, int y) {
    int v_1 = a + b - c - d;
    bool vert_1 = v_1 == x - y;
    int h_1 = a + c - b - d;
    bool hori_1 = h_1 == x - y;
    std::string v = ((vert_1) ? "1" : "0");
    std::string h = ((hori_1) ? "1" : "0");
    return v + h;
}

bool findCombinations(std::ostream& stream, std::vector<pll> arr) {
    size_t arr_len = arr.size();
    for (size_t i = 0; i < arr_len; i++) {
        for (size_t j = i + 1; j < arr_len; j++) {
            auto val1 = arr[i];
            auto val2 = arr[j];
            auto a = val1.first;
            auto d = val1.second;
            auto b = val2.first;
            auto c = val2.second;
            std::vector<std::pair<pll, psl>> arr3;
            for (size_t i2 = j + 1; i2 < arr_len; i2++) {
                auto val3 = arr[i2];
                auto x1 = val3.first;
                auto y1 = val3.second;
                auto com1 = checkEdges(a, b, c, d, x1, y1);
                if (com1 == "00") {
                    continue;
                }
                arr3.push_back(std::pair(val3, std::pair(com1, i2)));
            }
            if (arr3.size() > 0) {
                stream << i << "(" << std::sqrt(val1.first) << ", "
                       << std::sqrt(val1.second) << ") " << j << "("
                       << std::sqrt(val2.first) << ", "
                       << std::sqrt(val2.second) << ") | ";
                for (auto& v : arr3) {
                    stream << v.second.second << "(" << std::sqrt(v.first.first)
                           << ", " << std::sqrt(v.first.second) << ", '"
                           << v.second.first << "') ";
                }
                stream << std::endl;
                return true;
            }
        }
    }
    return false;
}
bool findCombinations(std::vector<pll> arr) {
    return findCombinations(std::cout, arr);
}
}  // namespace findCombo

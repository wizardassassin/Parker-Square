#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

typedef std::vector<std::vector<int64_t>> vv_int;

namespace compute_quiet {
std::string checkEdges(int64_t a, int64_t b, int64_t c, int64_t d, int64_t x,
                       int64_t y) {
    int64_t v_1 = a + b - c - d;
    bool vert_1 = v_1 == x - y;
    int64_t h_1 = a + c - b - d;
    bool hori_1 = h_1 == x - y;
    std::string v = ((vert_1) ? "1" : "0");
    std::string h = ((hori_1) ? "1" : "0");
    return v + h;
}

bool findCombinations(std::ostream &stream,
                      std::vector<std::pair<int64_t, int64_t>> arr) {
    size_t arr_len = arr.size();
    for (size_t i = 0; i < arr_len; i++) {
        for (size_t j = i + 1; j < arr_len; j++) {
            auto val1 = arr[i];
            auto val2 = arr[j];
            auto a = val1.first * val1.first;
            auto d = val1.second * val1.second;
            auto b = val2.first * val2.first;
            auto c = val2.second * val2.second;
            std::vector<std::pair<std::pair<int64_t, int64_t>,
                                  std::pair<std::string, int64_t>>>
                arr3;
            for (size_t i2 = j + 1; i2 < arr_len; i2++) {
                auto val3 = arr[i2];
                auto x1 = val3.first * val3.first;
                auto y1 = val3.second * val3.second;
                auto com1 = checkEdges(a, b, c, d, x1, y1);
                if (com1 == "00") {
                    continue;
                }
                arr3.push_back(std::pair(val3, std::pair(com1, i2)));
            }
            if (arr3.size() > 0) {
                stream << i << "(" << val1.first << ", " << val1.second << ") "
                       << j << "(" << val2.first << ", " << val2.second
                       << ") |";
                for (auto &v : arr3) {
                    stream << " " << v.second.second << "(" << v.first.first
                           << ", " << v.first.second << ", '" << v.second.first
                           << "')";
                }
                stream << "\n";
                return true;
            }
        }
    }
    return false;
}

void pre_compute(vv_int &vect, int64_t start) {
    int64_t start_min = std::ceil(std::sqrt(start * start / 2));
    for (int64_t i = start_min; i < start; i++) {
        int64_t j_min = std::ceil(std::sqrt(start * start - i * i));
        int64_t j_lim = std::ceil(std::sqrt((start + 1) * (start + 1) - i * i));
        int64_t j_max = std::min(i, j_lim);
        for (int64_t j = j_min; j < j_max; j++) {
            int64_t v = i * i + j * j;
            vect[v - start * start].push_back(j);
            vect[v - start * start].push_back(i);
        }
    }
}

void compute(vv_int &vect, int64_t start) {
    for (int64_t i = start; i < start + 1; i++) {
        int64_t j_lim = std::ceil(std::sqrt((start + 1) * (start + 1) - i * i));
        int64_t j_max = std::min(i, j_lim);
        for (int64_t j = 0; j < j_max; j++) {
            int64_t v = i * i + j * j;
            vect[v - start * start].push_back(j);
            vect[v - start * start].push_back(i);
        }
    }
}

void post_compute(std::ostream &stream, vv_int &vect, int64_t vect_len) {
    std::stringstream stream2;
    int64_t count = 0;
    for (int64_t i = 0; i < vect_len; i++) {
        int64_t len = vect[i].size();
        if (len > 6) {
            std::vector<std::pair<int64_t, int64_t>> vect2(len / 2);
            for (int64_t j = 0; j < len - 1; j += 2) {
                int64_t p1 = vect[i][j];
                int64_t p2 = vect[i][j + 1];
                vect2[j / 2] = std::pair(p1, p2);
            }
            bool printed = findCombinations(stream2, vect2);
            if (printed) {
                count++;
            }
        }
    }
    stream << count << "\n";
    stream << stream2.str();
}

void main_compute(std::ostream &stream, vv_int &vect, int64_t start) {
    int64_t stop = start + 1;
    stream << start << " " << stop << "\n";
    for (size_t i = 0; i < 2 * start + 1; i++) vect[i].clear();
    // vect.clear();
    // vect.reserve(2 * start + 1);
    // vect.resize(2 * start + 1);
    pre_compute(vect, start);
    compute(vect, start);
    post_compute(stream, vect, 2 * start + 1);
}
}  // namespace compute_quiet
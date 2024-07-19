#pragma once

#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

typedef std::vector<std::vector<int64_t>> vv_int;

namespace ComputeIncrement {
int checkEdges(int64_t a, int64_t b, int64_t c, int64_t d, int64_t x,
               int64_t y) {
    int64_t v_1 = a + b - c - d;
    bool vert_1 = v_1 == x - y;
    int64_t h_1 = a + c - b - d;
    bool hori_1 = h_1 == x - y;
    return (vert_1 << 1) + hori_1;
}

bool findCombinations(std::ostream &stream, const std::vector<int64_t> &vect) {
    size_t arr_len = vect.size();
    for (size_t i = 0; i < arr_len - 1; i += 2) {
        for (size_t j = i + 2; j < arr_len - 1; j += 2) {
            auto val1_f = vect[i];
            auto val1_s = vect[i + 1];
            auto val2_f = vect[j];
            auto val2_s = vect[j + 1];
            auto a = val1_f * val1_f;
            auto d = val1_s * val1_s;
            auto b = val2_f * val2_f;
            auto c = val2_s * val2_s;
            std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>> vect2;
            for (size_t i2 = j + 2; i2 < arr_len - 1; i2 += 2) {
                auto val3_f = vect[i2];
                auto val3_s = vect[i2 + 1];
                auto x1 = val3_f * val3_f;
                auto y1 = val3_s * val3_s;
                auto com1 = checkEdges(a, b, c, d, x1, y1);
                if (com1 == 0) continue;
                vect2.push_back({val3_f, val3_s, com1, i2});
            }
            if (vect2.size() > 0) {
                stream << i / 2 << "(" << val1_f << ", " << val1_s << ") "
                       << j / 2 << "(" << val2_f << ", " << val2_s << ") |";
                for (auto &v : vect2) {
                    stream << " " << std::get<3>(v) / 2 << "(" << std::get<0>(v)
                           << ", " << std::get<1>(v) << ", '"
                           << ((std::get<2>(v) >> 1) & 1)
                           << (std::get<2>(v) & 1) << "')";
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

void post_compute(std::ostream &stream, const vv_int &vect, int64_t vect_len) {
    for (int64_t i = 0; i < vect_len; i++) {
        int64_t len = vect[i].size();
        if (len < 8) continue;
        findCombinations(stream, vect[i]);
    }
}

void main_compute(std::ostream &stream, vv_int &vect, int64_t start) {
    int64_t stop = start + 1;
    std::stringstream stream2;
    stream2 << start << " " << stop << "\n";
    pre_compute(vect, start);
    compute(vect, start);
    post_compute(stream2, vect, 2 * start + 1);
    stream << stream2.str() << std::flush;
}
}  // namespace ComputeIncrement
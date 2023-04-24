#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "helper_defs.hpp"
#include "helper_find_combo.hpp"
#include "helper_timer.hpp"

namespace compute_1 {
void pre_compute_1(std::ostream &stream, std::vector<vv> &vect, ll start_2,
                   ll start, ll max_val) {
    ll lastPrint;
    tp startBar;
    tp stopBar;
    timer::labelBar(stream, startBar, lastPrint, "Pre Compute");
    ll start_min = std::ceil(std::sqrt(start_2 / 2));
    for (ll i = start_min; i < start; i++) {
        ll j_min = std::ceil(std::sqrt(start_2 - i * i));
        ll j_lim = std::ceil(std::sqrt(max_val - i * i));
        ll j_max = std::min(i, j_lim);
        for (ll j = j_min; j < j_max; j++) {
            long long v = i * i + j * j;
            vect[v - start_2].push_back(j);
            vect[v - start_2].push_back(i);
        }
    }
    timer::completeBar(stream, startBar, stopBar);
}

void compute_1(std::ostream &stream, std::vector<vv> &vect, ll start,
               ll start_2, ll max_lim, ll max_val) {
    ll lastPrint;
    tp startBar;
    tp stopBar;
    timer::labelBar(stream, startBar, lastPrint, "Compute");
    for (ll i = start; i < max_lim; i++) {
        ll j_lim = std::ceil(std::sqrt(max_val - i * i));
        ll j_max = std::min(i, j_lim);
        for (ll j = 0; j < j_max; j++) {
            long long v = i * i + j * j;
            vect[v - start_2].push_back(j);
            vect[v - start_2].push_back(i);
        }
    }
    timer::completeBar(stream, startBar, stopBar);
}

void post_compute_1(std::ostream &stream, std::vector<vv> &vect, ll vect_len) {
    ll lastPrint;
    tp startBar;
    tp stopBar;
    timer::labelBar(stream, startBar, lastPrint, "Post Compute");
    ll count = 0;
    for (ll i = 0; i < vect_len; i++) {
        ll len = vect[i].size();
        if (len > 6) {
            std::vector<pll> vect2(len / 2);
            for (ll j = 0; j < len - 1; j += 2) {
                ll p1 = vect[i][j];
                ll p2 = vect[i][j + 1];
                vect2[j / 2] = std::pair(p1, p2);
            }
            bool printed = findCombo::findCombinations(stream, vect2);
            if (printed) {
                count++;
            }
        }
    }
    stream << count << " pairs"
           << "\n";
    timer::completeBar(stream, startBar, stopBar);
}

void main_compute_1(std::ostream &stream, ll start, ll max_lim) {
    stream << "Start: " << start << std::endl;
    stream << "Stop: " << max_lim << std::endl;
    auto startTime = std::chrono::steady_clock::now();
    ll start_2 = start * start;
    ll max_val = max_lim * max_lim;
    ll vect_len = max_val - start_2;
    std::vector<vv> vect(vect_len);
    pre_compute_1(stream, vect, start_2, start, max_val);
    compute_1(stream, vect, start, start_2, max_lim, max_val);
    post_compute_1(stream, vect, vect_len);
    auto stopTime = std::chrono::steady_clock::now();
    stream << "Elapsed:\n";
    timer::printTime(stream, startTime, stopTime);
}
}  // namespace compute_1
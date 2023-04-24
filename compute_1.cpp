#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "helper_defs.hpp"
#include "helper_find_combo.hpp"
#include "helper_timer.hpp"

int main(int argc, char const *argv[]) {
    // ll start = 0;
    // ll max_lim = 10000;
    ll start;
    ll max_lim;
    if (argc == 3) {
        start = std::stoll(argv[1]);
        max_lim = std::stoll(argv[2]);
    } else {
        std::cout << "Start and Stop Values [Start, Stop): " << std::flush;
        std::cin >> start >> max_lim;
    }
    std::cout << "Start: " << start << std::endl;
    std::cout << "Stop: " << max_lim << std::endl;
    auto startTime = std::chrono::steady_clock::now();
    ll start_2 = start * start;
    ll max_val = max_lim * max_lim;
    ll vect_len = max_val - start_2;
    std::vector<vv> vect(vect_len);
    timer::labelBar("Pre Compute");
    ll start_min = std::ceil(std::sqrt(start_2 / 2));
    for (ll i = start_min; i < start; i++) {
        timer::progressBar(i - start_min, start - start_min);
        ll j_min = std::ceil(std::sqrt(start_2 - i * i));
        ll j_lim = std::ceil(std::sqrt(max_val - i * i));
        ll j_max = std::min(i, j_lim);
        for (ll j = j_min; j < j_max; j++) {
            long long v = i * i + j * j;
            vect[v - start_2].push_back(j);
            vect[v - start_2].push_back(i);
        }
    }
    timer::completeBar();
    timer::labelBar("Compute");
    for (ll i = start; i < max_lim; i++) {
        timer::progressBar(i - start, max_lim - start);
        ll j_lim = std::ceil(std::sqrt(max_val - i * i));
        ll j_max = std::min(i, j_lim);
        for (ll j = 0; j < j_max; j++) {
            long long v = i * i + j * j;
            vect[v - start_2].push_back(j);
            vect[v - start_2].push_back(i);
        }
    }
    timer::completeBar();
    timer::labelBar("Post Compute");
    ll count = 0;
    for (ll i = 0; i < vect_len; i++) {
        timer::progressBar(i, vect_len);
        ll len = vect[i].size();
        if (len > 6) {
            std::vector<pll> vect2(len / 2);
            for (ll j = 0; j < len - 1; j += 2) {
                ll p1 = vect[i][j] * vect[i][j];
                ll p2 = vect[i][j + 1] * vect[i][j + 1];
                vect2[j / 2] = std::pair(p1, p2);
            }
            bool printed = findCombo::findCombinations2(vect2);
            if (printed) {
                timer::printBar();
                count++;
            }
        }
    }
    std::cout << count << " pairs"
              << "\n";
    timer::completeBar();
    auto stopTime = std::chrono::steady_clock::now();
    std::cout << "Elapsed:\n";
    timer::printTime(startTime, stopTime);
}

#include <chrono>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

#include "helper_defs.cpp"
#include "helper_find_combo.cpp"
#include "helper_timer.cpp"

int main(int argc, char const *argv[]) {
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
    timer::labelBar("Compute");
    ll count = 0;
    for (ll i = start_2; i < max_val; i++) {
        timer::progressBar(i, max_val);
        ll j_max = std::ceil(std::sqrt(i / 2.0));
        std::vector<ll> vect;
        for (ll j = 0; j < j_max; j++) {
            ll k = i - j * j;
            ll k2 = (long long)std::sqrt(k);
            if (k2 * k2 != k) {
                continue;
            }
            vect.push_back(j);
            vect.push_back(k2);
        }
        if (vect.size() < 8) {
            continue;
        }
        std::vector<pll> vect2;
        for (ll j = vect.size() - 1; j >= 1; j -= 2) {
            vect2.push_back(
                std::pair(vect[j - 1] * vect[j - 1], vect[j] * vect[j]));
        }
        bool printed = findCombo::findCombinations(vect2);
        if (printed) {
            timer::printBar();
            count++;
        }
    }
    std::cout << count << " pairs"
              << "\n";
    timer::completeBar();
    auto stopTime = std::chrono::steady_clock::now();
    std::cout << "Elapsed:\n";
    timer::printTime(startTime, stopTime);
}
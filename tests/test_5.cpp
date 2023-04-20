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

#define ll long long
#define vv std::vector<ll>
#define pll std::pair<ll, ll>
#define psl std::pair<std::string, ll>
#define tp std::chrono::steady_clock::time_point

void print_vector(vv vect) {
    for (ll v : vect) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
}

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

std::string checkEdges(int a, int b, int c, int d, int x, int y) {
    int v_1 = a + b - c - d;
    bool vert_1 = v_1 == x - y;
    int h_1 = a + c - b - d;
    bool hori_1 = h_1 == x - y;
    std::string v = ((vert_1) ? "1" : "0");
    std::string h = ((hori_1) ? "1" : "0");
    return v + h;
}

bool findCombinations(std::vector<pll> arr) {
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
                auto com1 = checkEdges(a, b, c, d, x1, y1);
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

ll lastPrint;
tp startBar;
tp stopBar;
void printTime(tp startTime, tp stopTime) {
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        stopTime - startTime);
    ll time = duration.count();
    if (time < 1000) {
        std::cout << time / 1000.0 << " ms" << std::endl;
        return;
    }
    if (time < 10 * 1000) {
        std::cout << time / 10 / 100.0 << " ms" << std::endl;
        return;
    }
    if (time < 100 * 1000) {
        std::cout << time / 100 / 10.0 << " ms" << std::endl;
        return;
    }
    time /= 1000;
    ll sec = 1000;
    ll min = 60 * sec;
    ll hour = 60 * min;
    ll day = 24 * hour;
    if (time < sec) {
        std::cout << time << " ms" << std::endl;
        return;
    }
    if (time < 10 * sec) {
        std::cout << time / 10 / 100.0 << " sec" << std::endl;
        return;
    }
    if (time < min) {
        std::cout << time / 100 / 10.0 << " sec" << std::endl;
        return;
    }
    if (time < 10 * min) {
        std::cout << time / 600 / 100.0 << " min" << std::endl;
        return;
    }
    if (time < hour) {
        std::cout << time / 6000 / 10.0 << " min" << std::endl;
        return;
    }
    if (time < 10 * hour) {
        std::cout << time / 36000 / 100.0 << " hour" << std::endl;
        return;
    }
    if (time < day || true) {
        std::cout << time / 360000 / 10.0 << " hour" << std::endl;
        return;
    }
}
void printBar() {
    std::cout << std::right << std::setw(3) << lastPrint << "%"
              << "\r" << std::flush;
}

void progressBar(ll i, ll max_val) {
    if ((i * 100 / max_val) > lastPrint) {
        lastPrint = i * 100 / max_val;
        printBar();
    }
}

void completeBar() {
    stopBar = std::chrono::steady_clock::now();
    std::cout << "100%\n";
    printTime(startBar, stopBar);
}

void labelBar(std::string label) {
    lastPrint = -1;
    startBar = std::chrono::steady_clock::now();
    std::cout << label << ":" << std::endl;
}

int main() {
    auto startTime = std::chrono::steady_clock::now();
    ll start = 0;
    ll max_lim = 10000;
    ll max_val = max_lim * max_lim;
    std::vector<vv> vect(max_val);
    labelBar("Compute");
    for (ll i = start; i < max_lim; i++) {
        progressBar(i, max_lim);
        for (ll j = 0; j < i; j++) {
            long long v = i * i + j * j;
            if (v < max_val) {
                vect[v].push_back(j);
                vect[v].push_back(i);
            } else {
                break;
            }
        }
    }
    completeBar();
    labelBar("Post Compute");
    ll count = 0;
    for (ll i = 0; i < max_val; i++) {
        progressBar(i, max_val);
        ll len = vect[i].size();
        if (len > 6) {
            std::vector<pll> vect2(len / 2);
            for (ll j = 0; j < len - 1; j += 2) {
                ll p1 = vect[i][j] * vect[i][j];
                ll p2 = vect[i][j + 1] * vect[i][j + 1];
                vect2[j / 2] = std::pair(p1, p2);
            }
            bool printed = findCombinations(vect2);
            if (printed) {
                count++;
                printBar();
            }
        }
    }
    std::cout << count << "pairs"
              << "\n";
    completeBar();
    auto stopTime = std::chrono::steady_clock::now();
    std::cout << "Elapsed:\n";
    printTime(startTime, stopTime);
}

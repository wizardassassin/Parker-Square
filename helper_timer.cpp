#include <chrono>
#include <iomanip>
#include <iostream>

#include "helper_defs.cpp"

namespace timer {
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
}  // namespace timer

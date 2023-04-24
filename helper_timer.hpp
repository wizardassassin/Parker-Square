#include <chrono>
#include <iomanip>
#include <iostream>

#include "helper_defs.hpp"

namespace timer {
ll lastPrint;
tp startBar;
tp stopBar;
void printTime(std::ostream &stream, const tp &startTime, const tp &stopTime) {
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        stopTime - startTime);
    ll time = duration.count();
    if (time < 1000) {
        stream << time / 1000.0 << " ms" << std::endl;
        return;
    }
    if (time < 10 * 1000) {
        stream << time / 10 / 100.0 << " ms" << std::endl;
        return;
    }
    if (time < 100 * 1000) {
        stream << time / 100 / 10.0 << " ms" << std::endl;
        return;
    }
    time /= 1000;
    ll sec = 1000;
    ll min = 60 * sec;
    ll hour = 60 * min;
    ll day = 24 * hour;
    if (time < sec) {
        stream << time << " ms" << std::endl;
        return;
    }
    if (time < 10 * sec) {
        stream << time / 10 / 100.0 << " sec" << std::endl;
        return;
    }
    if (time < min) {
        stream << time / 100 / 10.0 << " sec" << std::endl;
        return;
    }
    if (time < 10 * min) {
        stream << time / 600 / 100.0 << " min" << std::endl;
        return;
    }
    if (time < hour) {
        stream << time / 6000 / 10.0 << " min" << std::endl;
        return;
    }
    if (time < 10 * hour) {
        stream << time / 36000 / 100.0 << " hour" << std::endl;
        return;
    }
    if (time < day) {
        stream << time / 360000 / 10.0 << " hour" << std::endl;
        return;
    }
    std::streamsize size = stream.precision();
    stream << std::fixed << std::setprecision(1) << time / 360000 / 10.0
           << " hour" << std::endl;
    stream << std::defaultfloat << std::setprecision(size);
    return;
}
void printTime(const tp &startTime, const tp &stopTime) {
    printTime(std::cout, startTime, stopTime);
}

void printBar(std::ostream &stream, ll lastPrint) {
    stream << std::right << std::setw(3) << lastPrint << "%"
           << "\r" << std::flush;
}
void printBar() {
    printBar(std::cout, lastPrint);
}

void progressBar(std::ostream &stream, ll &lastPrint, ll i, ll max_val) {
    if ((i * 100 / max_val) > lastPrint) {
        lastPrint = i * 100 / max_val;
        printBar();
    }
}
void progressBar(ll i, ll max_val) {
    progressBar(std::cout, lastPrint, i, max_val);
}

void completeBar(std::ostream &stream, const tp &startBar, tp &stopBar) {
    stopBar = std::chrono::steady_clock::now();
    stream << "100%\n";
    printTime(stream, startBar, stopBar);
}
void completeBar() {
    completeBar(std::cout, startBar, stopBar);
}

void labelBar(std::ostream &stream, tp &startBar, ll &lastPrint,
              const std::string &label) {
    lastPrint = -1;
    startBar = std::chrono::steady_clock::now();
    stream << label << ":" << std::endl;
}
void labelBar(const std::string &label) {
    labelBar(std::cout, startBar, lastPrint, label);
}
}  // namespace timer

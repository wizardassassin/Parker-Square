#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>

namespace Timer {
void printTime(std::ostream& stream,
               const std::chrono::steady_clock::time_point& startTime,
               const std::chrono::steady_clock::time_point& stopTime) {
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        stopTime - startTime);
    long long time = duration.count();
    if (time < 1000) {
        stream << time / 1000.0 << " ms";
        return;
    }
    if (time < 10 * 1000) {
        stream << time / 10 / 100.0 << " ms";
        return;
    }
    if (time < 100 * 1000) {
        stream << time / 100 / 10.0 << " ms";
        return;
    }
    time /= 1000;
    long long sec = 1000;
    long long min = 60 * sec;
    long long hour = 60 * min;
    long long day = 24 * hour;
    if (time < sec) {
        stream << time << " ms";
        return;
    }
    if (time < 10 * sec) {
        stream << time / 10 / 100.0 << " sec";
        return;
    }
    if (time < min) {
        stream << time / 100 / 10.0 << " sec";
        return;
    }
    if (time < 10 * min) {
        stream << time / 600 / 100.0 << " min";
        return;
    }
    if (time < hour) {
        stream << time / 6000 / 10.0 << " min";
        return;
    }
    if (time < 10 * hour) {
        stream << time / 36000 / 100.0 << " hour";
        return;
    }
    if (time < day) {
        stream << time / 360000 / 10.0 << " hour";
        return;
    }
    std::streamsize size = stream.precision();
    stream << std::fixed << std::setprecision(1) << time / 360000 / 10.0
           << " hour";
    stream << std::defaultfloat << std::setprecision(size);
    return;
}
}  // namespace Timer
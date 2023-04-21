#include <chrono>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
#include <utility>

#include "helper_parse_arg.hpp"
#include "thread_pool.hpp"
#include "threaded_compute_1.hpp"

int main(int argc, char const *argv[]) {
    long long minValue = 0;
    long long maxValue = 10000;
    long long vectorSize = 4000;
    long long threadCount = 4;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            const char *str = argv[i];
            int len = strlen(str);
            bool validArg = argParser::extractArg(str, len, minValue, maxValue,
                                                  vectorSize, threadCount);
            if (!validArg) {
                std::cerr << "Unused arg: " << str << std::endl;
            }
        }
    }
    if (threadCount == 0) {
        threadCount = std::thread::hardware_concurrency();
    }
    std::cout << "minValue: " << minValue << std::endl;
    std::cout << "maxValue: " << maxValue << std::endl;
    std::cout << "vectorSize: " << vectorSize << std::endl;
    std::cout << "threadCount: " << threadCount << std::endl;

    ThreadPool::ThreadPool pool(threadCount);
    std::vector<std::pair<long long, long long>> ranges;
    long long i = minValue;
    while (i < maxValue) {
        long long nextValue = std::min(
            (long long)std::sqrt(i * i + vectorSize * vectorSize), maxValue);
        ranges.push_back(std::pair(i, nextValue));
        i = nextValue;
    }
    long long jobCount = ranges.size();
    for (long long i = 0; i < jobCount; i++) {
        pool.addJob([&ranges, i] {
            std::ofstream file;
            file.open("compute_" + std::to_string(ranges[i].first) + "_" +
                      std::to_string(ranges[i].second) + ".txt");
            compute_1::main_compute_1(file, ranges[i].first, ranges[i].second);
            file.close();
        });
    }
    pool.start();
    pool.wait();
    pool.stop();
    // for (std::stringstream &ss : vect) {
    //     std::cout << ss.str();
    // }

    return 0;
}

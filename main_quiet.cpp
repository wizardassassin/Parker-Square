#include <chrono>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <regex>
#include <sstream>
#include <thread>
#include <utility>

#include "helper_parse_arg.hpp"
#include "thread_pool.hpp"
#include "threaded_compute_1.hpp"

int main(int argc, char const *argv[]) {
    auto start = std::chrono::steady_clock::now();
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
        long long nextValue =
            std::min((long long)std::sqrt(i * i + vectorSize * vectorSize /
                                                      (long double)threadCount),
                     maxValue);
        ranges.push_back(std::pair(i, nextValue));
        i = nextValue;
    }
    long long jobCount = ranges.size();
    std::cout << "jobCount: " << jobCount << std::endl;

    std::string fileName = "aggregated_" + std::to_string(minValue) + "_" +
                           std::to_string(maxValue) + ".txt";
    std::mutex fileLock;
    std::ofstream aggFile;
    aggFile.open(fileName);

    for (long long i = 0; i < jobCount; i++) {
        pool.addJob([&ranges, i, &fileLock, &aggFile] {
            std::stringstream stream;
            compute_1::main_compute_1(stream, ranges[i].first,
                                      ranges[i].second);
            std::string str = stream.str();
            std::regex pattern(
                "(\\d+\\(\\d+, \\d+\\) ){2}\\|( \\d+\\(\\d+, \\d+, "
                "'[01]{2}'\\))+\\n");
            std::sregex_iterator it(str.begin(), str.end(), pattern);
            std::sregex_iterator end;
            std::string str2 = "";
            while (it != end) {
                str2 += it->str();
                it++;
            }
            if (str2.size() == 0) return;
            std::unique_lock<std::mutex> lock(fileLock);
            aggFile << str2;
        });
    }
    pool.start();
    pool.wait(std::cout);
    pool.stop();
    aggFile.close();
    auto stop = std::chrono::steady_clock::now();
    std::cout << "\nElapsed:\n";
    timer::printTime(std::cout, start, stop);
    return 0;
}

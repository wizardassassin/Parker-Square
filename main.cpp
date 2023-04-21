#include <iostream>
#include <sstream>
#include <thread>

#include "helper_parse_arg.cpp"
#include "threaded_compute_1.cpp"

int main(int argc, char const *argv[]) {
    long long minValue = 0;
    long long maxValue = 10000;
    long long vectorSize = 1000;
    long long threadCount = 1;
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
    std::stringstream ss;
    compute_1::main_compute_1(ss, minValue, maxValue);
    std::cout << ss.str();
    return 0;
}

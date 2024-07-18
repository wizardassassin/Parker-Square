// Parses output files to find the start number, end number, missing values, and
// the next number

#include <algorithm>
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <thread>
#include <vector>

int64_t check_files(const std::string& prefix, const long long threadCount) {
    std::set<int64_t> val_set;
    for (int i = 0; i < threadCount; i++) {
        std::string filename = prefix + "_" + std::to_string(i) + "_" +
                               std::to_string(threadCount) + ".txt";
        std::ifstream file;
        file.open(filename);
        if (!file.good()) {
            std::cout << filename << " was not found\n";
            return -1;
        }
        std::cout << "Reading: " << filename << "\n";
        // file.seekg(0, file.end);
        // long long file_size = file.tellg();
        // file.seekg(0, file.beg);
        // file.seekg(std::max(-1000LL, -file_size), file.end);
        std::string str;
        std::regex re("^(\\d+) (\\d+)$");
        std::smatch sm;
        while (std::getline(file, str)) {
            if (!std::regex_match(str, sm, re)) continue;
            assert(sm.size() == 3);
            int64_t val1 = std::stoll(sm[1]);
            int64_t val2 = std::stoll(sm[2]);
            assert(val2 - val1 == 1);
            val_set.insert(val1);
        }
    }
    // assert(val_set.size() > threadCount * 2);
    int64_t start_val = *val_set.begin();
    int64_t end_val = *val_set.rbegin();

    std::cout << "Start: " << start_val << "\n";
    std::cout << "End: " << end_val << "\n";
    std::cout << "Missing Values: " << "\n";
    for (int64_t i = start_val; i <= end_val; i++) {
        if (val_set.find(i) == val_set.end()) {
            std::cout << i << "\n";
        }
    }

    return *val_set.rbegin() + 1;
}

int main(int argc, char const* argv[]) {
    if (argc < 3) return 1;
    const long thread_count = std::stoll(argv[1]);
    const std::string prefix = argv[2];
    int64_t last_val = check_files(prefix, thread_count);
    std::cout << "Next Value: " << last_val << "\n";
    return 0;
}
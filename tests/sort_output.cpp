#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <utility>
#include <vector>

int main(int argc, char const* argv[]) {
    if (argc < 2) return 1;
    const std::string filename = argv[1];

    std::ifstream infile(filename);

    std::vector<std::pair<int64_t, std::string>> vect;

    std::string str;
    std::regex re("^\\d+\\((\\d+), (\\d+)\\) .+$");
    std::smatch sm;
    while (std::getline(infile, str)) {
        assert(std::regex_match(str, sm, re));
        assert(sm.size() == 3);
        long long val1 = std::stoll(sm[1]);
        long long val2 = std::stoll(sm[2]);
        vect.push_back(std::pair(val1 * val1 + val2 * val2, str));
    }
    std::sort(vect.begin(), vect.end(),
              [](auto a, auto b) { return a.first < b.first; });

    std::ofstream outfile(filename + ".txt");
    for (const auto& val : vect) {
        outfile << val.second << "\n";
    }

    return 0;
}
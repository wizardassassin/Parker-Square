#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <utility>
#include <vector>

int main(int argc, char const* argv[]) {
    if (argc < 2) return 1;
    const std::string filename = argv[1];

    const long long min_val = (argc >= 4)
                                  ? std::stoll(argv[2]) * std::stoll(argv[2])
                                  : std::numeric_limits<long long>::min();
    const long long max_val = (argc >= 4)
                                  ? std::stoll(argv[3]) * std::stoll(argv[3])
                                  : std::numeric_limits<long long>::max();

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
        if (val.first < min_val) continue;
        if (val.first >= max_val) continue;
        outfile << val.second << "\n";
    }

    return 0;
}
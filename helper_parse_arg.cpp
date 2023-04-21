#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>

namespace argParser {
bool extractArg(const char *str, int len, long long &minValue,
                long long &maxValue, long long &vectorSize,
                long long &threadCount) {
    if (len < 5 || str[0] != '-' || str[1] != '-') {
        return false;
    }
    std::string varName = "";
    std::string varValue = "";
    char currChar;
    int inc = 2;
    while (inc < len && (currChar = str[inc++]) != '=') {
        if (!isalpha(currChar)) {
            return false;
        }
        varName += currChar;
    }
    while (inc < len) {
        currChar = str[inc++];
        if (!isdigit(currChar)) {
            return false;
        }
        varValue += currChar;
    }
    if (varName.length() == 0 || varValue.length() == 0) {
        return false;
    }
    // Negative values aren't needed here
    long long val = std::stoll(varValue);
    // Repetitive code
    if (varName == "minValue") {
        minValue = val;
        return true;
    }
    if (varName == "maxValue") {
        maxValue = val;
        return true;
    }
    if (varName == "vectorSize") {
        vectorSize = val;
        return true;
    }
    if (varName == "threadCount") {
        threadCount = val;
        return true;
    }
    return false;
}
}  // namespace argParser
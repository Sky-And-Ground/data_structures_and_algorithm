#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

int32_t string_search_bf(const std::string& str, const std::string& pattern) {
    int32_t strLen = str.size();
    int32_t patternLen = pattern.size();
    int32_t i = 0;
    int32_t j = 0;

    while (i < strLen && j < patternLen) {
        if (str[i] == pattern[j]) {
            ++i;
            ++j;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
    }

    if (j == patternLen) {
        return i - j;
    }
    else {
        return -1;
    }
}

std::vector<int32_t> get_next(const std::string& pattern) {
    std::vector<int32_t> next;
    next.resize(pattern.size());

    next[0] = -1;
} 

int32_t string_search_kmp(const std::string& str, const std::string& pattern) {
    if (pattern.empty()) {
        return -1;
    }

    
}

int main() {

    return 0;
}

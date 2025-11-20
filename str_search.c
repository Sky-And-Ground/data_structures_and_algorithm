#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_search_bf(const char* str, const char* pattern);
int* kmp_get_next(const char* pattern, int patternLen);
int* kmp_get_nextval(const char* pattern, int patternLen);
int str_search_kmp(const char* str, const char* pattern);
int str_search_kmp_optimized(const char* str, const char* pattern);

int str_search_bf(const char* str, const char* pattern) {
    int strLen = strlen(str);
    int patternLen = strlen(pattern);
    int i = 0;
    int j = 0;

    while (i < strLen && j < patternLen) {
        if (str[i] == pattern[j]) {
            ++i;
            ++j;
        }
        else {
            j = 0;
            i = i - j + 1;
        }
    }

    if (j == patternLen) {
        return i - j;
    }
    else {
        return -1;
    }
}

int* kmp_get_next(const char* pattern, int patternLen) {
    int* next = (int*)malloc(patternLen * sizeof(int));

    if (next) {
        int i = -1;
        int j = 0;

        next[0] = -1;
        while (j < patternLen - 1) {
            if (i == -1 || pattern[i] == pattern[j]) {
                ++i;
                ++j;

                next[j] = i;
            }
            else {
                i = next[i];
            }
        }
    }

    return next;
}

int* kmp_get_nextval(const char* pattern, int patternLen) {
    int* next = kmp_get_next(pattern, patternLen);

    if (next) {
        int i, j;

        for (i = 0; i < patternLen; ++i) {
            j = next[i];

            if (pattern[i] == pattern[j]) {
                next[i] = next[j];
            }
        }
    }

    return next;
}

int str_search_kmp(const char* str, const char* pattern) {
    int strLen = strlen(str);
    int patternLen = strlen(pattern);
    int i = 0;
    int j = 0;

    int* next = kmp_get_next(pattern, patternLen);
    if (!next) {
        return -1;
    }

    while (i < strLen && j < patternLen) {
        if (j == -1 || str[i] == pattern[j]) {
            ++i;
            ++j;
        }
        else {
            j = next[j];
        }
    }

    free(next);

    if (j == patternLen) {
        return i - j;
    }
    else {
        return -1;
    }
}

int str_search_kmp_optimized(const char* str, const char* pattern) {
    int strLen = strlen(str);
    int patternLen = strlen(pattern);
    int i = 0;
    int j = 0;

    int* next = kmp_get_nextval(pattern, patternLen);
    if (!next) {
        return -1;
    }

    while (i < strLen && j < patternLen) {
        if (j == -1 || str[i] == pattern[j]) {
            ++i;
            ++j;
        }
        else {
            j = next[j];
        }
    }

    free(next);

    if (j == patternLen) {
        return i - j;
    }
    else {
        return -1;
    }
}

int main(void) {
    printf("%d\n", str_search_kmp_optimized("abcdefabcfgabcusb", "abcu"));
    return 0;
}

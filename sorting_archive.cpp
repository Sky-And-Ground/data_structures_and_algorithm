#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>
#include <cstdint>

void print_array(const std::vector<int>& view) {
    if (view.size() == 0) {
        std::cout << "[]\n";
        return;
    }

    std::cout << "[";

    size_t i;
    for (i = 0; i < view.size() - 1; ++i) {
        std::cout << view[i] << " ";   
    }

    std::cout << view[i] << "]\n";
}

void array_swap(std::vector<int>& vec, size_t i, size_t j) {
    std::swap(vec[i], vec[j]);
}

void bubble_sort(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        for (size_t j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                array_swap(vec, j, j + 1);
            }
        }
    }
}

void selection_sort(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        size_t min = i;

        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[j] < vec[min]) {
                min = j;
            }
        }

        if (min != i) {
            array_swap(vec, i, min);
        }
    }
}

void insert_sort(std::vector<int>& vec) {
    // do not use size_t here.
    int32_t len = static_cast<int32_t>(vec.size());

    for (int32_t i = 1; i < vec.size(); ++i) {
        int val = vec[i];
        int32_t j = i - 1;

        while (j >= 0 && vec[j] > val) {
            vec[j + 1] = vec[j];
            --j;
        }

        vec[j + 1] = val;
    }
}

void shell_sort(std::vector<int>& vec) {
    // do not use size_t here.
    int32_t len = static_cast<int32_t>(vec.size());
    int32_t gap = len / 2;

    while (gap > 0) {
        for (int32_t i = gap; i < vec.size(); ++i) {
            int val = vec[i];
            int32_t j = i - gap;

            while (j >= 0 && vec[j] > val) {
                vec[j + gap] = vec[j];
                j -= gap;
            }

            vec[j + gap] = val;
        }

        gap /= 2;
    }
}

class MergeSort {
    // split the partition into [l ... m] and [m + 1 ... r].
    void merge(std::vector<int>& vec, int32_t l, int32_t m, int32_t r) {
        int32_t leftLen = m - l + 1;
        int32_t rightLen = r - m;

        // temp array is needed.
        auto tempL = std::make_unique<int[]>(leftLen);
        auto tempR = std::make_unique<int[]>(rightLen);

        for (int32_t i = 0; i < leftLen; ++i) {
            tempL[i] = vec[i + l];
        }

        for (int32_t i = 0; i < rightLen; ++i) {
            tempR[i] = vec[i + m + 1];
        }

        int32_t i = 0;
        int32_t j = 0;
        int32_t k = l;

        while (i < leftLen && j < rightLen) {
            if (tempL[i] < tempR[j]) {
                vec[k] = tempL[i];

                ++i;
                ++k;
            }
            else {
                vec[k] = tempR[j];

                ++j;
                ++k;
            }
        }

        // if tempL remain elements, then insert them.
        // it's impossible for both tempL and tempR remain elements.
        while (i < leftLen) {
            vec[k] = tempL[i];

            ++i;
            ++k;
        }

        // if tempR remain elements, then insert them.
        while (j < rightLen) {
            vec[k] = tempR[j];

            ++j;
            ++k;
        }
    }

    void merge_sort(std::vector<int>& vec, int32_t l, int32_t r) {
        if (l < r) {
            int32_t m = l + (r - l) / 2;

            merge_sort(vec, l, m);
            merge_sort(vec, m + 1, r);
            merge(vec, l, m, r);
        }
    }
public:
    void operator()(std::vector<int>& vec) {
        if (vec.size() == 0) {
            return;
        }

        merge_sort(vec, 0, static_cast<int32_t>(vec.size()) - 1);
    }
};

class QuickSort {
    int32_t partition(std::vector<int>& vec, int32_t low, int32_t high) {
        // assmue we use the value at low as the pivot.
        int pivot = vec[low];

        while (low < high) {
            while (low < high && vec[high] >= pivot) {
                --high;
            }

            vec[low] = vec[high];

            while (low < high && vec[low] <= pivot) {
                ++low;
            }

            vec[high] = vec[low];
        }

        vec[low] = pivot;
        return low;
    }

    void quick_sort(std::vector<int>& vec, int32_t low, int32_t high) {
        if (low < high) {
            int32_t index = partition(vec, low, high);
            quick_sort(vec, low, index - 1);
            quick_sort(vec, index + 1, high);
        }
    }
public:
    void operator()(std::vector<int>& vec) {
        if (vec.size() == 0) {
            return;
        }

        quick_sort(vec, 0, static_cast<int32_t>(vec.size()) - 1);
    }
};

void counting_sort(std::vector<int>& vec) {
    if (vec.empty()) {
        return;
    }

    int max = vec[0];
    for (int i : vec) {
        if (i > max) {
            max = i;
        }
    }

    auto result = std::make_unique<int[]>(vec.size());
    auto appearance = std::make_unique<int[]>(max + 1);
    for (int i = 0; i < max + 1; ++i) {
        appearance[i] = 0;
    }

    for (int i = 0; i < vec.size(); ++i) {
        appearance[vec[i]] += 1;
    }

    for (int i = 1; i < max + 1; ++i) {
        appearance[i] += appearance[i - 1];
    }

    for (int i = max; i >= 0; --i) {
        result[appearance[vec[i]] - 1] = vec[i];
        appearance[vec[i]] -= 1;
    }

    for (int i = 0; i < vec.size(); ++i) {
        vec[i] = result[i];
    }
}

int main() {
    std::vector<int> vec = {
        3, 7, 5, 4, 1, 6, 9, 0, 2, 8
    };

    counting_sort(vec);
    print_array(vec);
    return 0;
}

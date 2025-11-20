#include <iostream>
#include <vector>
#include <cstdint>

class HeapSortDesc {
    void swap_2(std::vector<int>& vec, int i, int j) {
        int temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
    }

    void sift_down(std::vector<int>& vec, int32_t length, int index) {
        while (true) {
            int leftChild = index * 2 + 1;
            int rightChild = index * 2 + 2;
            int minIndex = index;

            if (leftChild < length && vec[leftChild] < vec[minIndex]) {
                minIndex = leftChild;
            }

            if (rightChild < length && vec[rightChild] < vec[minIndex]) {
                minIndex = rightChild;
            }

            if (minIndex == index) {
                break;
            }
            else {
                swap_2(vec, minIndex, index);
                index = minIndex;
            }
        }
    }

    void build_min_heap(std::vector<int>& vec) {
        int32_t len = (int32_t)vec.size();

        for (int32_t i = vec.size() / 2; i >= 0; --i) {
            sift_down(vec, len, i);
        }
    }
public:
    void sort(std::vector<int>& vec) {
        if (vec.empty()) {
            return;
        }

        build_min_heap(vec);

        int32_t len = (int32_t)vec.size();
        for (int32_t i = len - 1; i >= 0; --i) {
            swap_2(vec, 0, i);
            --len;
            sift_down(vec, len, 0);
        }
    }
};

class HeapSortAsc {
    void swap_2(std::vector<int>& vec, int i, int j) {
        int temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
    }

    void sift_down(std::vector<int>& vec, int32_t length, int index) {
        while (true) {
            int leftChild = index * 2 + 1;
            int rightChild = index * 2 + 2;
            int maxIndex = index;

            if (leftChild < length && vec[leftChild] > vec[maxIndex]) {
                maxIndex = leftChild;
            }

            if (rightChild < length && vec[rightChild] > vec[maxIndex]) {
                maxIndex = rightChild;
            }

            if (maxIndex == index) {
                break;
            }
            else {
                swap_2(vec, maxIndex, index);
                index = maxIndex;
            }
        }
    }

    void build_max_heap(std::vector<int>& vec) {
        int32_t len = (int32_t)vec.size();

        for (int32_t i = vec.size() / 2; i >= 0; --i) {
            sift_down(vec, len, i);
        }
    }
public:
    void sort(std::vector<int>& vec) {
        if (vec.empty()) {
            return;
        }

        build_max_heap(vec);

        int32_t len = (int32_t)vec.size();
        for (int32_t i = len - 1; i >= 0; --i) {
            swap_2(vec, 0, i);
            --len;
            sift_down(vec, len, 0);
        }
    }
};

void print_vec(const std::vector<int>& vec) {
    for (int i : vec) {
        std::cout << i << " ";
    }
    
    std::cout << "\n";
}

int main() {
    std::vector<int> vec = {
        5, 4, 7, 9, 8, 0, 1, 3, 2, 6
    };

    HeapSortAsc{}.sort(vec);
    print_vec(vec);
    return 0;
}

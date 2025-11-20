#include <iostream>
#include <array>
#include <vector>
#include <cstdint>

template<uint32_t N>
class TopBiggest {
    std::array<int, N> data;
    int len;

    void swap_2(int i, int j) {
        int temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    void sift_up(int index) {
        int parent = (index - 1) / 2;

        while (parent > 0 && data[parent] > data[index]) {
            swap_2(parent, index);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void sift_down(int index) {
        while (true) {
            int leftChild = index * 2 + 1;
            int rightChild = index * 2 + 2;
            int minIndex = index;

            if (leftChild < len && data[leftChild] < data[minIndex]) {
                minIndex = leftChild;
            }

            if (rightChild < len && data[rightChild] < data[minIndex]) {
                minIndex = rightChild;
            }

            if (minIndex == index) {
                break;
            }
            else {
                swap_2(minIndex, index);
                index = minIndex;
            }
        }
    }
public:
    TopBiggest() : len{ 0 } {}

    void push(int elem) {
        if (len < N) {
            data[len] = elem;
            sift_up(len);
            ++len;
        }
        else {
            if (elem > data[0]) {
                data[0] = elem;
                sift_down(0);
            }
        }
    }

    void print() {
        for (int i = 0; i < len; ++i) {
            std::cout << data[i] << " ";
        }

        std::cout << "\n";
    }
};

template<uint32_t N>
class TopSmallest {
    std::array<int, N> data;
    int len;

    void swap_2(int i, int j) {
        int temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    void sift_up(int index) {
        int parent = (index - 1) / 2;

        while (parent > 0 && data[parent] < data[index]) {
            swap_2(parent, index);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void sift_down(int index) {
        while (true) {
            int leftChild = index * 2 + 1;
            int rightChild = index * 2 + 2;
            int maxIndex = index;

            if (leftChild < len && data[leftChild] > data[maxIndex]) {
                maxIndex = leftChild;
            }

            if (rightChild < len && data[rightChild] > data[maxIndex]) {
                maxIndex = rightChild;
            }

            if (maxIndex == index) {
                break;
            }
            else {
                swap_2(maxIndex, index);
                index = maxIndex;
            }
        }
    }
public:
    TopSmallest() : len { 0 } {}

    void push(int elem) {
        if (len < N) {
            data[len] = elem;
            sift_up(len);
            ++len;
        }
        else {
            if (elem < data[0]) {
                data[0] = elem;
                sift_down(0);
            }
        }
    }

    void print() {
        for (int i = 0; i < len; ++i) {
            std::cout << data[i] << " ";
        }

        std::cout << "\n";
    }
};

int main() {
    std::vector<int> input = {
        39,  31,  27,  3, 16,
        29,  55, 103, 91, 27,
        33, 971, 111
    };

    TopSmallest<5> tb;

    for (int i : input) {
        tb.push(i);
    }

    tb.print();
    return 0;
}

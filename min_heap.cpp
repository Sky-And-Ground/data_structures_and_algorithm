#include <iostream>

template<int N>
class MinHeap {
    int data[N];
    int len;

    void swap_2(int i, int j);
    void sift_up(int i);
    void sift_down(int i);
public:
    MinHeap();

    bool is_full();
    bool is_empty();
    void push(int value);
    int pop();
};

template<int N>
MinHeap<N>::MinHeap() : len{ 0 } {}

template<int N>
void MinHeap<N>::swap_2(int i, int j) {
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

template<int N>
void MinHeap<N>::sift_up(int i) {
    int parent = (i - 1) / 2;

    while (i > 0 && data[parent] > data[i]) {
        swap_2(parent, i);
        i = parent;
        parent = (i - 1) / 2;
    }
}

template<int N>
void MinHeap<N>::sift_down(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int minIndex = i;

    if (left < len && data[left] < data[minIndex]) {
        minIndex = left;
    }

    if (right < len && data[right] < data[minIndex]) {
        minIndex = right;
    }

    if (minIndex != i) {
        swap_2(minIndex, i);
        sift_down(minIndex);
    }
}

template<int N>
bool MinHeap<N>::is_full() {
    return len == N;
}

template<int N>
bool MinHeap<N>::is_empty() {
    return len == 0;
}

template<int N>
void MinHeap<N>::push(int value) {
    data[len] = value;
    sift_up(len);
    ++len;
}

template<int N>
int MinHeap<N>::pop() {
    if (len == 1) {
        --len;
        return data[0];
    }
    else {
        int root = data[0];

        data[0] = data[len - 1];
        --len;
        sift_down(0);

        return root;
    }
}

int main() {
    MinHeap<5> heap;

    heap.push(57);
    heap.push(39);
    heap.push(21);
    heap.push(99);
    heap.push(16);

    while (!heap.is_empty()) {
        std::cout << heap.pop() << "\n";
    }

    return 0;
}

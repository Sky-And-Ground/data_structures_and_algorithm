#include <iostream>
#include <array>

using std::array;

template<auto N>
void array_swap_2(array<int, N>& arr, int i, int j);

template<auto N>
void array_print(const array<int, N>& arr);

template<auto N>
void bubble_sort(array<int, N>& arr);

template<auto N>
void selection_sort(array<int, N>& arr);

template<auto N>
void insert_sort(array<int, N>& arr);

template<auto N>
void shell_sort(array<int, N>& arr);

template<auto N>
int quick_sort_partition(array<int, N>& arr, int l, int r);

template<auto N>
void quick_sort_impl(array<int, N>& arr, int l, int r);

template<auto N>
void quick_sort(array<int, N>& arr);

template<auto N>
void merge_sort_merge(array<int, N>& arr, int l, int m, int r);

template<auto N>
void merge_sort_impl(array<int, N>& arr, int l, int r);

template<auto N>
void merge_sort(array<int, N>& arr);

// definitions.
template<auto N>
void array_swap_2(array<int, N>& arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

template<auto N>
void array_print(const array<int, N>& arr) {
    std::cout << "[";

    for (int i = 0; i < N - 1; ++i) {
        std::cout << arr[i] << ", ";
    }

    std::cout << arr[N - 1] << "]\n";
}

template<auto N>
void bubble_sort(array<int, N>& arr) {
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                array_swap_2(arr, j, j + 1);
            }
        }
    }
}

template<auto N>
void selection_sort(array<int, N>& arr) {
    for (int i = 0; i < N; ++i) {
        int minIndex = i;

        for (int j = minIndex + 1; j < N; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            array_swap_2(arr, minIndex, i);
        }
    }
}

template<auto N>
void insert_sort(array<int, N>& arr) {
    for (int i = 0; i < N; ++i) {
        int key = arr[i];

        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}

template<auto N>
void shell_sort(array<int, N>& arr) {

}

template<auto N>
int quick_sort_partition(array<int, N>& arr, int l, int r) {

}

template<auto N>
void quick_sort_impl(array<int, N>& arr, int l, int r) {

}

template<auto N>
void quick_sort(array<int, N>& arr) {

}

template<auto N>
void merge_sort_merge(array<int, N>& arr, int l, int m, int r) {

}

template<auto N>
void merge_sort_impl(array<int, N>& arr, int l, int r) {

}

template<auto N>
void merge_sort(array<int, N>& arr) {

}

int main() {
    array<int, 10> arr = {
        3, 9, 0, 1, 2, 8, 5, 6, 4, 7
    };

    insert_sort(arr);
    array_print(arr);
    return 0;
}
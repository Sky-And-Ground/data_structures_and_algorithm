#include <stdio.h>
#include <stddef.h>

int binary_search(int* arr, int size, int key) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] > key) {
            high = high - 1;
        }
        else if (arr[mid] < key) {
            low = mid + 1;
        }
        else {
            return mid;
        }
    }

    return -1;
}

int main(void) {
    int arr[] = {
        0, 2, 5, 7, 8, 10, 13, 15, 16, 19, 20
    };

    int index = binary_search(arr, sizeof(arr) / sizeof(arr[0]), 21);
    printf("%d\n", index);
    return 0;
}

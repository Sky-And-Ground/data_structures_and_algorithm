#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_AND_SIZE(arr) \
    arr, (sizeof(arr) / sizeof(arr[0]))

void arr_swap_2(int* arr, int i, int j);
void arr_print(int* arr, int len);

void bubble_sort(int* arr, int len);
void selection_sort(int* arr, int len);
void insert_sort(int* arr, int len);
void shell_sort(int* arr, int len);

int merge(int* arr, int l, int m, int r);
int merge_sort(int* arr, int l, int r);
int MERGE_SORT(int* arr, int len);

int partition(int* arr, int low, int high);
int quick_sort(int* arr, int low, int high);
int QUICK_SORT(int* arr, int len);

void heap_sift_down(int* arr, int len, int i);
void build_max_heap(int* arr, int len);
void heap_sort(int* arr, int len);

void arr_swap_2(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void arr_print(int* arr, int len) {
    int i;

    for (i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }

    putchar('\n');
}

void bubble_sort(int* arr, int len) {
    int i, j;

    for (i = 0; i < len - 1; ++i) {
        for (j = 0; j < len - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                arr_swap_2(arr, j, j + 1);
            }
        }
    }
}

void selection_sort(int* arr, int len) {
    int i, j, min;

    for (i = 0; i < len; ++i) {
        min = i;

        for (j = min + 1; j < len; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        if (min != i) {
            arr_swap_2(arr, i, min);
        }
    }
}

void insert_sort(int* arr, int len) {
    int i, j, key;

    for (i = 0; i < len; ++i) {
        key = arr[i];

        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}

void shell_sort(int* arr, int len) {
    int i, j, gap, key;

    for (gap = len / 2; gap >= 1; gap /= 2) {
        for (i = gap; i < len; ++i) {
            key = arr[i];

            j = i - gap;
            while (j >= 0 && arr[j] > key) {
                arr[j + gap] = arr[j];
                j -= gap;
            }

            arr[j + gap] = key;
        }
    }
}

int merge(int* arr, int l, int m, int r) {
    int leftLen, rightLen, i, j, k;
    int* tempL;
    int* tempR;

    leftLen = m - l + 1;
    rightLen = r - m;

    tempL = (int*)malloc((leftLen + rightLen) * sizeof(int));
    if (tempL == NULL) {
        return 0;
    }

    tempR = tempL + leftLen;

    memcpy(tempL, arr + l, leftLen * sizeof(int));
    memcpy(tempR, arr + m + 1, rightLen * sizeof(int));

    i = 0;
    j = 0;
    k = l;

    while (i < leftLen && j < rightLen) {
        if (tempL[i] < tempR[j]) {
            arr[k] = tempL[i];
            
            ++k;
            ++i;
        }
        else {
            arr[k] = tempR[j];

            ++k;
            ++j;
        }
    }

    while (i < leftLen) {
        arr[k] = tempL[i];

        ++k;
        ++i;
    }

    while (j < rightLen) {
        arr[k] = tempR[j];

        ++k;
        ++j;
    }

    free(tempL);
    return 1;
}

int merge_sort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        if (!merge_sort(arr, l, m)) {
            return 0;
        }

        if (!merge_sort(arr, m + 1, r)) {
            return 0;
        }

        if (!merge(arr, l, m, r)) {
            return 0;
        }
    }

    return 1;
}

int MERGE_SORT(int* arr, int len) {
    return merge_sort(arr, 0, len - 1);
}

int partition(int* arr, int low, int high) {
    int temp = low;

    while (low < high) {
        while (low < high && arr[low] <= arr[high]) {
            --high;
        }

        while (low < high && arr[low] <= arr[high]) {
            ++low;
        }

        arr_swap_2(arr, low, high);
    }

    arr_swap_2(arr, temp, low);
    return low;
}

int quick_sort(int* arr, int low, int high) {
    if (low < high) {
        int index = partition(arr, low, high);
        quick_sort(arr, low, index - 1);
        quick_sort(arr, index + 1, high);
    }
}

int QUICK_SORT(int* arr, int len) {
    return quick_sort(arr, 0, len - 1);
}

void heap_sift_down(int* arr, int len, int i) {
    while (1) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        int maxIndex = i;

        if (leftChild < len && arr[leftChild] > arr[maxIndex]) {
            maxIndex = leftChild;
        }

        if (rightChild < len && arr[rightChild] > arr[maxIndex]) {
            maxIndex = rightChild;
        }

        if (maxIndex == i) {
            return;
        }
        else {
            arr_swap_2(arr, maxIndex, i);
            i = maxIndex;
        }
    }
}

void build_max_heap(int* arr, int len) {
    int i;

    /* do sift down for every parent. */
    for (i = len / 2; i >= 0; --i) {
        heap_sift_down(arr, len, i);
    }
}

void heap_sort(int* arr, int len) {
    int i;

    build_max_heap(arr, len);

    /* begin from the last, swap it with the first, and decrease the length. */
    for (i = len - 1; i >= 0; --i) {
        arr_swap_2(arr, 0, i);
        --len;
        heap_sift_down(arr, len, 0);
    }
}

int main(void) {
    int arr[] = {
        9, 3, 7, 2, 0, 1, 8, 5, 6, 4
    };

    heap_sort(ARR_AND_SIZE(arr));
    arr_print(ARR_AND_SIZE(arr));
    return 0;
}

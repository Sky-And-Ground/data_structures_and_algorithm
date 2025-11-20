#include <stdio.h>

int group_search(int* block, int groupSize, int blockLength, int key) {
    int i;

    for (i = 0; i < blockLength; ++i) {
        if (block[i] >= key) {
            return i;
        }
    }

    return -1;
}

/*
    if block is: 4, 8, 25, 84, 121
    when find 2, then:

    low = 0, high = 4, mid = 2   =>   result = 2, high = 1
    low = 0, high = 1, mid = 0   =>   result = 0, high = 0
    low = 0, high = 0, mid = 0   =>   result = 0, high = -1

    break.
*/
int group_search_binary_search(int* block, int groupSize, int blockLength, int key) {
    int low = 0;
    int high = blockLength - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (block[mid] < key) {
            low = mid + 1;
        }
        else {
            /* 
                find the index position of the first element on the left side,
                which value is greater than or equal to key.
            */
            result = mid;
            high = mid - 1;
        }
    }

    return result;
}

int block_search(int* block, int groupSize, int blockLength, int* arr, int arrLength, int key) {
    int groupIndex = group_search_binary_search(block, groupSize, blockLength, key);

    if (groupIndex == -1) {
        return -1;
    }
    else {
        int i = groupIndex * groupSize;
        while (groupSize > 0) {
            if (arr[i] == key) {
                return i;
            }

            ++i;
            --groupSize;
        }

        return -1;
    }
}

int main(void) {
    /* 
        5 groups, every group has 4 elements. 
        block contains every group's biggest value.
    */
    int block[] = {
        4, 8, 25, 84, 121
    };

    int arr[] = {
         1,  2,  3,   4,   
         5,  6,  7,   8,  
         9, 13, 21,  25, 
        37, 45, 62,  84, 
        89, 90, 91, 121
    };

    int index = block_search(block, 4, sizeof(block) / sizeof(block[0]), arr, sizeof(arr) / sizeof(arr[0]), 1);
    printf("%d\n", index);
    return 0;
}

#include <stdio.h>

#define MIN_HEAP_CAPACITY   5

struct MinHeap {
    int data[MIN_HEAP_CAPACITY];
    int len;
};

void min_heap_swap2(struct MinHeap* heap, int i, int j);
void min_heap_init(struct MinHeap* heap);
void min_heap_sift_up(struct MinHeap* heap, int i);
void min_heap_sift_down(struct MinHeap* heap, int i);
void min_heap_push(struct MinHeap* heap, int value);
int min_heap_pop(struct MinHeap* heap);
int min_heap_is_full(struct MinHeap* heap);
int min_heap_is_empty(struct MinHeap* heap);

/* test case. */
void test_min_heap(void);

void min_heap_init(struct MinHeap* heap) {
    heap->len = 0;
}

void min_heap_swap2(struct MinHeap* heap, int i, int j) {
    int temp = heap->data[i];
    heap->data[i] = heap->data[j];
    heap->data[j] = temp;
}

int min_heap_is_full(struct MinHeap* heap) {
    return heap->len == MIN_HEAP_CAPACITY;
}

int min_heap_is_empty(struct MinHeap* heap) {
    return heap->len == 0;
}

void min_heap_sift_up(struct MinHeap* heap, int i) {
    int parent = (i - 1) / 2;

    while (i > 0 && heap->data[parent] > heap->data[i]) {
        min_heap_swap2(heap, parent, i);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void min_heap_sift_down(struct MinHeap* heap, int i) {
    int minIndex = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->len && heap->data[left] < heap->data[minIndex]) {
        minIndex = left;
    }

    if (right < heap->len && heap->data[right] < heap->data[minIndex]) {
        minIndex = right;
    }

    if (minIndex != i) {
        min_heap_swap2(heap, minIndex, i);
        min_heap_sift_down(heap, minIndex);
    }
}

void min_heap_push(struct MinHeap* heap, int value) {
    heap->data[heap->len] = value;
    heap->len += 1;
    min_heap_sift_up(heap, heap->len - 1);
}

int min_heap_pop(struct MinHeap* heap) {
    if (heap->len == 1) {
        heap->len -= 1;
        return heap->data[0];
    }
    else {
        int root = heap->data[0];

        heap->data[0] = heap->data[heap->len - 1];
        heap->len -= 1;
        min_heap_sift_down(heap, 0);

        return root;
    }
}

void test_min_heap(void) {
    struct MinHeap heap;
    
    min_heap_init(&heap);
    min_heap_push(&heap, 57);
    min_heap_push(&heap, 39);
    min_heap_push(&heap, 21);
    min_heap_push(&heap, 99);
    min_heap_push(&heap, 16);

    while (!min_heap_is_empty(&heap)) {
        printf("%d\n", min_heap_pop(&heap));
    }
}

int main(void) {
    test_min_heap();
    return 0;
}
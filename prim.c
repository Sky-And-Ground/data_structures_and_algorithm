#include <stdio.h>

#define MAX_DISTANCE_LIMIT   999999
#define VERTICE_NUM   6

struct Node {
    int vertex;
    int weight;
};

struct MinHeap {
    struct Node data[VERTICE_NUM];
    int len;
};

struct Graph {
    int adjacentMatrix[VERTICE_NUM][VERTICE_NUM];
    int edges;
};

/* min heap. */
void min_heap_swap2(struct MinHeap* heap, int i, int j);
void min_heap_init(struct MinHeap* heap);
void min_heap_sift_up(struct MinHeap* heap, int i);
void min_heap_sift_down(struct MinHeap* heap, int i);
void min_heap_push(struct MinHeap* heap, int vertex, int weight);
void min_heap_pop(struct MinHeap* heap, int* vertex);
int min_heap_is_full(struct MinHeap* heap);
int min_heap_is_empty(struct MinHeap* heap);

/* graph. */
void graph_init(struct Graph* g);
void graph_add_edge(struct Graph* g, int v, int w, int weight);
void graph_del_edge(struct Graph* g, int v, int w);
void prim(struct Graph* g);

/* test case. */
void test_prim(void);

void min_heap_swap2(struct MinHeap* heap, int i, int j) {
    struct Node temp = heap->data[i];
    heap->data[i] = heap->data[j];
    heap->data[j] = temp;
}

void min_heap_init(struct MinHeap* heap) {
    heap->len = 0;
}

void min_heap_sift_up(struct MinHeap* heap, int i) {
    int parent = (i - 1) / 2;

    while (i > 0 && heap->data[parent].weight > heap->data[i].weight) {
        min_heap_swap2(heap, i, parent);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void min_heap_sift_down(struct MinHeap* heap, int i) {
    int minIndex = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->len && heap->data[left].weight < heap->data[minIndex].weight) {
        minIndex = left;
    }

    if (right < heap->len && heap->data[right].weight < heap->data[minIndex].weight) {
        minIndex = right;
    }

    if (minIndex != i) {
        min_heap_swap2(heap, i, minIndex);
        min_heap_sift_down(heap, minIndex);
    }
}

void min_heap_push(struct MinHeap* heap, int vertex, int weight) {
    heap->data[heap->len].vertex = vertex;
    heap->data[heap->len].weight = weight;

    heap->len += 1;
    min_heap_sift_up(heap, heap->len - 1);
}

void min_heap_pop(struct MinHeap* heap, int* vertex) {
    *vertex = heap->data[0].vertex;

    if (heap->len == 1) {
        heap->len -= 1;
        return;
    }

    heap->data[0] = heap->data[heap->len - 1];
    heap->len -= 1;

    min_heap_sift_down(heap, 0);
}

int min_heap_is_full(struct MinHeap* heap) {
    return heap->len == VERTICE_NUM;
}

int min_heap_is_empty(struct MinHeap* heap) {
    return heap->len == 0;
}

void graph_init(struct Graph* g) {
    int i, j;

    for (i = 0; i < VERTICE_NUM; ++i) {
        for (j = 0; j < VERTICE_NUM; ++j) {
            g->adjacentMatrix[i][j] = 0;
        }
    }

    g->edges = 0;
}

void graph_add_edge(struct Graph* g, int v, int w, int weight) {
    g->adjacentMatrix[v][w] = weight;
    g->adjacentMatrix[w][v] = weight;
    g->edges += 1;
}

void graph_del_edge(struct Graph* g, int v, int w) {
    g->adjacentMatrix[v][w] = 0;
    g->adjacentMatrix[w][v] = 0;
    g->edges -= 1;
}

void prim(struct Graph* g) {
    struct MinHeap heap;
    int distances[VERTICE_NUM];
    int visited[VERTICE_NUM];
    int parent[VERTICE_NUM];
    int i, vertex, weight;

    /* init all things. */
    min_heap_init(&heap);

    for (i = 0; i < VERTICE_NUM; ++i) {
        distances[i] = MAX_DISTANCE_LIMIT;
        visited[i] = 0;
        parent[i] = -1;
    }

    distances[0] = 0;
    min_heap_push(&heap, 0, 0);

    /* extract every vertex. */
    while (!min_heap_is_empty(&heap)) {
        min_heap_pop(&heap, &vertex);
        visited[vertex] = 1;

        for (i = 0; i < VERTICE_NUM; ++i) {
            weight = g->adjacentMatrix[vertex][i];

            if (weight > 0 && !visited[i] && weight < distances[i]) {
                distances[i] = weight;
                parent[i] = vertex;
                min_heap_push(&heap, i, weight);
            }
        }
    }

    /* print the result. */
    for (i = 0; i < VERTICE_NUM; ++i) {
        if (parent[i] != -1) {
            printf("%d -> %d, distance: %d\n", parent[i], i, distances[i]);
        }
    }
}

void test_prim(void) {
    struct Graph g;

    graph_init(&g);
    graph_add_edge(&g, 0, 1, 6);
    graph_add_edge(&g, 0, 3, 5);
    graph_add_edge(&g, 0, 2, 1);
    graph_add_edge(&g, 1, 2, 5);
    graph_add_edge(&g, 1, 4, 3);
    graph_add_edge(&g, 3, 2, 4);
    graph_add_edge(&g, 3, 5, 2);
    graph_add_edge(&g, 2, 4, 6);
    graph_add_edge(&g, 2, 5, 4);
    graph_add_edge(&g, 4, 5, 6);

    prim(&g);
}

int main(void) {
    test_prim();
    return 0;
}

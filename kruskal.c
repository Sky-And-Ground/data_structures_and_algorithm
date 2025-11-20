#include <stdio.h>

#define VERTICE_NUM   5
#define MAX_EDGE_NUM  (VERTICE_NUM * (VERTICE_NUM - 1) / 2)

/* union find disjoint set. */
struct UFDS {
    int parent[VERTICE_NUM];
};

struct Edge {
    int begin;
    int end;
    int distance;
};

struct Edges {
    struct Edge data[MAX_EDGE_NUM];
    int len;
};

/* using union find disjoint set to check if some edge is already connected. */
void ufds_init(struct UFDS* ufds);
void ufds_union(struct UFDS* ufds, int x, int y);
int ufds_find(struct UFDS* ufds, int x);
int ufds_is_connected(struct UFDS* ufds, int x, int y);

/* sorting the edges, in ascend order. */
void quick_sort_swap2(struct Edge* data, int left, int right);
int quick_sort_partition(struct Edge* data, int l, int r);
void quick_sort_edges(struct Edge* data, int l, int r);
void sort_edges(struct Edges* edges);

/* edges operations. */
void edges_init(struct Edges* edges);
void edges_add(struct Edges* edges, int begin, int end, int distance);

/* do kruskal and get the total cost! */
int kruskal(struct Edges* edges);

/* test case. */
void test_kruskal(void);

void ufds_init(struct UFDS* ufds) {
    int i;

    for (i = 0; i < VERTICE_NUM; ++i) {
        ufds->parent[i] = -1;
    }
}

void ufds_union(struct UFDS* ufds, int x, int y) {
    int rootX = ufds_find(ufds, x);
    int rootY = ufds_find(ufds, y);

    if (rootX != rootY) {
        ufds->parent[rootX] = rootY;
    }
}

int ufds_find(struct UFDS* ufds, int x) {
    while (ufds->parent[x] != -1) {
        x = ufds->parent[x];
    }

    return x;
}

int ufds_is_connected(struct UFDS* ufds, int x, int y) {
    return ufds_find(ufds, x) == ufds_find(ufds, y);
}

void quick_sort_swap2(struct Edge* data, int left, int right) {
    struct Edge temp = data[left];
    data[left] = data[right];
    data[right] = temp;
}

int quick_sort_partition(struct Edge* data, int l, int r) {
    int index = l;

    while (l < r) {
        while (l < r && data[l].distance <= data[r].distance) {
            --r;
        }

        while (l < r && data[l].distance <= data[r].distance) {
            ++l;
        }

        quick_sort_swap2(data, l, r);
    }

    quick_sort_swap2(data, index, l);
    return l;
}

void quick_sort_edges(struct Edge* data, int l, int r) {
    if (l < r) {
        int index = quick_sort_partition(data, l, r);
        quick_sort_edges(data, l, index - 1);
        quick_sort_edges(data, index + 1, r);
    }
}

void sort_edges(struct Edges* edges) {
    quick_sort_edges(edges->data, 0, edges->len - 1);
}

void edges_init(struct Edges* edges) {
    edges->len = 0;
}

void edges_add(struct Edges* edges, int begin, int end, int distance) {
    struct Edge* edge = &(edges->data[edges->len]);

    edge->begin = begin;
    edge->end = end;
    edge->distance = distance;

    edges->len += 1;
}

int kruskal(struct Edges* edges) {
    struct UFDS ufds;
    struct Edge* edge;
    int totalCost = 0;
    int counter = 0;
    int i;

    ufds_init(&ufds);
    sort_edges(edges);

    for (i = 0; i < edges->len; ++i) {
        edge = &(edges->data[i]);

        if (!ufds_is_connected(&ufds, edge->begin, edge->end)) {
            printf("%d -> %d, distance: %d\n", edge->begin, edge->end, edge->distance);

            ufds_union(&ufds, edge->begin, edge->end);
            totalCost += edge->distance;
            ++counter;

            if (counter == VERTICE_NUM - 1) {
                break;
            }
        }
    }

    return totalCost;
}

void test_kruskal(void) {
    struct Edges edges;
    int totalCost = 0;

    edges_init(&edges);
    edges_add(&edges, 0, 1, 10);
    edges_add(&edges, 1, 3, 15);
    edges_add(&edges, 2, 3, 4);
    edges_add(&edges, 2, 0, 6);
    edges_add(&edges, 0, 3, 5);
    edges_add(&edges, 3, 4, 2);

    totalCost = kruskal(&edges);
    printf("\ntotal cost is %d\n", totalCost);
}

int main(void) {
    test_kruskal();
    return 0;
}

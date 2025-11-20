#include <stdio.h>

#define VERTICE_NUM   5

/* union find disjoint set. */
struct UFDS {
    int parent[VERTICE_NUM];
};

void ufds_init(struct UFDS* ufds);
void ufds_union(struct UFDS* ufds, int x, int y);
int ufds_find(struct UFDS* ufds, int x);
int ufds_is_connected(struct UFDS* ufds, int x, int y);

/* test case. */
void test_ufds_connected(void);
void test_detect_cycle(void);

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

void test_ufds_connected(void) {
    struct UFDS ufds;
    ufds_init(&ufds);

    ufds_union(&ufds, 0, 3);
    ufds_union(&ufds, 1, 2);

    printf("conncected: %d\n", ufds_is_connected(&ufds, 3, 2));
    printf("conncected: %d\n", ufds_is_connected(&ufds, 0, 1));
    printf("conncected: %d\n", ufds_is_connected(&ufds, 1, 2));
}

void test_detect_cycle(void) {
    struct UFDS ufds;
    int start[] = { 0, 1, 2, 3, 4 };
    int end[] = { 1, 2, 3, 4, 0 };
    int i;

    ufds_init(&ufds);

    for (i = 0; i < sizeof(start) / sizeof(int); ++i) {
        if (ufds_is_connected(&ufds, start[i], end[i])) {
            printf("detect cycle: %d -> %d\n", start[i], end[i]);
        }
        else {
            ufds_union(&ufds, start[i], end[i]);
        }
    }
}

int main(void) {
    test_detect_cycle();
    return 0;
}

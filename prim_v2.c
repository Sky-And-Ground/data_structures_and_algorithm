#include <stdio.h>
#include <assert.h>

#define MAX_DISTANCE_LIMIT   999999
#define VERTICE_NUM   6

struct Graph {
    int adjacentMatrix[VERTICE_NUM][VERTICE_NUM];
    int edges;
};

/* graph. */
void graph_init(struct Graph* g);
void graph_add_edge(struct Graph* g, int v, int w, int weight);

/* prim. */
int get_min_distance_vertex(int* distances, int* visited);
void prim(struct Graph* g);
void print_mst(struct Graph* g, int* parent);

/* test case. */
void test_prim(void);

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
    assert(v >= 0 && v < VERTICE_NUM);
    assert(w >= 0 && w < VERTICE_NUM);
    assert(weight >= 0 && weight < MAX_DISTANCE_LIMIT);

    g->adjacentMatrix[v][w] = weight;
    g->adjacentMatrix[w][v] = weight;
    g->edges += 1;
}

int get_min_distance_vertex(int* distances, int* visited) {
    int minDistance = MAX_DISTANCE_LIMIT;
    int minIndex = 0;
    int i;

    for (i = 0; i < VERTICE_NUM; ++i) {
        if (!visited[i] && distances[i] < minDistance) {
            minIndex = i;
            minDistance = distances[i];
        }
    }

    return minIndex;
}

void prim(struct Graph* g) {
    int distances[VERTICE_NUM];
    int visited[VERTICE_NUM];
    int parent[VERTICE_NUM];
    int i, minVertex, distance, counter;

    for (i = 0; i < VERTICE_NUM; ++i) {
        distances[i] = MAX_DISTANCE_LIMIT;
        visited[i] = 0;
        parent[i] = -1;
    }

    distances[0] = 0;
    parent[0] = -1;

    for (counter = 0; counter < VERTICE_NUM - 1; ++counter) {
        minVertex = get_min_distance_vertex(distances, visited);
        visited[minVertex] = 1;

        for (i = 0; i < VERTICE_NUM; ++i) {
            distance = g->adjacentMatrix[minVertex][i];

            if (distance > 0 && !visited[i] && distance < distances[i]) {
                parent[i] = minVertex;
                distances[i] = distance;
            }
        }
    }

    print_mst(g, parent);
}

void print_mst(struct Graph* g, int* parent) {
    int i, start, end;

    for (i = 0; i < VERTICE_NUM; ++i) {
        if (parent[i] != -1) {
            start = parent[i];
            end = i;

            printf("%d -> %d, distance: %d\n", start, end, g->adjacentMatrix[start][end]);
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

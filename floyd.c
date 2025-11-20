#include <stdio.h>

#define MAX_DISTANCE_LIMIT   999999
#define V   4

/* directed graph. */
void graph_init(int graph[V][V]);
void graph_add_edge(int graph[V][V], int src, int dst, int distance);
void floyd_warshall(int graph[V][V]);
void print_path(int path[V][V], int i, int j);

void graph_init(int graph[V][V]) {
    int i, j;

    for (i = 0; i < V; ++i) {
        for (j = 0; j < V; ++j) {
            if (i == j) {
                graph[i][j] = 0;
            }
            else {
                graph[i][j] = MAX_DISTANCE_LIMIT;
            }
        }
    }
}

void graph_add_edge(int graph[V][V], int src, int dst, int distance) {
    graph[src][dst] = distance;
}

void floyd_warshall(int graph[V][V]) {
    int i, j, k;
    int path[V][V];

    for (i = 0; i < V; ++i) {
        for (j = 0; j < V; ++j) {
            if (i == j) {
                path[i][j] = 0;
            }
            else if (i != j && graph[i][j] != MAX_DISTANCE_LIMIT) {
                path[i][j] = j;
            }
            else {
                path[i][j] = -1;
            }
        }
    }

    for (k = 0; k < V; ++k) {
        for (i = 0; i < V; ++i) {
            for (j = 0; j < V; ++j) {
                if (graph[i][k] != MAX_DISTANCE_LIMIT && graph[k][j] != MAX_DISTANCE_LIMIT && graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }

    printf("shortest path matrix:\n");
    for (i = 0; i < V; ++i) {
        for (j = 0; j < V; ++j) {
            if (graph[i][j] == MAX_DISTANCE_LIMIT) {
                printf(" oo ");
            }
            else {
                printf("%3d ", graph[i][j]);
            }
        }

        printf("\n");
    }

    printf("\nshortest path:\n");
    for (i = 0; i < V; ++i) {
        for (j = 0; j < V; ++j) {
            if (i != j && graph[i][j] != MAX_DISTANCE_LIMIT) {
                print_path(path, i, j);
            }
        }
    }
}

void print_path(int path[V][V], int i, int j) {
    if (path[i][j] == -1) {
        printf("%d -> %d, no road\n", i, j);
        return;
    }
    else {
        int current = i;

        printf("%d -> %d   [%d", i, j, current);
        while (current != j) {
            current = path[current][j];
            printf(" -> %d", current);
        }

        printf("]\n");
    }
}

int main(void) {
    int graph[V][V];

    graph_init(graph);
    graph_add_edge(graph, 0, 1, 5);
    graph_add_edge(graph, 1, 2, 3);
    graph_add_edge(graph, 2, 3, 1);
    graph_add_edge(graph, 0, 3, 10);

    floyd_warshall(graph);
    return 0;
}

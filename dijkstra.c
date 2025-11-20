#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_DISTANCE_LIMIT   999999
#define V 7

/* undirected graph. */
void graph_init(int graph[V][V]);
void graph_add_edge(int graph[V][V], int src, int dst, int distance);
int get_min_distance_vertex(int* distances, int* visited);
void dijkstra(int graph[V][V], int src);
void print_solution(int src, int* distances, int* parent);

/* test cases. */
void test_case_1(void);

void graph_init(int graph[V][V]) {
    memset(graph, 0, V * V * sizeof(int));
}

void graph_add_edge(int graph[V][V], int src, int dst, int distance) {
    assert(src >= 0 && src < V);
    assert(dst >= 0 && dst < V);
    assert(distance >= 0 && distance < MAX_DISTANCE_LIMIT);

    graph[src][dst] = distance;
    graph[dst][src] = distance;
}

int get_min_distance_vertex(int* distances, int* visited) {
    int minDistance = MAX_DISTANCE_LIMIT;
    int minIndex = 0;
    int i;

    for (i = 0; i < V; ++i) {
        if (!visited[i] && distances[i] <= minDistance) {
            minDistance = distances[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void dijkstra(int graph[V][V], int src) {
    int distances[V];
    int visited[V];
    int parent[V];
    int i, counter, minVertex;

    for (i = 0; i < V; ++i) {
        distances[i] = MAX_DISTANCE_LIMIT;
        visited[i] = 0;
        parent[i] = -1;
    }

    /* self to self is 0. */
    distances[src] = 0;

    for (counter = 0; counter < V - 1; ++counter) {
        minVertex = get_min_distance_vertex(distances, visited);
        visited[minVertex] = 1;

        for (i = 0; i < V; ++i) {
            if (!visited[i] && graph[minVertex][i] > 0 && distances[minVertex] != MAX_DISTANCE_LIMIT && distances[minVertex] + graph[minVertex][i] < distances[i]) {
                distances[i] = distances[minVertex] + graph[minVertex][i];
                parent[i] = minVertex;
            }
        }
    }

    print_solution(src, distances, parent);
}

void print_solution(int src, int* distances, int* parent) {
    int i, j;

    for (i = 0; i < V; ++i) {
        if (i == src) {
            continue;
        }

        printf("%d -> %d, the shortest path distance is %d\n", src, i, distances[i]);
        printf("path is: ");

        j = i;
        printf("%d", j);
        while (parent[j] != -1) {
            printf(" <- %d", parent[j]);
            j = parent[j];
        }

        printf("\n\n");
    }
}

void test_case_1(void) {
    int graph[V][V];

    graph_init(graph);
    graph_add_edge(graph, 0, 1, 4);
    graph_add_edge(graph, 0, 2, 6);
    graph_add_edge(graph, 0, 3, 6);
    graph_add_edge(graph, 1, 2, 1);
    graph_add_edge(graph, 1, 4, 7);
    graph_add_edge(graph, 3, 2, 2);
    graph_add_edge(graph, 3, 5, 5);
    graph_add_edge(graph, 2, 4, 6);
    graph_add_edge(graph, 2, 5, 4);
    graph_add_edge(graph, 5, 4, 1);
    graph_add_edge(graph, 5, 6, 8);
    graph_add_edge(graph, 4, 6, 6);

    dijkstra(graph, 3);
}

int main(void) {
    test_case_1();
    return 0;
}

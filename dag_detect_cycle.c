#include <stdio.h>
#include <string.h>

#define V  4

/* directed graph. */
void graph_init(int graph[V][V]);
void graph_add_edge(int graph[V][V], int src, int dst);
int graph_detect_cycle(int graph[V][V]);

/* test case. */
void test_graph_cycle(void);

void graph_init(int graph[V][V]) {
    memset(graph, 0, V * V * sizeof(int));
}

void graph_add_edge(int graph[V][V], int src, int dst) {
    graph[src][dst] = 1;
}

int graph_detect_cycle(int graph[V][V]) {
    int inDegree[V];
    int queue[V];
    int i, j, counter, front, rear;

    /* initialize the in degree array. */
    memset(inDegree, 0, V * sizeof(int));
    
    for (i = 0; i < V; ++i) {
        for (j = 0; j < V; ++j) {
            if (graph[i][j] == 1) {
                inDegree[j] += 1;
            }
        }
    }

    /* collect vertex which in degree is 0. */
    front = rear = 0;
    for (i = 0; i < V; ++i) {
        if (inDegree[i] == 0) {
            queue[rear] = i;
            ++rear;
        }
    }

    counter = 0;
    while (front != rear) {
        i = queue[front];
        
        ++front;
        ++counter;

        for (j = 0; j < V; ++j) {
            if (graph[i][j] == 1) {
                inDegree[j] -= 1;

                if (inDegree[j] == 0) {
                    queue[rear] = j;
                    ++rear;
                }
            }
        }
    }

    return counter != V;
}

void test_graph_cycle(void) {
    int graph[V][V];

    graph_init(graph);
    graph_add_edge(graph, 0, 1);
    graph_add_edge(graph, 1, 2);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 3, 0);

    printf("graph cycle: %s\n", graph_detect_cycle(graph) ? "yes" : "no");
}

int main(void) {
    test_graph_cycle();
    return 0;
}

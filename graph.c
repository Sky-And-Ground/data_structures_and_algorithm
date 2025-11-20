#include <stdio.h>

#define VERTICE_NUM   5

/* undirected graph. */
struct Graph {
    int adjacentMatrix[VERTICE_NUM][VERTICE_NUM];
    int edges;
};

void graph_init(struct Graph* g);
void graph_add_edge(struct Graph* g, int v, int w);
void graph_del_edge(struct Graph* g, int v, int w);
void graph_bfs(struct Graph* g, int start);
void graph_dfs_impl(struct Graph* g, int* visited, int i);
void graph_dfs(struct Graph* g);

/* test cases. */
void test_graph_bfs(void);
void test_graph_dfs(void);

void graph_init(struct Graph* g) {
    int i, j;

    for (i = 0; i < VERTICE_NUM; ++i) {
        for (j = 0; j < VERTICE_NUM; ++j) {
            g->adjacentMatrix[i][j] = 0;
        }
    }

    g->edges = 0;
}

void graph_add_edge(struct Graph* g, int v, int w) {
    g->adjacentMatrix[v][w] = 1;
    g->adjacentMatrix[w][v] = 1;
    g->edges += 1;
}

void graph_del_edge(struct Graph* g, int v, int w) {
    g->adjacentMatrix[v][w] = 0;
    g->adjacentMatrix[w][v] = 0;
    g->edges -= 1;
}

void graph_bfs(struct Graph* g, int start) {
    int i, v, front, rear;
    int visited[VERTICE_NUM];
    int queue[VERTICE_NUM];

    for (i = 0; i < VERTICE_NUM; ++i) {
        visited[i] = 0;
    }

    front = rear = 0;
    queue[rear] = start;
    visited[start] = 1;
    ++rear;

    while (front != rear) {
        v = queue[front];
        ++front;
        printf("%d\n", v);

        for (i = 0; i < VERTICE_NUM; ++i) {
            if (g->adjacentMatrix[v][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear] = i;
                ++rear;
            }
        }
    }
}

void graph_dfs_impl(struct Graph* g, int* visited, int i) {
    int j;

    printf("%d\n", i);
    visited[i] = 1;

    for (j = 0; j < VERTICE_NUM; ++j) {
        if (g->adjacentMatrix[i][j] == 1 && !visited[j]) {
            graph_dfs_impl(g, visited, j);
        }
    }
}

void graph_dfs(struct Graph* g) {
    int visited[VERTICE_NUM];
    int i;

    for (i = 0; i < VERTICE_NUM; ++i) {
        visited[i] = 0;
    }

    for (i = 0; i < VERTICE_NUM; ++i) {
        if (!visited[i]) {
            graph_dfs_impl(g, visited, i);
        }
    }
}

void test_graph_bfs(void) {
    struct Graph g;
    graph_init(&g);

    graph_add_edge(&g, 0, 3);
    graph_add_edge(&g, 0, 4);
    graph_add_edge(&g, 0, 1);
    graph_add_edge(&g, 4, 2);
    graph_add_edge(&g, 3, 4);

    graph_bfs(&g, 0);
}

void test_graph_dfs(void) {
    struct Graph g;
    graph_init(&g);

    graph_add_edge(&g, 0, 3);
    graph_add_edge(&g, 3, 1);
    graph_add_edge(&g, 2, 4);
    graph_add_edge(&g, 1, 4);

    graph_dfs(&g);
}

int main(void) {
    test_graph_dfs();
    return 0;
}

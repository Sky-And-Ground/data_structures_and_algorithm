#include <iostream>
#include <queue>
#include <array>

// undirected graph.
template<int V>
class Graph {
    std::array<std::array<int, V>, V> adjacentMatrix;

    void dfs_impl(std::array<bool, V>& visited, int i);
public:
    Graph();
    void add_edge(int src, int dst);
    void del_edge(int src, int dst);
    void bfs(int start);
    void dfs();
};

template<int V>
Graph<V>::Graph() {
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            adjacentMatrix[i][j] = 0;
        }
    }
}

template<int V>
void Graph<V>::add_edge(int src, int dst) {
    adjacentMatrix[src][dst] = 1;
    adjacentMatrix[dst][src] = 1;
}

template<int V>
void Graph<V>::del_edge(int src, int dst) {
    adjacentMatrix[src][dst] = 0;
    adjacentMatrix[dst][src] = 0;
}

template<int V>
void Graph<V>::bfs(int start) {
    std::array<bool, V> visited;
    std::queue<int> q;

    visited.fill(false);

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        std::cout << vertex << "\n";

        for (int i = 0; i < V; ++i) {
            if (adjacentMatrix[vertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

template<int V>
void Graph<V>::dfs_impl(std::array<bool, V>& visited, int i) {
    std::cout << i << "\n";
    visited[i] = true;

    for (int j = 0; j < V; ++j) {
        if (adjacentMatrix[i][j] == 1 && !visited[j]) {
            dfs_impl(visited, j);
        }
    }
}

template<int V>
void Graph<V>::dfs() {
    std::array<bool, V> visited;
    visited.fill(false);

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfs_impl(visited, i);
        }
    }
}

int main() {
    Graph<5> g;

    g.add_edge(0, 3);
    g.add_edge(0, 4);
    g.add_edge(0, 1);
    g.add_edge(4, 2);
    g.add_edge(3, 4);

    g.dfs();
    return 0;
}

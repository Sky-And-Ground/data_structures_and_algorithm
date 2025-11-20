#include <iostream>
#include <iomanip>
#include <array>

using std::array;

// directed graph.
template<int V>
class Graph {
    static constexpr int max_distance = 999999;
    array<array<int, V>, V> adjacentMatrix;

    void print_distance_matrix();
    void print_every_vertex_shortest_path(const array<array<int, V>, V>& path);
    void print_path(const array<array<int, V>, V>& path, int i, int j);
public:
    Graph();

    void add_edge(int src, int dst, int distance);
    void floyd_warshall();
};

template<int V>
Graph<V>::Graph() {
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i == j) {
                adjacentMatrix[i][j] = 0;
            }
            else {
                adjacentMatrix[i][j] = max_distance;
            }
        }
    }
}

template<int V>
void Graph<V>::add_edge(int src, int dst, int distance) {
    adjacentMatrix[src][dst] = distance;
}

template<int V>
void Graph<V>::floyd_warshall() {
    array<array<int, V>, V> path;

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i == j) {
                path[i][j] = 0;   // self to self is 0.
            }
            else if (i != j && adjacentMatrix[i][j] != max_distance) {
                path[i][j] = j;   // has road.
            }
            else {
                path[i][j] = -1;  // no road.
            }
        }
    }

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (adjacentMatrix[i][k] != max_distance && 
                    adjacentMatrix[k][j] != max_distance && 
                    adjacentMatrix[i][k] + adjacentMatrix[k][j] < adjacentMatrix[i][j]
                ) {
                    adjacentMatrix[i][j] = adjacentMatrix[i][k] + adjacentMatrix[k][j];
                    path[i][j] = path[i][k];   // k as transit point.
                }
            }
        }
    }

    print_distance_matrix();
    print_every_vertex_shortest_path(path);
}

template<int V>
void Graph<V>::print_distance_matrix() {
    std::cout << "distance matrix:\n";

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (adjacentMatrix[i][j] == max_distance) {
                std::cout << " oo ";
            }
            else {
                std::cout << std::setw(3) << adjacentMatrix[i][j] << " ";
            }
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}

template<int V>
void Graph<V>::print_every_vertex_shortest_path(const array<array<int, V>, V>& path) {
    std::cout << "shortest path:\n";

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j && adjacentMatrix[i][j] != max_distance) {
                print_path(path, i, j);
            }
        }
    }
}

template<int V>
void Graph<V>::print_path(const array<array<int, V>, V>& path, int i, int j) {
    if (path[i][j] == -1) {
        std::cout << i << " -> " << j << ", no road\n";
        return;
    }

    int current = i;
    std::cout << i << " -> " << j << "   [" << current;
    
    while (current != j) {
        current = path[current][j];
        std::cout << " -> " << current;
    }

    std::cout << "]\n";
}

int main() {
    Graph<4> g;

    g.add_edge(0, 1, 5);
    g.add_edge(1, 2, 3);
    g.add_edge(2, 3, 1);
    g.add_edge(0, 3, 10);

    g.floyd_warshall();
    return 0;
}
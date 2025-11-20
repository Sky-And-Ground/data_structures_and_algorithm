#include <iostream>
#include <array>

using std::array;

// undirected graph.
template<int V>
class Graph {
    static constexpr int max_distance = 999999;
    std::array<std::array<int, V>, V> adjacentMatrix;

    int get_min_distance_vertex(const array<int, V>& distances, const array<bool, V>& visited);
    void print_mst(const array<int, V>& parent);
public:
    Graph();

    void add_edge(int src, int dst, int distance);
    void prim();
};

template<int V>
Graph<V>::Graph() {
    for (auto& line : adjacentMatrix) {
        line.fill(0);
    }
}

template<int V>
void Graph<V>::add_edge(int src, int dst, int distance) {
    adjacentMatrix[src][dst] = distance;
    adjacentMatrix[dst][src] = distance;
}

template<int V>
int Graph<V>::get_min_distance_vertex(const array<int, V>& distances, const array<bool, V>& visited) {
    int minVertex = 0;
    int minDistance = max_distance;

    for (int i = 0; i < V; ++i) {
        if (!visited[i] && distances[i] < minDistance) {
            minDistance = distances[i];
            minVertex = i;
        }
    }

    return minVertex;
}

template<int V>
void Graph<V>::prim() {
    array<int, V> distances;
    array<int, V> parent;
    array<bool, V> visited;

    distances.fill(max_distance);
    parent.fill(-1);
    visited.fill(false);

    distances[0] = 0;

    for (int counter = 0; counter < V - 1; ++counter) {
        int minVertex = get_min_distance_vertex(distances, visited);
        visited[minVertex] = true;

        for (int i = 0; i < V; ++i) {
            int distance = adjacentMatrix[minVertex][i];

            if (!visited[i] && distance > 0 && distance < distances[i]) {
                parent[i] = minVertex;
                distances[i] = distance;
            }
        }
    }

    print_mst(parent);
}

template<int V>
void Graph<V>::print_mst(const array<int, V>& parent) {
    for (int i = 0; i < V; ++i) {
        if (parent[i] != -1) {
            int start = parent[i];
            
            std::cout << start << " -> " << i << ", distance is " << adjacentMatrix[start][i] << "\n";
        }
    }
}

int main() {
    Graph<6> g;

    g.add_edge(0, 1, 6);
    g.add_edge(0, 3, 5);
    g.add_edge(0, 2, 1);
    g.add_edge(1, 2, 5);
    g.add_edge(1, 4, 3);
    g.add_edge(3, 2, 4);
    g.add_edge(3, 5, 2);
    g.add_edge(2, 4, 6);
    g.add_edge(2, 5, 4);
    g.add_edge(4, 5, 6);

    g.prim();
    return 0;
}
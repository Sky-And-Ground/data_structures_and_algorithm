#include <iostream>
#include <array>

using std::array;

// undirected graph.
template<int V>
class Graph {
    static constexpr int max_distance = 999999;
    array<array<int, V>, V> adjacentMatrix;

    int get_min_distance_vertex(const array<bool, V>& visited, const array<int, V>& distances);
    void print_solution(int src, const array<int, V>& distances, const array<int, V>& parent);
public:
    Graph();
    void add_edge(int src, int dst, int distance);
    void dijkstra(int src);
};

template<int V>
Graph<V>::Graph() {
    for (auto& line : adjacentMatrix) {
        line.fill(0);
    }
}

template<int V>
int Graph<V>::get_min_distance_vertex(const array<bool, V>& visited, const array<int, V>& distances) {
    int minVertex = 0;
    int minDistance = max_distance;

    for (int i = 0; i < V; ++i) {
        if (!visited[i] && distances[i] < minDistance) {
            minVertex = i;
            minDistance = distances[i];
        }
    }

    return minVertex;
}

template<int V>
void Graph<V>::print_solution(int src, const array<int, V>& distances, const array<int, V>& parent) {
    for (int i = 0; i < V; ++i) {
        if (i == src) {
            continue;;
        }

        std::cout << src << " -> " << i << ", the shortes path distance is " << distances[i] << "\n";
        std::cout << "path is: ";

        int j = i;
        std::cout << j;

        while (parent[j] != -1) {
            std::cout << " <- " << parent[j];
            j = parent[j];
        }

        std::cout << "\n\n";
    }
}

template<int V>
void Graph<V>::add_edge(int src, int dst, int distance) {
    adjacentMatrix[src][dst] = distance;
    adjacentMatrix[dst][src] = distance;
}

template<int V>
void Graph<V>::dijkstra(int src) {
    array<int, V> distances;
    array<int, V> parent;
    array<bool, V> visited;

    distances.fill(max_distance);
    parent.fill(-1);
    visited.fill(false);

    distances[src] = 0;   // self to self is 0.

    for (int counter = 0; counter < V - 1; ++counter) {
        int minVertex = get_min_distance_vertex(visited, distances);
        visited[minVertex] = true;

        if (distances[minVertex] != max_distance) {
            for (int i = 0; i < V; ++i) {
                if (!visited[i] && adjacentMatrix[minVertex][i] > 0 && distances[minVertex] + adjacentMatrix[minVertex][i] < distances[i]) {
                    distances[i] = distances[minVertex] + adjacentMatrix[minVertex][i];
                    parent[i] = minVertex;
                }
            }
        }
    }

    print_solution(src, distances, parent);
}

int main() {
    Graph<7> g;

    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 6);
    g.add_edge(0, 3, 6);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 4, 7);
    g.add_edge(3, 2, 2);
    g.add_edge(3, 5, 5);
    g.add_edge(2, 4, 6);
    g.add_edge(2, 5, 4);
    g.add_edge(5, 4, 1);
    g.add_edge(5, 6, 8);
    g.add_edge(4, 6, 6);

    g.dijkstra(0);
    return 0;
}
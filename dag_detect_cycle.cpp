#include <iostream>
#include <queue>
#include <array>

// directed graph.
template<int V>
class Graph {
    std::array<std::array<int, V>, V> adjacentMatrix;
public:
    Graph();
    void add_edge(int src, int dst);
    bool detect_cycle();
};

template<int V>
Graph<V>::Graph() {
    for (auto& line : adjacentMatrix) {
        line.fill(0);
    }
}

template<int V>
void Graph<V>::add_edge(int src, int dst) {
    adjacentMatrix[src][dst] = 1;
}

template<int V>
bool Graph<V>::detect_cycle() {
    std::array<int, V> inDegree;
    std::queue<int> q;

    inDegree.fill(0);
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            inDegree[j] += 1;
        }
    }

    for (int i = 0; i < V; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    int counter = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ++counter;

        for (int i = 0; i < V; ++i) {
            if (adjacentMatrix[v][i] == 1) {
                inDegree[i] -= 1;

                if (inDegree[i] == 0) {
                    q.push(i);
                }
            }
        }
    }

    return counter != V;
}

int main() {
    Graph<4> g;

    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 0);

    std::cout << g.detect_cycle() << "\n";
    return 0;
}
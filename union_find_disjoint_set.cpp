#include <iostream>
#include <array>

template<int V>
class UFDS {
    std::array<int, V> parent;

    int find_parent(int x);
public:
    UFDS();

    void unite(int x, int y);
    bool is_connected(int x, int y);
};

struct Edge {
    int src;
    int dst;

    explicit Edge(int _src, int _dst) : src{ _src }, dst{ _dst } {}
};

template<int V>
bool detect_cycle(const std::array<Edge, V>& edges);

// definitions.
template<int V>
UFDS<V>::UFDS() {
    parent.fill(-1);
}

template<int V>
int UFDS<V>::find_parent(int x) {
    while (parent[x] != -1) {
        x = parent[x];
    }

    return x;
}

template<int V>
void UFDS<V>::unite(int x, int y) {
    int rootX = find_parent(x);
    int rootY = find_parent(y);

    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

template<int V>
bool UFDS<V>::is_connected(int x, int y) {
    return find_parent(x) == find_parent(y);
}

template<auto V>
bool detect_cycle(const std::array<Edge, V>& edges) {
    UFDS<V> ufds;

    for (const Edge& edge : edges) {
        if (ufds.is_connected(edge.src, edge.dst)) {
            return true;
        }
        else {
            ufds.unite(edge.src, edge.dst);
        }
    }

    return false;
}

int main() {
    const std::array<Edge, 5> edges = {
        Edge{ 0, 1 },
        Edge{ 1, 2 },
        Edge{ 2, 3 },
        Edge{ 3, 4 },
        Edge{ 4, 0 }
    };

    std::cout << detect_cycle(edges) << "\n";
    return 0;
}

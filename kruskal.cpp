#include <iostream>
#include <vector>
#include <algorithm>

class UFS {
    std::vector<int> parent;
public:
    UFS(int number) {
        parent.resize(number);
        parent.assign(number, -1);
    }

    int find(int x) {
        while (parent[x] != -1) {
            x = parent[x];
        }

        return x;
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }
};

struct Edge {
    int begin;
    int end;
    int distance;

    Edge(int _begin, int _end, int _distance) : begin{ _begin }, end{ _end }, distance{ _distance } {}
};

int kruskal(int vertices, std::vector<Edge>& edges) {
    // asc order.
    std::sort(edges.begin(), edges.end(), [](const Edge& left, const Edge& right) {
        return left.distance < right.distance;
    });

    UFS ufs{ vertices };
    int totalCost = 0;
    int counter = 0;

    for (const Edge& edge : edges) {
        if (ufs.find(edge.begin) != ufs.find(edge.end)) {
            std::cout << edge.begin << " --> " << edge.end << ", distance is " << edge.distance << "\n";

            ufs.unite(edge.begin, edge.end);
            totalCost += edge.distance;
            ++counter;

            if (counter == vertices - 1) {
                break;
            }
        }
    }

    return totalCost;
}

int main() {
    // assume that we have 4 vertices, and 5 edges.
    std::vector<Edge> edges;
    
    edges.emplace_back(0, 1, 10);
    edges.emplace_back(1, 3, 15);
    edges.emplace_back(2, 3, 4);
    edges.emplace_back(2, 0, 6);
    edges.emplace_back(0, 3, 5);

    auto minCost = kruskal(4, edges);
    std::cout << "minimal cost is " << minCost << "\n";
    return 0;
}

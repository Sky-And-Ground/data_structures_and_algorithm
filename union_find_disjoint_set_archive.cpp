#include <iostream>
#include <vector>

class UFDS_V1 {
    std::vector<int> parent;
public:
    UFDS_V1(int parentSize) {
        parent.resize(parentSize);
        parent.assign(parentSize, -1);
    }

    // path compression.
    int find(int x) {
        if (parent[x] == -1) {
            return x;
        }
        else {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }

    void do_union(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);

        if (xRoot != yRoot) {
            parent[xRoot] = yRoot;
        }
    }

    bool is_connected(int x, int y) {
        return find(x) == find(y);
    }
};

class UFDS_V2 {
    std::vector<int> parent;
    std::vector<int> height;
public:
    UFDS_V2(int parentSize) {
        parent.resize(parentSize);
        parent.assign(parentSize, -1);

        height.resize(parentSize);
        height.assign(parentSize, 1);
    }

    int find(int x) {
        while (parent[x] != -1) {
            x = parent[x];
        }

        return x;
    }

    /*
        Inserting a shorter tree into a taller one can reduce the overall height of the final merged tree, 
        thereby decreasing the number of find operations.

        be cautions that, this method cannot deal with path compression, because path compression would modify the height.
    */
    void do_union(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);

        if (xRoot != yRoot) {
            if (height[xRoot] > height[yRoot]) {
                parent[yRoot] = xRoot;
            }
            else if (height[xRoot] < height[yRoot]) {
                parent[xRoot] = yRoot;
            }
            else {
                parent[xRoot] = yRoot;
                height[yRoot] += 1;
            }
        }
    }

    bool is_connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    UFDS_V2 ufds{ 5 };

    ufds.do_union(1, 2);
    ufds.do_union(3, 4);
    ufds.do_union(1, 4);

    std::cout << ufds.is_connected(4, 2) << "\n";
    return 0;
}

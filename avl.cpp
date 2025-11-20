#include <iostream>
#include <algorithm>
#include <queue>

struct Node {
    int value;
    int height;

    Node* left;
    Node* right;

    Node() : value{ 0 }, height{ 1 }, left{ nullptr }, right{ nullptr } {}
    Node(int v) : value{ v }, height{ 1 }, left{ nullptr }, right{ nullptr } {}
};

class AVL {
    Node* root;
    int len;

    int node_height(Node* node);
    int node_balance_factor(Node* node);
    Node* node_search_min_descendant(Node* node);
    void destroy_node(Node* node);
    Node* rotate_right(Node* node);
    Node* rotate_left(Node* node);
    Node* add_impl(Node* node, int value);
    Node* del_impl(Node* node, int value);
    void node_traverse_pre_order(Node* node);
    void node_traverse_in_order(Node* node);
    void node_traverse_post_order(Node* node);
public:
    AVL();
    ~AVL();

    bool contains(int value);
    void add(int value);
    void del(int value);
    void bfs();
    void print_pre_order();
    void print_in_order();
    void print_post_order();
};

AVL::AVL() : root{ nullptr }, len{ 0 } {}

AVL::~AVL() {
    destroy_node(root);
}

int AVL::node_height(Node* node) {
    return node == nullptr ? 0 : node->height;
}

int AVL::node_balance_factor(Node* node) {
    return node == nullptr ? 0 : node_height(node->left) - node_height(node->right);
}

Node* AVL::node_search_min_descendant(Node* node) {
    while (node->left) {
        node = node->left;
    }

    return node;
}

void AVL::destroy_node(Node* node) {
    if (node) {
        destroy_node(node->left);
        destroy_node(node->right);
        delete node;
    }
}

Node* AVL::rotate_right(Node* node) {
    Node* x = node->left;
    Node* y = x->right;

    node->left = y;
    x->right = node;

    node->height = 1 + std::max(node_height(node->left), node_height(node->right));
    x->height = 1 + std::max(node_height(x->left), node_height(x->right));

    return x;
}

Node* AVL::rotate_left(Node* node) {
    Node* x = node->right;
    Node* y = x->left;

    node->right = y;
    x->left = node;

    node->height = 1 + std::max(node_height(node->left), node_height(node->right));
    x->height = 1 + std::max(node_height(x->left), node_height(x->right));

    return x;
}

Node* AVL::add_impl(Node* node, int value) {
    if (node == nullptr) {
        ++len;
        return new Node(value);
    }

    if (node->value == value) {
        return node;
    }
    else if (value < node->value) {
        node->left = add_impl(node->left, value);
    }
    else {
        node->right = add_impl(node->right, value);
    }

    node->height = 1 + std::max(node_height(node->left), node_height(node->right));
    int balanceFactor = node_balance_factor(node);

    // LL.
    if (balanceFactor > 1 && node_balance_factor(node->left) >= 0) {
        return rotate_right(node);
    }

    // LR.
    if (balanceFactor > 1 && node_balance_factor(node->left) < 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // RR.
    if (balanceFactor < -1 && node_balance_factor(node->right) <= 0) {
        return rotate_left(node);
    }

    // RL.
    if (balanceFactor < -1 && node_balance_factor(node->right) > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

Node* AVL::del_impl(Node* node, int value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->value) {
        node->left = del_impl(node->left, value);
    }
    else if (value > node->value) {
        node->right = del_impl(node->right, value);
    }
    else {
        // no child or only 1 child.
        if (node->left == nullptr || node->right == nullptr) {
            Node* child = (node->left != nullptr ? node->left : node->right);

            // no child.
            if (child == nullptr) {
                delete node;
                node = nullptr;
            }
            else {
                *node = *child;
                delete child;
            }

            --len;
        }
        else {
            Node* descendant = node_search_min_descendant(node->right);
            node->value = descendant->value;
            node->right = del_impl(node->right, descendant->value);
        }
    }

    if (node == nullptr) {
        return nullptr;
    }

    node->height = 1 + std::max(node_height(node->left), node_height(node->right));
    int balanceFactor = node_balance_factor(node);

    // LL.
    if (balanceFactor > 1 && node_balance_factor(node->left) >= 0) {
        return rotate_right(node);
    }

    // LR.
    if (balanceFactor > 1 && node_balance_factor(node->left) < 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // RR.
    if (balanceFactor < -1 && node_balance_factor(node->right) <= 0) {
        return rotate_left(node);
    }

    // RL.
    if (balanceFactor < -1 && node_balance_factor(node->right) > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

void AVL::node_traverse_pre_order(Node* node) {
    if (node) {
        std::cout << node->value << "\n";
        node_traverse_pre_order(node->left);
        node_traverse_pre_order(node->right);
    }
}

void AVL::node_traverse_in_order(Node* node) {
    if (node) {
        node_traverse_in_order(node->left);
        std::cout << node->value << "\n";
        node_traverse_in_order(node->right);
    }
}

void AVL::node_traverse_post_order(Node* node) {
    if (node) {
        node_traverse_post_order(node->left);
        node_traverse_post_order(node->right);
        std::cout << node->value << "\n";
    }
}

bool AVL::contains(int value) {
    Node* cursor = root;

    while (cursor) {
        if (cursor->value == value) {
            return true;
        }
        else if (value < cursor->value) {
            cursor = cursor->left;
        }
        else {
            cursor = cursor->right;
        }
    }

    return false;
}

void AVL::add(int value) {
    root = add_impl(root, value);
}

void AVL::del(int value) {
    root = del_impl(root, value);
}

void AVL::bfs() {
    if (len == 0) {
        return;
    }

    std::queue<Node*> q;

    q.push(root);
    while (!q.empty()) {
        Node* cursor = q.front();
        std::cout << cursor->value << "\n";
        q.pop();

        if (cursor->left) {
            q.push(cursor->left);
        }

        if (cursor->right) {
            q.push(cursor->right);
        }
    }
}

void AVL::print_pre_order() {
    node_traverse_pre_order(root);
}

void AVL::print_in_order() {
    node_traverse_in_order(root);
}

void AVL::print_post_order() {
    node_traverse_post_order(root);
}

/*
  39

  39
 /
2

  39
 /  \
2    78

  39
 /  \
2    78
       \
        101

  39
 /  \
2    78
    /  \
  57    101


  39
 /  \
2    78
    /  \
  57    101
 /
46

  39
 /  \
2    57
    /  \
  46    78
          \
           101

     57
    /  \
  39    78
 /  \     \
2    46    101

*/
int main() {
    AVL avl;

    avl.add(39);
    avl.add(2);
    avl.add(78);
    avl.add(101);
    avl.add(57);
    avl.add(46);

    std::cout << "in order:\n";
    avl.print_in_order();

    std::cout << "\nbfs:\n";
    avl.bfs();
    return 0;
}
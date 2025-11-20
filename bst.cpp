#include <iostream>

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int _value) : value{ _value }, left{ nullptr }, right{ nullptr } {}
};

class BST {
    Node* root;

    void destroy_node(Node* node) {
        if (node) {
            destroy_node(node->left);
            destroy_node(node->right);
            delete node;
        }
    }

    Node* add(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        else {
            if (node->value == value) {
                return node;
            }
            else if (node->value > value) {
                node->left = add(node->left, value);
            }
            else {
                node->right = add(node->right, value);
            }

            return node;
        }
    }

    Node* get_min_node(Node* node) {
        Node* cursor = node;

        while (cursor && cursor->left) {
            cursor = cursor->left;
        }

        return cursor;
    }

    Node* del(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->value > value) {
            node->left = del(node->left, value);
        }
        else if (node->value < value) {
            node->right = del(node->right, value);
        }
        else {
            // no child or only one child.
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left != nullptr ? node->left : node->right;

                // no child.
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }

                delete temp;
            }
            else {
                Node* successor = get_min_node(node->right);
                node->value = successor->value;
                node->right = del(node->right, successor->value);
            }
        }

        return node;
    }
public:
    BST() : root{ nullptr } {}

    ~BST() {
        destroy_node(root);
    }

    void add(int value) {
        root = add(root, value);
    }

    void add_no_recursive(int value) {
        if (root == nullptr) {
            root = new Node(value);
            return;
        }

        Node* cursor = root;
        Node* pre = nullptr;

        while (cursor) {
            pre = cursor;

            if (cursor->value == value) {
                return;
            }
            else if (cursor->value > value) {
                cursor = cursor->left;
            }
            else {
                cursor = cursor->right;
            }
        }

        if (pre->value > value) {
            pre->left = new Node(value);
        }
        else {
            pre->right = new Node(value);
        }
    }

    bool contains(int value) noexcept {
        Node* cursor = root;

        while (cursor) {
            if (cursor->value == value) {
                return true;
            }
            else if (cursor->value > value) {
                cursor = cursor->left;
            }
            else {
                cursor = cursor->right;
            }
        }

        return false;
    }

    void del(int value) noexcept {
        root = del(root, value);
    }
};

int main() {
    BST bst;

    bst.add(29);
    bst.add(11);
    bst.add(5);
    bst.add(31);
    bst.add(59);

    std::cout << bst.contains(29) << "\n";
    bst.del(29);
    std::cout << bst.contains(29) << "\n";

    std::cout << bst.contains(11) << "\n";
    bst.del(11);
    std::cout << bst.contains(11) << "\n";

    std::cout << bst.contains(5) << "\n";
    bst.del(5);
    std::cout << bst.contains(5) << "\n";

    std::cout << bst.contains(31) << "\n";
    bst.del(31);
    std::cout << bst.contains(31) << "\n";

    std::cout << bst.contains(59) << "\n";
    bst.del(59);
    std::cout << bst.contains(59) << "\n";
    return 0;
}

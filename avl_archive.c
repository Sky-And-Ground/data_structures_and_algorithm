#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    int height;
};

struct AVL {
    struct Node* root;
};

void* malloc_or_die(size_t size) {
    void* memory = malloc(size);

    if (memory == NULL) {
        fprintf(stderr, "%s: malloc failed for %lld bytes\n", size);
        exit(EXIT_FAILURE);
    }

    return memory;
}

int avl_max(int a, int b) {
    return a > b ? a : b;
}

int height(struct Node* node) {
    return (node != NULL) ? node->height : 0;
}

struct Node* create_new_node(int value) {
    struct Node* node = (struct Node*)malloc_or_die(sizeof(struct Node));

    node->value = value;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

struct AVL* create_avl(void) {
    struct AVL* avl = (struct AVL*)malloc_or_die(sizeof(struct AVL));

    avl->root = NULL;
    return avl;
}

void __destroy_avl_node(struct Node* node) {
    if (node) {
        __destroy_avl_node(node->left);
        __destroy_avl_node(node->right);
        free(node);
    }
}

void destory_avl(struct AVL* avl) {
    if (avl) {
        __destroy_avl_node(avl->root);
    }
}

/*
    / \
    \
*/
struct Node* avl_rotate_right(struct Node* node) {
    struct Node* x = node->left;
    struct Node* y = x->right;

    x->right = node;
    node->left = y;

    node->height = 1 + avl_max(height(node->left), height(node->right));
    x->height = 1 + avl_max(height(x->left), height(x->right));

    return x;
}

/*
    / \
      /
*/
struct Node* avl_rotate_left(struct Node* node) {
    struct Node* x = node->right;
    struct Node* y = x->left;

    x->left = node;
    node->right = y;

    node->height = 1 + avl_max(height(node->left), height(node->right));
    x->height = 1 + avl_max(height(x->left), height(x->right));

    return x;
}

int avl_get_balance(struct Node* node) {
    if (node == NULL) {
        return 0;
    }

    return height(node->left) - height(node->right);
}

struct Node* __avl_insert(struct Node* node, int value) {
    if (node == NULL) {
        return create_new_node(value);
    }

    if (node->value == value) {
        return node;
    }
    else if (node->value > value) {
        node->left = __avl_insert(node->left, value);
    }
    else {
        node->right = __avl_insert(node->right, value);
    }

    node->height = 1 + avl_max(height(node->left), height(node->right));
    int balanceFactor = avl_get_balance(node);

    if (balanceFactor > 1 && value < node->left->value) {
        return avl_rotate_right(node);
    }

    if (balanceFactor < -1 && value > node->right->value) {
        return avl_rotate_left(node);
    }

    if (balanceFactor > 1 && value > node->left->value) {
        node->left = avl_rotate_left(node->left);
        return avl_rotate_right(node);
    }

    if (balanceFactor < -1 && value < node->right->value) {
        node->right = avl_rotate_right(node->right);
        return avl_rotate_left(node);
    }

    return node;
}

void avl_insert(struct AVL* avl, int value) {
    avl->root = __avl_insert(avl->root, value);
}

int avl_contains(struct AVL* avl, int value) {
    struct Node* cursor = avl->root;

    while (cursor) {
        if (cursor->value == value) {
            return 1;
        }
        else if (cursor->value > value) {
            cursor = cursor->left;
        }
        else {
            cursor = cursor->right;
        }
    }

    return 0;
}

struct Node* avl_get_min_node(struct Node* node) {
    while (node->left) {
        node = node->left;
    }

    return node;
}

struct Node* __avl_del_node(struct Node* node, int value) {
    if (node == NULL) {
        return NULL;
    }

    if (node->value < value) {
        node->right = __avl_del_node(node->right, value);
    }
    else if (node->value > value) {
        node->left = __avl_del_node(node->left, value);
    }
    else {
        /* no child or only one child. */
        if (node->left == NULL || node->right == NULL) {
            struct Node* temp = node->left != NULL ? node->left : node->right;

            /* no child. */
            if (temp == NULL) {
                temp = node;
                node = NULL;
            }
            else {   /* only one child. */
                *node = *temp;
            }

            free(temp);
        }
        else {   /* have both children. */
            struct Node* successor = avl_get_min_node(node->right);
            node->value = successor->value;
            node->right = __avl_del_node(node->right, successor->value);
        }
    }

    /* no child. */
    if (node == NULL) {
        return node;
    }

    node->height = 1 + avl_max(height(node->left), height(node->right));
    int balanceFactor = avl_get_balance(node);

    /*
            A           A
           /           /
          B           B
         /           / \
        C           C   D

        both cases need right rotate.
    */
    if (balanceFactor > 1 && avl_get_balance(node->left) >= 0) {
        return avl_rotate_right(node);
    }

    if (balanceFactor > 1 && avl_get_balance(node->left) < 0) {
        node->left = avl_rotate_left(node->left);
        return avl_rotate_right(node);
    }

    if (balanceFactor < -1 && avl_get_balance(node->right) <= 0) {
        return avl_rotate_left(node);
    }

    if (balanceFactor < -1 && avl_get_balance(node->right) > 0) {
        node->right = avl_rotate_right(node->right);
        return avl_rotate_left(node);
    }

    return node;
}

void avl_del(struct AVL* avl, int value) {
    avl->root = __avl_del_node(avl->root, value);
}

int main(void) {
    struct AVL* avl = create_avl();

    avl_insert(avl, 1);
    avl_insert(avl, 2);
    avl_insert(avl, 3);
    avl_insert(avl, 4);
    avl_insert(avl, 5);

    printf("avl contains: %d\n", avl_contains(avl, 3));
    printf("avl contains: %d\n", avl_contains(avl, 6));

    avl_del(avl, 3);
    printf("avl contains: %d\n", avl_contains(avl, 3));
    printf("avl contains: %d\n", avl_contains(avl, 6));
    destory_avl(avl);
    return 0;
}

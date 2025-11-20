#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    int height;

    struct Node* left;
    struct Node* right;
};

struct AVL {
    struct Node* root;
    int len;
};

/* avl operations. */
int avl_max(int a, int b);
int avl_node_height(struct Node* node);
int avl_node_balance_factor(struct Node* node);
struct Node* avl_node_search_min_descendant(struct Node* node);
struct Node* avl_node_new(int value);
void avl_init(struct AVL* avl);
void avl_destroy_node(struct Node* node);
void avl_destroy(struct AVL* avl);
struct Node* avl_rotate_right(struct Node* node);
struct Node* avl_rotate_left(struct Node* node);
struct Node* avl_insert_impl(struct AVL* avl, struct Node* node, int value, int* out_of_memory);
struct Node* avl_delete_impl(struct AVL* avl, struct Node* node, int value);
int avl_insert(struct AVL* avl, int value);
int avl_contains(struct AVL* avl, int value);
void avl_delete(struct AVL* avl, int value);

/* traverse. */
int avl_traverse_bfs(struct AVL* avl);
void avl_node_traverse_pre_order(struct Node* node);
void avl_node_traverse_in_order(struct Node* node);
void avl_node_traverse_post_order(struct Node* node);
void avl_traverse_pre_order(struct AVL* avl);
void avl_traverse_in_order(struct AVL* avl);
void avl_traverse_post_order(struct AVL* avl);

/* test cases. */
void test_avl_case1(void);

int avl_max(int a, int b) {
    return a > b ? a : b;
}

int avl_node_height(struct Node* node) {
    return node == NULL ? 0 : node->height;
}

int avl_node_balance_factor(struct Node* node) {
    return node == NULL ? 0 : (avl_node_height(node->left) - avl_node_height(node->right));
}

struct Node* avl_node_new(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    if (node) {
        node->value = value;
        node->height = 1;
        node->left = node->right = NULL;
    }

    return node;
}

void avl_init(struct AVL* avl) {
    avl->len = 0;
    avl->root = NULL;
}

void avl_destroy_node(struct Node* node) {
    if (node) {
        avl_destroy_node(node->left);
        avl_destroy_node(node->right);
        free(node);
    }
}

void avl_destroy(struct AVL* avl) {
    avl_destroy_node(avl->root);
}

struct Node* avl_rotate_right(struct Node* node) {
    struct Node* x = node->left;
    struct Node* y = x->right;

    node->left = y;
    x->right = node;

    node->height = 1 + avl_max(avl_node_height(node->left), avl_node_height(node->right));
    x->height = 1 + avl_max(avl_node_height(x->left), avl_node_height(x->right));

    return x;
}

struct Node* avl_rotate_left(struct Node* node) {
    struct Node* x = node->right;
    struct Node* y = x->left;

    node->right = y;
    x->left = node;

    node->height = 1 + avl_max(avl_node_height(node->left), avl_node_height(node->right));
    x->height = 1 + avl_max(avl_node_height(x->left), avl_node_height(x->right));

    return x;
}

struct Node* avl_insert_impl(struct AVL* avl, struct Node* node, int value, int* out_of_memory) {
    struct Node* temp;
    int balanceFactor;

    if (node == NULL) {
        struct Node* newNode = avl_node_new(value);

        if (newNode == NULL) {
            *out_of_memory = 1;
        }
        else {
            avl->len += 1;
        }

        return newNode;
    }

    if (node->value == value) {
        return node;
    }
    else if (node->value > value) {
        temp = avl_insert_impl(avl, node->left, value, out_of_memory);

        if (*out_of_memory) {
            return NULL;
        }
        else {
            node->left = temp;
        }
    }
    else {
        temp = avl_insert_impl(avl, node->right, value, out_of_memory);

        if (*out_of_memory) {
            return NULL;
        }
        else {
            node->right = temp;
        }
    }

    node->height = 1 + avl_max(avl_node_height(node->left), avl_node_height(node->right));
    balanceFactor = avl_node_balance_factor(node);

    if (balanceFactor > 1 && avl_node_balance_factor(node->left) >= 0) {
        return avl_rotate_right(node);
    }

    if (balanceFactor > 1 && avl_node_balance_factor(node->left) < 0) {
        node->left = avl_rotate_left(node->left);
        return avl_rotate_right(node);
    }

    if (balanceFactor < -1 && avl_node_balance_factor(node->right) <= 0) {
        return avl_rotate_left(node);
    }

    if (balanceFactor < -1 && avl_node_balance_factor(node->right) > 0) {
        node->right = avl_rotate_right(node->right);
        return avl_rotate_left(node);
    }

    return node;
}

int avl_insert(struct AVL* avl, int value) {
    int out_of_memory = 0;
    avl->root = avl_insert_impl(avl, avl->root, value, &out_of_memory);
    return out_of_memory == 0;
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

struct Node* avl_node_search_min_descendant(struct Node* node) {
    while (node->left) {
        node = node->left;
    }

    return node;
}

struct Node* avl_delete_impl(struct AVL* avl, struct Node* node, int value) {
    int balanceFactor;

    if (node == NULL) {
        return NULL;
    }

    if (node->value < value) {
        node->right = avl_delete_impl(avl, node->right, value);
    }
    else if (node->value > value) {
        node->left = avl_delete_impl(avl, node->left, value);
    }
    else {
        /* no child or only one child. */
        if (node->left == NULL || node->right == NULL) {
            struct Node* child = (node->left != NULL ? node->left : node->right);

            if (child == NULL) {
                child = node;
                node = NULL;
            }
            else {
                *node = *child;
            }

            avl->len -= 1;
            free(child);
        }
        else {
            struct Node* descendant = avl_node_search_min_descendant(node->right);
            node->value = descendant->value;
            node->right = avl_delete_impl(avl, node->right, descendant->value);
        }
    }

    if (node == NULL) {
        return NULL;
    }

    node->height = 1 + avl_max(avl_node_height(node->left), avl_node_height(node->right));
    balanceFactor = avl_node_balance_factor(node);

    if (balanceFactor > 1 && avl_node_balance_factor(node->left) >= 0) {
        return avl_rotate_right(node);
    }

    if (balanceFactor > 1 && avl_node_balance_factor(node->left) < 0) {
        node->left = avl_rotate_left(node->left);
        return avl_rotate_right(node);
    }

    if (balanceFactor < -1 && avl_node_balance_factor(node->right) <= 0) {
        return avl_rotate_left(node);
    }

    if (balanceFactor < -1 && avl_node_balance_factor(node->right) > 0) {
        node->right = avl_rotate_right(node->right);
        return avl_rotate_left(node);
    }

    return node;
}

void avl_delete(struct AVL* avl, int value) {
    avl->root = avl_delete_impl(avl, avl->root, value);
}

int avl_traverse_bfs(struct AVL* avl) {
    int front, rear;
    struct Node* cursor;
    struct Node** queue;

    if (avl->len == 0) {
        return 1;
    }

    if ((queue = (struct Node**)malloc(avl->len * sizeof(struct Node*))) == NULL) {
        return 0;
    }

    front = rear = 0;
    queue[rear] = avl->root;
    ++rear;

    while (front != rear) {
        cursor = queue[front];
        ++front;

        printf("%d ", cursor->value);

        if (cursor->left) {
            queue[rear] = cursor->left;
            ++rear;
        }

        if (cursor->right) {
            queue[rear] = cursor->right;
            ++rear;
        }        
    }

    free(queue);
    printf("\n");
    return 1;
}

void avl_node_traverse_pre_order(struct Node* node) {
    if (node) {
        printf("%d ", node->value);
        avl_node_traverse_pre_order(node->left);
        avl_node_traverse_pre_order(node->right);
    }
}

void avl_node_traverse_in_order(struct Node* node) {
    if (node) {
        avl_node_traverse_in_order(node->left);
        printf("%d ", node->value);
        avl_node_traverse_in_order(node->right);
    }
}

void avl_node_traverse_post_order(struct Node* node) {
    if (node) {
        avl_node_traverse_post_order(node->left);
        avl_node_traverse_post_order(node->right);
        printf("%d ", node->value);
    }
}

void avl_traverse_pre_order(struct AVL* avl) {
    avl_node_traverse_pre_order(avl->root);
    printf("\n");
}

void avl_traverse_in_order(struct AVL* avl) {
    avl_node_traverse_in_order(avl->root);
    printf("\n");
}

void avl_traverse_post_order(struct AVL* avl) {
    avl_node_traverse_post_order(avl->root);
    printf("\n");
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
void test_avl_case1(void) {
    struct AVL avl;

    avl_init(&avl);
    avl_insert(&avl, 39);
    avl_insert(&avl, 2);
    avl_insert(&avl, 78);
    avl_insert(&avl, 101);
    avl_insert(&avl, 57);
    avl_insert(&avl, 46);

    printf("in order:\n");
    avl_traverse_in_order(&avl);

    printf("\nbfs:\n");
    avl_traverse_bfs(&avl);
    avl_destroy(&avl);
}

int main(void) {
    test_avl_case1();
    return 0;
}

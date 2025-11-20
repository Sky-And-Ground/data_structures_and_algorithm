#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    const char* key;
    const char* value;
    struct Node* next;
};

struct NodeList {
    struct Node* head;
    struct Node* tail;
};

struct Dict {
    struct NodeList* bucket;
    int bucketSize;
    int len;
};

/* single list. */
void node_init(struct Node* node, const char* key, const char* value);
int node_list_init(struct NodeList* list);
void node_list_destroy(struct NodeList* list);
void node_list_add_node(struct NodeList* list, struct Node* node);
void node_list_del_node(struct NodeList* list, struct Node* node);

/* dict. */
unsigned int dict_hash(struct Dict* dict, const char* key);
int dict_init(struct Dict* dict, int bucketSize);
void dict_destroy(struct Dict* dict);
int dict_put(struct Dict* dict, const char* key, const char* value);
void dict_del(struct Dict* dict, const char* key);
struct Node* dict_find_node(struct Dict* dict, const char* key);
const char* dict_find(struct Dict* dict, const char* key);

typedef void(*dict_traverse_callback)(const char* key, const char* value, void* param);
void dict_traverse(struct Dict* dict, dict_traverse_callback callback, void* param);

/* test cases. */
void test_dict_print_callback(const char* key, const char* value, void* param);
void test_dict(void);

void node_init(struct Node* node, const char* key, const char* value) {
    node->key = key;
    node->value = value;
    node->next = NULL;
}

int node_list_init(struct NodeList* list) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));

    if (temp) {
        list->head = temp;
        list->head->next = NULL;
        list->tail = list->head;
        return 1;
    }

    return 0;
}

void node_list_destroy(struct NodeList* list) {
    struct Node* cursor = list->head->next;
    struct Node* temp;

    while (cursor != NULL) {
        temp = cursor->next;
        free(cursor);
        cursor = temp;
    }

    free(list->head);
}

void node_list_add_node(struct NodeList* list, struct Node* node) {
    list->tail->next = node;
    list->tail = node;
}

void node_list_del_node(struct NodeList* list, struct Node* node) {
    struct Node* cursor = list->head->next;
    struct Node* parent = list->head;

    while (cursor != node) {
        parent = parent->next;
        cursor = cursor->next;
    }

    if (node == list->tail) {
        list->tail = parent;
    }

    parent->next = cursor->next;
    free(cursor);
}

unsigned int dict_hash(struct Dict* dict, const char* key) {
    unsigned int hashval = 0;

    while (*key) {
        hashval = 131 * hashval + (unsigned int)(*key - '0');
        ++key;
    }

    return hashval % dict->bucketSize;
}

int dict_init(struct Dict* dict, int bucketSize) {
    int i;

    dict->bucket = (struct NodeList*)malloc(bucketSize * sizeof(struct NodeList));
    if (dict->bucket == NULL) {
        return 0;
    }

    for (i = 0; i < bucketSize; ++i) {
        if (!node_list_init(&(dict->bucket[i]))) {
            --i;

            while (i >= 0) {
                node_list_destroy(&(dict->bucket[i]));
                --i;
            }

            return 0;
        }
    }

    dict->bucketSize = bucketSize;
    dict->len = 0;
    return 1;
}

void dict_destroy(struct Dict* dict) {
    int i;

    for (i = 0; i < dict->bucketSize; ++i) {
        node_list_destroy(&(dict->bucket[i]));
    }
}

int dict_put(struct Dict* dict, const char* key, const char* value) {
    struct Node* node = dict_find_node(dict, key);

    if (node) {
        node->value = value;
        return 1;
    }
    else {
        node = (struct Node*)malloc(sizeof(struct Node));

        if (node == NULL) {
            return 0;
        }
        else {
            unsigned int hashval = dict_hash(dict, key);
            node_init(node, key, value);
            node_list_add_node(&(dict->bucket[hashval]), node);
            dict->len += 1;
            return 1;
        }
    }
}

void dict_del(struct Dict* dict, const char* key) {
    unsigned int hashval = dict_hash(dict, key);
    struct Node* cursor = dict->bucket[hashval].head->next;
    
    while (cursor != NULL) {
        if (strcmp(key, cursor->key) == 0) {
            node_list_del_node(&(dict->bucket[hashval]), cursor);
            dict->len -= 1;
            return;
        }

        cursor = cursor->next;
    }
}

struct Node* dict_find_node(struct Dict* dict, const char* key) {
    unsigned int hashval = dict_hash(dict, key);
    struct Node* cursor = dict->bucket[hashval].head->next;
    
    while (cursor != NULL) {
        if (strcmp(key, cursor->key) == 0) {
            return cursor;
        }

        cursor = cursor->next;
    }
    
    return NULL;
}

const char* dict_find(struct Dict* dict, const char* key) {
    struct Node* node = dict_find_node(dict, key);
    return (node == NULL ? "" : node->value);
}

void dict_traverse(struct Dict* dict, dict_traverse_callback callback, void* param) {
    int i;
    struct Node* cursor;

    for (i = 0; i < dict->bucketSize; ++i) {
        cursor = dict->bucket[i].head->next;

        while (cursor != NULL) {
            callback(cursor->key, cursor->value, param);
            cursor = cursor->next;
        }
    }
}

void test_dict_print_callback(const char* key, const char* value, void* param) {
    printf("%s: %s\n", key, value);
}

void test_dict(void) {
    struct Dict dict;
    int ret;
    
    if (!dict_init(&dict, 101)) {
        fprintf(stderr, "out of memory\n");
        return;
    }
    
    ret = dict_put(&dict, "fenny", "ynnef") && 
            dict_put(&dict, "miku", "ukim") && 
            dict_put(&dict, "katya", "aytak") && 
            dict_put(&dict, "elysia", "aisyle");

    if (ret == 0) {
        dict_destroy(&dict);
        fprintf(stderr, "out of memory\n");
        return;
    }

    dict_traverse(&dict, test_dict_print_callback, NULL);
    dict_destroy(&dict);
}

int main(void) {
    test_dict();
    return 0;
}

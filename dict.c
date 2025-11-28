#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    const char* key;
    const char* value;
    struct Node* next;
};

struct Dict {
    struct Node** bucket;
    int bucketSize;
    int len;
};

void node_init(struct Node* node, const char* key, const char* value);
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

    dict->bucket = (struct Node**)malloc(bucketSize * sizeof(struct Node*));
    if (dict->bucket == NULL) {
        return 0;
    }

    for (i = 0; i < bucketSize; ++i) {
        dict->bucket[i] = NULL;
    }

    dict->bucketSize = bucketSize;
    dict->len = 0;
    return 1;
}

void dict_destroy(struct Dict* dict) {
    int i;
    for (i = 0; i < dict->bucketSize; ++i) {
        struct Node* cursor = dict->bucket[i];
        struct Node* tmp;

        while (cursor) {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
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
            
            if (dict->bucket[hashval] == NULL) {
                dict->bucket[hashval] = node;
            }
            else {
                node->next = dict->bucket[hashval];
                dict->bucket[hashval] = node;
            }
            
            dict->len += 1;
            return 1;
        }
    }
}

void dict_del(struct Dict* dict, const char* key) {
    unsigned int hashval = dict_hash(dict, key);
    struct Node* cursor = dict->bucket[hashval];
    struct Node* parent = NULL;;
    
    while (cursor) {
        if (strcmp(key, cursor->key) == 0) {
            if (cursor == dict->bucket[hashval]) {
                struct Node* next = cursor->next;
                free(cursor);
                dict->bucket[hashval] = next;
            }
            else {
                parent->next = cursor->next;
                free(cursor);
            }

            dict->len -= 1;
            return;
        }

        parent = cursor;
        cursor = cursor->next;
    }
}

struct Node* dict_find_node(struct Dict* dict, const char* key) {
    unsigned int hashval = dict_hash(dict, key);
    struct Node* cursor = dict->bucket[hashval];
    
    while (cursor) {
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
        cursor = dict->bucket[i];

        while (cursor) {
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
    dict_init(&dict, 101);
    
    dict_put(&dict, "fenny", "ynnef");
    dict_put(&dict, "miku", "ukim");
    dict_put(&dict, "katya", "aytak");
    dict_put(&dict, "elysia", "aisyle");

    dict_del(&dict, "miku");
    dict_del(&dict, "katya");
    dict_del(&dict, "fenny");
    dict_del(&dict, "elysia");

    dict_put(&dict, "fenny", "_ynnef");
    dict_put(&dict, "miku", "_ukim");
    dict_put(&dict, "katya", "_aytak");
    dict_put(&dict, "elysia", "_aisyle");

    dict_traverse(&dict, test_dict_print_callback, NULL);
    dict_destroy(&dict);
}

int main(void) {
    test_dict();
    return 0;
}

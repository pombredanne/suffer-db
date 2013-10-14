#include <stdbool.h>
#include <stddef.h>
#include "critbit.h"

typedef struct {
    critbit_tree tree;
} suffer_db;

typedef bool (*suffer_iter)(const void *key, size_t klen, const void *val, size_t vlen, void * arg);

void suffer_init(suffer_db * db);
bool suffer_add(suffer_db * db, void * key, size_t keylen, void * val, size_t vallen);
bool suffer_get(suffer_db * db, void * key, size_t keylen, suffer_iter iter, void * arg);

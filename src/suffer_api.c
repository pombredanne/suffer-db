#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#include "suffer_api.h"
#include "critbit.h"

void suffer_init(suffer_db * db) {
    db->tree.root = NULL;
}

bool suffer_add(suffer_db * db, void * key, size_t klen, void * val, size_t vlen) {
    size_t entrylen = klen + 1 + vlen + 1;
    void * entry = alloca(entrylen);
    memmove(entry, key, klen);
    memset(entry+klen, 0, 1);
    memmove(entry+klen+1, val, vlen);
    memset(entry+klen+1+vlen, 0, 1);
    return CB_SUCCESS != cb_insert(&db->tree, entry, entrylen);
}

typedef struct {
    suffer_iter iter;
    void * arg;
} get_iter_data;

static int get_iter(const void * match, const void * _key, size_t _keylen, void * arg) {
    const uint8_t * data = (const uint8_t *)match;
    int i;
    for (i = 0; data[i] != 0; ++i);
    return 0;
}

bool suffer_get(suffer_db * db, void * key, size_t keylen, suffer_iter iter, void * arg) {
    get_iter_data state = { iter, arg };
    return 0 == cb_foreach(&db->tree, key, keylen, get_iter, &state);
}

#pragma once
#include <stddef.h>
#include "EnumTypes.h"

typedef struct dict_enrty{
    void *key;
    void *value;
}dict_entry;
typedef struct dict{
    enum types key_type;
    enum types value_type;
    dict_entry **entries;
    size_t size;
}dict;
dict *dict_init(enum types key_type, enum types value_type);
int dict_insert(dict *D, void *key, void *value);
int dict_deleteAt(dict *D, size_t index);
size_t dict_search(dict *D, void *key);
int dict_delete(dict *D, void *key);
void dict_free(dict *D);
void dict_print(dict *D);

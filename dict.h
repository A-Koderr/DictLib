#pragma once
#include <stddef.h>

/*
    enum types represents type of dictionary
    x_y,    x -> type of key
            y -> type of value
    num -> long long
    str -> char*
*/
enum types{num_num, num_str, str_str, str_num};
typedef struct dict_enrty{
    void *key;
    void *value;
}dict_entry;
typedef struct dict{
    enum types dict_type;
    dict_entry **entries;
    size_t size;
}dict;
dict *dict_init(enum types type);
int dict_insert(dict *D, void *key, void *value);
int dict_deleteAt(dict *D, unsigned index);
int dict_delete(dict *D, void *key);
void *dict_search(dict *D);

#include "dict.h"
dict *dict_init(enum types type){
    dict *ptr = malloc(sizeof(dict));
    ptr->dict_type = type;
    ptr->entries = NULL;
    ptr->size = 0;
    return ptr;
}

// Returns -1 if malloc is failed
// Returns -2 if realloc is failed with means old block is still allocated
int dict_insert(dict *D, void *key, void *value){
    if ( (D->entries = realloc(D->entries, sizeof(void *)*(D->size+1))) == NULL)
        return -2;                                                          //old block is still allocated
    if ( (D->entries[D->size-1] = malloc(sizeof(dict_entry))) == NULL)
        return -1;

    if (D->dict_type == num_num) {
        if ( (D->entries[D->size-1]->key = malloc(sizeof(long long))) == NULL)
            return -1;
        *(long long*)D->entries[D->size-1]->key = *(long long*)key;

        if ( (D->entries[D->size-1]->value = malloc(sizeof(long long))) == NULL)
            return -1;
        *(long long*)D->entries[D->size-1]->value = *(long long*)value;
    }
    else if (D->dict_type == num_str) {
        if ( (D->entries[D->size-1]->key = malloc(sizeof(long long))) == NULL)
            return -1;
        *(long long*)D->entries[D->size-1]->key = *(long long*)key;

        if ( (D->entries[D->size-1]->value = malloc((sizeof(char)*strlen(value)+1))) == NULL)
            return -1;
        strcpy(D->entries[D->size-1]->value, value);
    }
    else if (D->dict_type == str_str) {
        if ( (D->entries[D->size-1]->key = malloc((sizeof(char)*strlen(key)+1))) == NULL)
            return -1;
        strcpy(D->entries[D->size-1]->key, key);

        if ( (D->entries[D->size-1]->value = malloc((sizeof(char)*strlen(value)+1))) == NULL)
            return -1;
        strcpy(D->entries[D->size-1]->value, value);
    }
    else if (D->dict_type == str_num) {
        if ( (D->entries[D->size-1]->key = malloc((sizeof(char)*strlen(key)+1))) == NULL)
            return -1;
        strcpy(D->entries[D->size-1]->key, key);

        if ( (D->entries[D->size-1]->value = malloc(sizeof(long long))) == NULL)
            return -1;
        *(long long*)D->entries[D->size-1]->value = *(long long*)value;
    }
    ++D->size;
    return 0;
}
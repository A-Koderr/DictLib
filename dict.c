#include "dict.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Internal Functions
void *dict_insert_num(void *num);
void *dict_insert_str(void *str);
dict_entry *dict_entry_init();
void dict_entry_free(dict_entry *ptr);

dict *dict_init(enum types type) {
    dict *ptr = malloc(sizeof(dict));
    ptr->dict_type = type;
    ptr->entries = NULL;
    ptr->size = 0;
    return ptr;
}

dict_entry *dict_entry_init() {
    dict_entry *ptr = malloc(sizeof(dict_entry));
    if (ptr == NULL) {
        fprintf(stderr, "Allocation of dict_enrty failed. Possible memory corruption");
        return NULL;
    }
    ptr->key = NULL;
    ptr->value = NULL;
    return ptr;
}

// Returns -1 if malloc is failed
// Returns -2 if realloc is failed with means old block is still allocated
int dict_insert(dict *D, void *key, void *value) {
    void *ptr = realloc(D->entries, sizeof(void *)*(D->size+1));
    if (ptr == NULL) {
        fprintf(stderr,"Reallocation of ptr to Dictionary Entries failed.\nRetry allocation old memory block still intact");
        return -2;                                                          //old block is still allocated
    }
    D->entries = ptr;
    ptr = NULL;

    ptr = dict_entry_init();
    if(ptr == NULL)
        return -1;
    D->entries[D->size] = ptr;
    ptr = NULL;

    if (D->dict_type == num_num) {
        D->entries[D->size]->key = dict_insert_num(key);
        D->entries[D->size]->value = dict_insert_num(value);
    }
    else if (D->dict_type == num_str) {
        D->entries[D->size]->key = dict_insert_num(key);
        D->entries[D->size]->value = dict_insert_str(value);
    }
    else if (D->dict_type == str_str) {
        D->entries[D->size]->key = dict_insert_str(key);
        D->entries[D->size]->value = dict_insert_str(value);
    }
    else if (D->dict_type == str_num) {
        D->entries[D->size]->key = dict_insert_str(key);
        D->entries[D->size]->value = dict_insert_num(value);
    }

    if (D->entries[D->size]->key == NULL || D->entries[D->size]->value == NULL) {
        dict_entry_free(D->entries[D->size]);
        return -1;
    }
    ++D->size;
    return 0;
}
int dict_deleteAt(dict *D, unsigned index) {
    dict_entry_free(D->entries[index]);
    for(int i=index; i<D->size; ++i){
        D->entries[i] = D->entries[i+1];
    }
    void *ptr = realloc(D->entries,sizeof(void *)*(D->size-1));
    if(ptr == NULL) {
        return -2;
    }   
    D->entries = ptr;
    --D->size;
    return 0;
}
void *dict_insert_num(void *num) {
    long long *ptr = malloc(sizeof(long long));
    if (ptr == NULL) {
        fprintf(stderr, "malloc failed while allocating %lu bytes for num", sizeof(long long));
        return NULL;
    }
    long long NUM = *(long long*)num;
    *ptr = NUM;
    return ptr;
}
void *dict_insert_str(void *str) {
    unsigned long long i = 0;
    char *STR = str;
    while(STR[i] != '\0' || i != (ULLONG_MAX-1))
        ++i;
    char *ptr = malloc(sizeof(char)*(i+1));
    if (ptr == NULL) {
        fprintf(stderr, "malloc failed while allocating %lu bytes for num", sizeof(long long));
        return NULL;
    }
    strncpy(ptr, str, i);
    ptr[i+1] = '\0';
    return ptr;
}
void dict_entry_free(dict_entry *ptr) {
    if(ptr != NULL) {
        if(ptr->key != NULL)
            free(ptr->key);
        if(ptr->value != NULL)
            free(ptr->value);
    free(ptr);
    }
}
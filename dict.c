#include "dict.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


//Internal Functions
void *dict_insert_num(void *num);
void *dict_insert_str(void *str);
dict_entry *dict_entry_init();
void dict_entry_free(dict_entry *ptr);

dict *dict_init(enum types key_type, enum types value_type) {
    dict *ptr = malloc(sizeof(dict));
    ptr->key_type = key_type;
    ptr->value_type = value_type;
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

    // Key Insertion
    if (D->key_type == num) {
        D->entries[D->size]->key = dict_insert_num(key);
    }
    else if (D->key_type == str) {
        D->entries[D->size]->key = dict_insert_str(key);
    }

    // Value Insertion
    if(D->value_type == num){
        D->entries[D->size]->value = dict_insert_num(value);
    }
    else if (D->value_type == str) {
        D->entries[D->size]->value = dict_insert_str(value);
    }

    // If memory allocation fails
    if (D->entries[D->size]->key == NULL || D->entries[D->size]->value == NULL) {
        dict_entry_free(D->entries[D->size]);
        return -1;
    }

    // If everything goes alright
    ++D->size;
    return 0;
}

//Deletes Dict Entry at a particular index
int dict_deleteAt(dict *D, size_t index) {
    dict_entry_free(D->entries[index]);

    //Moving all the Enrty ptrs to fill the space left by the above free() operation
    for(int i=index; i<D->size; ++i){
        D->entries[i] = D->entries[i+1];
    }
    D->entries[D->size] = NULL;
    void *ptr = realloc(D->entries,sizeof(void *)*(D->size-1));
    if(ptr == NULL) {
        fprintf(stderr, "Deletion successfull but reallocation failed dict size intact");
        return -2;
    }   
    D->entries = ptr;
    --D->size;
    return 0;
}

size_t dict_search(dict *D, void *key) {
    if(D->key_type==num) { 
        long long KEY = *(long long *)key;
        for(size_t i = 0; i<D->size; ++i) {
            if (*(unsigned long long *)D->entries[i]->key == KEY) {
                return i;
            } 
        }
    }
    else if (D->key_type==str) {
        size_t i = 0;
        char *STR = key;
        while (STR[i] != '\0' || i != (ULLONG_MAX-1))
            ++i;
        for (size_t j = 0; j<D->size; ++j) {
            if (strncmp(STR, D->entries[j]->key, i) == 0) {
                return j;
            }
        }
    }
    return -1;
}
int dict_delete(dict *D, void *key) {
    size_t index = dict_search(D, key);
    int ret = dict_deleteAt(D, index);
    return ret;
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
    size_t i = 0;
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
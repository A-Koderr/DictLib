#include "dict/dict_lib.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


//Internal Functions
void *dict_insert_num(void *LONG);
void *dict_insert_str(void *STR);
dict_entry *dict_entry_init();
void dict_entry_free(dict_entry *ptr);
void dict_print_LONG(void *LONG);
void dict_print_STR(void *STR);

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
// Returns -2 if realloc is failed which means old block is still allocated
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
    if (D->key_type == LONG) {
        D->entries[D->size]->key = dict_insert_num(key);
    }
    else if (D->key_type == STR) {
        D->entries[D->size]->key = dict_insert_str(key);
    }

    // Value Insertion
    if(D->value_type == LONG){
        D->entries[D->size]->value = dict_insert_num(value);
    }
    else if (D->value_type == STR) {
        D->entries[D->size]->value = dict_insert_str(value);
    }

    //If memory allocation fails
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
    for(int i=index; i<(D->size-1); ++i){
        D->entries[i] = D->entries[i+1];
    }
    D->entries[D->size-1] = NULL;
    if (D->size>1) {
        void *ptr = realloc(D->entries,sizeof(void *)*(D->size-1));
        if(ptr == NULL) {
            fprintf(stderr, "Deletion successfull but reallocation failed dict size intact");
            return -2;
        }   
        D->entries = ptr;
    }
    --D->size;
    return 0;
}

size_t dict_search(dict *D, void *key) {
    if(D->key_type==LONG) { 
        long long KEY = *(long long *)key;
        for(size_t i = 0; i<D->size; ++i) {
            if (*(unsigned long long *)D->entries[i]->key == KEY) {
                return i;
            } 
        }
    }
    else if (D->key_type==STR) {
        size_t i = 0;
        char *STR = key;
        while (STR[i] != '\0' && i != (ULLONG_MAX-1))
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

void *dict_insert_num(void *LONG) {
    long *ptr = NULL;
    if(LONG == NULL) {
        fprintf(stderr, "Passed a NULL ptr instead of long*. Dictionary Entry cannot be made.\n");
    }
    else {
        ptr = (long *)malloc(sizeof(long));
        if (ptr == NULL) {
            fprintf(stderr, "malloc failed while allocating %lu bytes for LONG", sizeof(long));
            return NULL;
        }
        *ptr = *(long *)LONG;
        }
    return ptr;
}
void *dict_insert_str(void *STR) {
    char *ptr = NULL;
    if(STR == NULL)
        fprintf(stderr, "Passed a NULL ptr instead of char*. Dictionary Entry cannot be made.\n");
    else {
        size_t i = 0;
        char *temp = (char *)STR;
        while(temp[i] != '\0' && i != (ULLONG_MAX-1))
            ++i;
        ptr = malloc(sizeof(char)*(i+1));
        if (ptr == NULL) {
            fprintf(stderr, "malloc failed while allocating %lu bytes for STR", sizeof(char)*(i-1));
            return NULL;
        }
        strncpy(ptr, STR, i);
        ptr[i] = '\0';
    }
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
void dict_free(dict *D) {
    for(size_t i = 0; i<D->size; ++i) {
        dict_entry_free(D->entries[i]);
    }
    free(D->entries);
    free(D);
}

void dict_print_LONG(void *LONG) {
    if(LONG == NULL)
        printf("(null)");
    else
        printf("%ld", *(long *)LONG);
}
void dict_print_STR(void *STR) {
    if(STR == NULL)
        printf("(null)");
    else
        printf("%s", (char *)STR);
}

void dict_print(dict *D) {
    printf("\n");
    for (size_t i = 0; i<D->size; ++i) {
        if (D->key_type == LONG) {
            dict_print_LONG(D->entries[i]->key);
        }
        else if (D->key_type == STR) {
            dict_print_STR(D->entries[i]->key);
        }
        printf(" - ");
        if (D->value_type == LONG) {
            dict_print_LONG(D->entries[i]->value);
        }
        else if (D->value_type == STR) {
            dict_print_STR(D->entries[i]->value);
        }
        printf("\n");
    }
}
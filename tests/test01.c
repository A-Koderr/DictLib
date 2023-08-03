//Test library by making 10 insertion and deletion
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "Dict/Dict.h"
int main(void)
{
    dict *ptr = dict_init(STR, STR);
    char **k = malloc(sizeof(void *)*10);
    char **v = malloc(sizeof(void *)*10);
    char seed = 'A';

    for(int i = 0; i<10; ++i) {
        k[i] = malloc(sizeof(char)*3);
        v[i] = malloc(sizeof(char)*3);
        for(int j = 0; j<2; ++j) {
            k[i][j] = j+seed;
            v[i][j] = 30+j+seed;
            ++seed;
        }
        k[i][2] = '\0';
        v[i][2] = '\0';
        int ret = dict_insert(ptr, k[i], v[i]);
        if(ret != 0) {
            return ret;
        }
    }
    dict_print(ptr);

    for(int i = 9; i<=0; --i) {
        int ret = dict_delete(ptr, k[i]);
        if(ret != 0)
            return ret;
    }
    dict_free(ptr);
    for(int i = 0; i<10; ++i){
        free(k[i]);
        free(v[i]);
    } 
    free(k);
    free(v);
    return 0;
}
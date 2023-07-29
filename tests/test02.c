#include "dict/dict_lib.h"
#include <stdio.h>
int main(void) {
    dict *D = dict_init(LONG, LONG);
    long key  = 1;
    long value = 10;
    for (int i = 0; i<10; ++i) {
        key = key*2 + i;
        value = value*4 + 2*i;
        int ret = dict_insert(D, &key, &value);
        if(ret != 0) {
            return ret;
        }
    }
    dict_print(D);
    key = 1;
    for(int i = 0; i<10; ++i) {
        key = key*2 + i;
        int ret = dict_delete(D, &key);
        if(ret != 0)
            return ret;
    }
    dict_free(D);
}
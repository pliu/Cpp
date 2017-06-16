//
// Created by Peng on 6/14/2017.
//

#include <cstdio>
#include "HashTables/separate_chaining_ht.h"
#include "Utils/utils.h"

int main() {
    SeparateChainingHt *scht = new SeparateChainingHt(5, 1.5);
    int hits = 0;
    for (int i = 0; i < 10000000; i++) {
        char *key = random_string(5);
        char *value = random_string(10);
        scht->add_item(key, 5, value, 10);
        delete key;
        delete value;
    }
    for (int i = 0; i < 10000000; i++) {
        char* key = random_string(5);
        if (scht->get_item(key, 5) != NULL) {
            hits ++;
        }
        delete key;
    }
    printf("%d", hits);
}

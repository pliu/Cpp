//
// Created by Peng on 6/14/2017.
//

#include <cstdio>
#include "HashTables/separate_chaining_ht.h"
#include "Utils/utils.h"

int main() {
    SeparateChainingHt *scht = new SeparateChainingHt(5, 1.5);
    int negatives = 0;
    for (int i = 0; i < 1000000; i++) {
        char *key = random_string(5);
        char *value = random_string(10);
        if (!scht->add_item(key, 5, value, 10)) {
            negatives++;
        }
        delete key;
        delete value;
    }
    printf("%d %d %d", scht->buckets(), scht->size(), negatives);
}

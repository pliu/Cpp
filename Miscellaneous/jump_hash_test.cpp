//
// Created by Peng on 6/4/2017.
//

#include <cstdio>
#include "HashTables/jump_hash.h"

int main() {
    JumpHash *jh = new JumpHash(10);
    uint64_t num_keys = 100000ULL;
    for (uint64_t i = 0; i < num_keys; i++) {
        jh->add_key(i);
    }
    jh->print_sizes();
    for (uint32_t i = 0; i < 10; i++) {
        jh->add_bucket();
    }
    printf("*** AFTER BUCKET(S) ADDED ***\n");
    jh->print_sizes();
    for (uint64_t i = 0; i <= num_keys; i++) {
        if (!jh->key_exists(i)) {
            printf("Could not find %d", i);
        }
    }
    return 0;
}

//
// Created by Peng on 6/14/2017.
//

#include <cstdio>
#include <iostream>
#include "HashTables/separate_chaining_ht.h"
#include "Utils/utils.h"

int main() {
    AbstractHt *scht = new SeparateChainingHt(5, 1.5);
    for (uint32_t i = 0; i < 1000000; i++) {
        char *key = random_string(5);
        char *value = random_string(10);
        scht->add_item(key, 5, value, 10);
        delete key;
        delete value;
    }
    for (uint32_t i = 0; i < 1000000; i++) {
        char *key = random_string(5);
        scht->get_item(key, 5);
        delete key;
    }

#ifdef INSTRUMENT
    std::cout << stats.add_time.count() << std::endl;
    std::cout << stats.get_time.count() << std::endl;
    std::cout << stats.expand_time.count() << std::endl;
#endif

}

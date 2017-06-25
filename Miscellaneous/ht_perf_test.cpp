#include <cstdio>
#include <iostream>
#include "HashTables/separate_chaining_ht.h"
#include "Utils/utils.h"

#ifdef INSTRUMENT
Stats stats;
#endif

int main() {
    AbstractHt *ht = new SeparateChainingHt(5, 1.5);
    for (uint32_t i = 0; i < 1000000; i++) {
        char *key = random_string(5);
        char *value = random_string(10);
        ht->add_item(key, 5, value, 10);
        delete key;
        delete value;
    }
    for (uint32_t i = 0; i < 10000000; i++) {
        char *key = random_string(5);
        ht->get_item(key, 5);
        delete key;
    }

#ifdef INSTRUMENT
    std::cout << stats.add_time.count() << std::endl;
    std::cout << stats.get_time.count() << std::endl;
    std::cout << stats.expand_time.count() << std::endl;
#endif

}

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
    for (uint32_t i = 0; i < 1000000; i++) {
        char *key = random_string(5);
        ht->get_item(key, 5);
        delete key;
    }

#ifdef INSTRUMENT
    stats.printGetStats();
    stats.printAddStats();
    stats.printExpandStats();
#endif

    /*delete ht;
    ht = new SeparateChainingHt(5, 1.5);
    ht->add_item("test", 4, "lol", 3);
    ht->add_item("test2", 5, "lol2", 4);
    ht->add_item("test3", 5, "lol3", 4);
    ht->add_item("test4", 5, "lol4", 4);
    ht->add_item("test5", 5, "lol5", 4);
    ht->add_item("test6", 5, "lol6", 4);
    ht->add_item("test7", 5, "lol7", 4);
    ht->delete_item("test4", 5);
    std::cout << (char *)ht->get_item("test", 4) << std::endl;
    std::cout << (char *)ht->get_item("test2", 5) << std::endl;
    std::cout << (char *)ht->get_item("test3", 5) << std::endl;
    std::cout << ht->get_item("test4", 5) << std::endl;
    std::cout << (char *)ht->get_item("test5", 5) << std::endl;
    std::cout << (char *)ht->get_item("test6", 5) << std::endl;
    std::cout << (char *)ht->get_item("test7", 5) << std::endl;*/
}

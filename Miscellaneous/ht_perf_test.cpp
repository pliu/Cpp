//
// Created by Peng on 6/14/2017.
//

#include <cstdio>
#include "HashTables/separate_chaining_ht.h"

int main() {
    SeparateChainingHt *scht = new SeparateChainingHt(5, 1.5);
    scht->add_item("key", 3, "value", 5);
    printf("%s\n", scht->get_item("key", 3));
    printf("%d\n", scht->size());
    scht->set_item("keg", 3, "omgwtf", 6);
    printf("%s\n", scht->get_item("keg", 3));
    printf("%d\n", scht->size());
    scht->set_item("ket", 3, "omgabc", 6);
    scht->set_item("kes", 3, "omgbbq", 6);
    scht->set_item("keh", 3, "ggwtf", 5);
    scht->set_item("kea", 3, "ha", 2);
    scht->set_item("kep", 3, "quip", 4);
    scht->set_item("kel", 3, "linked", 6);
    scht->delete_item("key", 3);
    printf("%d\n", scht->size());
    printf("%s\n", scht->get_item("keh", 3));
}

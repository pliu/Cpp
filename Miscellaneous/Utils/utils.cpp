//
// Created by Peng on 6/15/2017.
//

#include <cstdint>
#include <cstdlib>
#include "utils.h"

static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

char* random_string(uint8_t len) {
    char *s = (char*)malloc(len);
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return s;
}

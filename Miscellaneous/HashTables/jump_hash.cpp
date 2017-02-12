//
// Created by Peng on 6/13/2017.
//

#include <cstdio>
#include "jump_hash.h"

JumpHash::JumpHash(int32_t num_buckets) {
    buckets = new std::vector<uint64_t>[num_buckets];
    this->num_buckets = num_buckets;
}

JumpHash::~JumpHash() {
    delete[] buckets;
}

void JumpHash::add_key(uint64_t key) {
    int32_t bucket_index = jump_hash(key);
    buckets[bucket_index].push_back(key);
}

bool JumpHash::key_exists(uint64_t key) {
    int32_t bucket_index = jump_hash(key);
    for (std::vector<uint64_t>::iterator it = buckets[bucket_index].begin(); it != buckets[bucket_index].end(); it++) {
        if (key == *it) {
            return true;
        }
    }
    return false;
}

void JumpHash::add_bucket() {
    int moved = 0;
    std::vector<uint64_t> *new_buckets = new std::vector<uint64_t>[++num_buckets];
    for (int32_t i = 0; i < num_buckets - 1; i++) {
        for (std::vector<uint64_t>::iterator it = buckets[i].begin(); it != buckets[i].end(); it++) {
            int32_t bucket_index = jump_hash(*it);
            if (i != bucket_index) {
                moved++;
            }
            new_buckets[bucket_index].push_back(*it);
        }
    }
    printf("%d items moved\n", moved);
    delete[] buckets;
    buckets = new_buckets;
}

void JumpHash::print_sizes() {
    for (int32_t i = 0; i < num_buckets; i++) {
        printf("Bucket #%d: %d\n", i, buckets[i].size());
    }
}

int32_t JumpHash::jump_hash(uint64_t key) {
    int64_t b = -1, j = 0;
    while (j < num_buckets) {
        b = j;
        key = key * 2862933555777941757ULL + 1;
        j = (b + 1) * (double(1LL << 31) / double((key >> 33) + 1));
    }
    return b;
}

//
// Created by Peng on 6/13/2017.
//

#ifndef CPP_JUMP_HASH_H
#define CPP_JUMP_HASH_H

#include <cstdint>
#include <vector>

class JumpHash {
public:
    JumpHash(int32_t num_buckets);

    ~JumpHash();

    void add_key(uint64_t key);

    bool key_exists(uint64_t key);

    void add_bucket();

    void print_sizes();

private:
    std::vector<uint64_t> *buckets;
    int32_t num_buckets;

    int32_t jump_hash(uint64_t key);
};

#endif //CPP_JUMP_HASH_H

//
// Created by Peng on 6/14/2017.
//

#ifndef CPP_SEPARATE_CHAINING_HT_H
#define CPP_SEPARATE_CHAINING_HT_H

#include <cstdint>
#include "abstract_ht.h"

namespace {

    class Node {
    public:
        Node(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

        ~Node();

        void replace(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

        uint32_t key_len;
        void *key;
        void *value;
        Node *next = NULL;

    private:
        void set(const void *key, uint32_t key_len, const void *value, uint32_t value_len);
    };

}

class SeparateChainingHt : public AbstractHt {
public:
    SeparateChainingHt(uint32_t num_buckets, double load_threshold);

    ~SeparateChainingHt();

    bool add_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

    void set_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

    const void *get_item(const void *key, uint32_t len);

    void delete_item(const void *key, uint32_t len);

private:
    Node **bucket_array;
    double load_threshold;

    void insert_node(uint32_t bucket_index, Node *node);

    void expand_table();

    static uint32_t get_bucket_index(const void *key, uint32_t key_len, uint32_t num_buckets);

    static Node **find_item(Node **bucket_array, uint32_t bucket_index, const void *key, uint32_t len);

    static void clear_bucket_array(Node **bucket_array, uint32_t num_buckets);
};

#endif //CPP_SEPARATE_CHAINING_HT_H

/**
 *
 */

#ifndef CPP_SEPARATE_CHAINING_HT_H
#define CPP_SEPARATE_CHAINING_HT_H


#include <cstdint>
#include "abstract_ht.h"

namespace {

    class Node {
    public:
        Node(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

        ~Node() {}

        void replace(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

        Node *next = NULL;
        uint32_t key_len;
        uint32_t value_len;
        char key[5];
        char value[10];
    };

}

class SeparateChainingHt : public AbstractHt {
public:
    SeparateChainingHt(uint32_t num_buckets, double load_threshold);

    ~SeparateChainingHt();

    bool add_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

    void set_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

    const void *get_item(const void *key, uint32_t len) const;

    void delete_item(const void *key, uint32_t len);

    uint16_t *get_bucket_sizes();

private:
    Node **bucket_array;
    double load_threshold;

    void expand_table();

    void insert_node(uint32_t bucket_index, Node *node);

    static const uint32_t get_bucket_index(const void *key, uint32_t key_len, uint32_t num_buckets);

    static void find_node(Node **bucket_array, uint32_t bucket_index, const void *key, uint32_t len);
};


#endif //CPP_SEPARATE_CHAINING_HT_H

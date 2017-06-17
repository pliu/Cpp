/*
 *
 */

#ifndef CPP_OPEN_ADDRESSING_HT_H
#define CPP_OPEN_ADDRESSING_HT_H


#include <cstdint>
#include "abstract_ht.h"

#define SLOTS_PER_BUCKET 4

namespace {

    class Entry {
    public:
        Entry(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

        ~Entry();

        void replace(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

        uint32_t key_len;
        void *key;
        void *value;

    private:
        void set(const void *key, uint32_t key_len, const void *value, uint32_t value_len);
    };

    class BucketSlot {
    public:
        BucketSlot();

        ~BucketSlot() {}

        Entry* entry;
        char tag;
        char tombstone:1;
    };

}

class OpenAddressingHt : public AbstractHt {
public:
    OpenAddressingHt(uint32_t num_buckets, double load_threshold);

    ~OpenAddressingHt();

    bool add_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

    void set_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

    const void *get_item(const void *key, uint32_t len) const;

    void delete_item(const void *key, uint32_t len);

private:
    BucketSlot** bucket_array;

    void expand_table();

    static const uint32_t get_bucket_index(const void *key, uint32_t key_len, uint32_t num_buckets);
};


#endif //CPP_OPEN_ADDRESSING_HT_H

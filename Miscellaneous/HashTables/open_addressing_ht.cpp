#include <cstdlib>
#include <cstring>
#include "open_addressing_ht.h"
#include "murmur3_hash.h"

#ifdef DEBUG
#include <cstdio>
#endif

#ifdef INSTRUMENT
#include <chrono>

extern Stats stats;
#endif

Entry::Entry(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
    replace(key, key_len, value, value_len);
}

inline void Entry::replace(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
    this->key_len = key_len;
    this->value_len = value_len;
    memcpy(this->key, key, key_len);
    memcpy(this->value, value, value_len);
}

BucketSlot::BucketSlot() {
    entry = NULL;
}

OpenAddressingHt::OpenAddressingHt(uint32_t num_buckets, double load_threshold) {
    this->num_buckets = num_buckets;
    bucket_array = new BucketSlot *[num_buckets];
    for (uint32_t i = 0; i < num_buckets; i++) {
        bucket_array[i] = new BucketSlot[SLOTS_PER_BUCKET]();
    }
    this->load_threshold = load_threshold;
}

OpenAddressingHt::~OpenAddressingHt() {
    for (uint32_t i = 0; i < num_buckets; i++) {
        delete[] bucket_array[i];
    }
}

bool OpenAddressingHt::add_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {

#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif

    uint32_t *bucket_indices = get_bucket_indices(key, key_len, num_buckets);

    num_items++;

#ifdef INSTRUMENT
    stats.add_time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -
                                                                           start);
#endif

    if ((double) num_items / (num_buckets * SLOTS_PER_BUCKET) >= load_threshold) {
        expand_table();
    }
    return true;
}

void OpenAddressingHt::set_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {

#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif

    num_items++;

#ifdef INSTRUMENT
    stats.set_time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -
                                                                           start);
#endif

    if ((double) num_items / (num_buckets * SLOTS_PER_BUCKET) >= load_threshold) {
        expand_table();
    }
}

const void *OpenAddressingHt::get_item(const void *key, uint32_t len) const {

#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif


#ifdef INSTRUMENT
    stats.get_time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -
                                                                           start);
#endif

    return NULL;
}

void OpenAddressingHt::delete_item(const void *key, uint32_t len) {

#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif


#ifdef INSTRUMENT
    stats.delete_time += std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start);
#endif

}

void OpenAddressingHt::expand_table() {

#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif


#ifdef INSTRUMENT
    stats.expand_time += std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start);
#endif

}

uint32_t *OpenAddressingHt::get_bucket_indices(const void *key, uint32_t key_len, uint32_t num_buckets) {
    uint64_t *ret = new uint64_t[2];
    MurmurHash3_x64_128(key, key_len, 0, ret);
    ret[0] %= num_buckets;
    ret[1] %= num_buckets;
    return (uint32_t *) ret;
}

Entry* OpenAddressingHt::find_item(BucketSlot **bucket_array, uint32_t bucket_index, const void *key, uint32_t len) {

}

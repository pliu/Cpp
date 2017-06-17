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
    set(key, key_len, value, value_len);
}

Entry::~Entry() {
    delete key;
    delete value;
}

void Entry::replace(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
    delete this->key;
    delete this->value;
    set(key, key_len, value, value_len);
}

BucketSlot::BucketSlot() {
    entry = NULL;
}

inline void Entry::set(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
    this->key_len = key_len;
    this->key = malloc(key_len);
    memcpy(this->key, key, key_len);
    this->value = malloc(value_len);
    memcpy(this->value, value, value_len);
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

const uint32_t OpenAddressingHt::get_bucket_index(const void *key, uint32_t key_len, uint32_t num_buckets) {

}

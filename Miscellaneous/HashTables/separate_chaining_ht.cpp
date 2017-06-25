#include <cstdlib>
#include <cstring>
#include "separate_chaining_ht.h"
#include "murmur3_hash.h"

#ifdef INSTRUMENT
#include <chrono>

extern Stats stats;
#endif

static Node *found[2];

Node::Node(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
    replace(key, key_len, value, value_len);
}

inline void Node::replace(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
    this->key_len = key_len;
    this->value_len = value_len;
    memcpy(this->key, key, key_len + 1);
    memcpy(this->value, value, value_len + 1);
}

SeparateChainingHt::SeparateChainingHt(uint32_t num_buckets, double load_threshold) {
    this->num_buckets = num_buckets;
    bucket_array = new Node *[num_buckets]();
    this->load_threshold = load_threshold;
}

SeparateChainingHt::~SeparateChainingHt() {
    for (uint32_t i = 0; i < num_buckets; i++) {
        Node *current = bucket_array[i];
        while (current != NULL) {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }
}

bool SeparateChainingHt::add_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif

    uint32_t bucket_index = get_bucket_index(key, key_len, num_buckets);
    find_node(bucket_array, bucket_index, key, key_len);
    if (found[0] != NULL) {

#ifdef INSTRUMENT
        stats.add_time.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now() - start));
#endif

        return false;
    }
    insert_node(bucket_index, new Node(key, key_len, value, value_len));
    num_items++;

#ifdef INSTRUMENT
    stats.add_time.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start));
#endif

    if ((double) num_items / num_buckets >= load_threshold) {
        expand_table();
    }
    return true;
}

void SeparateChainingHt::set_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif

    uint32_t bucket_index = get_bucket_index(key, key_len, num_buckets);
    find_node(bucket_array, bucket_index, key, key_len);
    if (found[0] != NULL) {
        found[0]->replace(key, key_len, value, value_len);

#ifdef INSTRUMENT
        stats.set_time.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now() - start));
#endif

        return;
    }
    insert_node(bucket_index, new Node(key, key_len, value, value_len));
    num_items++;

#ifdef INSTRUMENT
    stats.set_time.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start));
#endif

    if ((double) num_items / num_buckets >= load_threshold) {
        expand_table();
    }
}

const void *SeparateChainingHt::get_item(const void *key, uint32_t len) const {
#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif

    uint32_t bucket_index = get_bucket_index(key, len, num_buckets);
    find_node(bucket_array, bucket_index, key, len);

#ifdef INSTRUMENT
    stats.get_time.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start));
#endif

    if (found[0] == NULL) {
        return NULL;
    }
    return found[0]->value;
}

void SeparateChainingHt::delete_item(const void *key, uint32_t len) {
#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif

    uint32_t bucket_index = get_bucket_index(key, len, num_buckets);
    find_node(bucket_array, bucket_index, key, len);

    if (found[0] != NULL) {
        if (found[1] != NULL) {
            found[1]->next = found[0]->next;
        } else {
            bucket_array[bucket_index] = found[0]->next;
        }
        delete found[0];
        num_items--;
    }

#ifdef INSTRUMENT
    stats.delete_time.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start));
#endif
}

void SeparateChainingHt::expand_table() {
#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif

    uint32_t old_num = num_buckets;
    num_buckets *= 2;
    Node **old_array = bucket_array;
    bucket_array = new Node *[num_buckets]();
    for (uint32_t i = 0; i < old_num; i++) {
        Node *node_ptr = old_array[i], *next_ptr = node_ptr == NULL ? NULL : node_ptr->next;
        while (node_ptr != NULL) {
            uint32_t bucket_index = get_bucket_index(node_ptr->key, node_ptr->key_len, num_buckets);
            insert_node(bucket_index, node_ptr);
            node_ptr = next_ptr;
            if (node_ptr != NULL) {
                next_ptr = next_ptr->next;
            }
        }
    }
    delete old_array;

#ifdef INSTRUMENT
    stats.expand_time.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start));
#endif
}

inline void SeparateChainingHt::insert_node(uint32_t bucket_index, Node *node) {
    Node *old = bucket_array[bucket_index];
    bucket_array[bucket_index] = node;
    node->next = old;
}

inline const uint32_t SeparateChainingHt::get_bucket_index(const void *key, uint32_t key_len, uint32_t num_buckets) {
    uint64_t hash_out[2];
    MurmurHash3_x64_128(key, key_len, 0, &hash_out);
    return (uint32_t) (hash_out[0] % num_buckets);
}

void SeparateChainingHt::find_node(Node **bucket_array, uint32_t bucket_index, const void *key, uint32_t len) {
    found[0] = NULL;
    found[1] = NULL;
    found[0] = bucket_array[bucket_index];
    while (found[0] != NULL) {
        if (len == found[0]->key_len && memcmp(found[0]->key, key, len) == 0) {
            break;
        }
        found[1] = found[0];
        found[0] = found[0]->next;
    }
}

uint16_t *SeparateChainingHt::get_bucket_sizes() {
    uint16_t *bucket_sizes = new uint16_t[num_buckets]();
    for (uint32_t i = 0; i < num_buckets; i++) {
        Node *node_ptr = bucket_array[i];
        while (node_ptr != NULL) {
            bucket_sizes[i]++;
            node_ptr = node_ptr->next;
        }
    }
    return bucket_sizes;
}

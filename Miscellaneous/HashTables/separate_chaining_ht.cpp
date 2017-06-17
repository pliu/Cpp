//
// Created by Peng on 6/14/2017.
//

#include <cstdlib>
#include <cstring>
#include "separate_chaining_ht.h"
#include "murmur3_hash.h"

#ifdef DEBUG
#include <cstdio>
#endif

#ifdef INSTRUMENT

#include <chrono>

Stats stats;
#endif

Node::Node(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
    set(key, key_len, value, value_len);
}

Node::~Node() {
    if (next != NULL) {
        delete next;
    }
    delete key;
    delete value;
}

void Node::replace(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
    delete this->key;
    delete this->value;
    set(key, key_len, value, value_len);
}

void Node::set(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
    this->key_len = key_len;
    this->key = malloc(key_len);
    memcpy(this->key, key, key_len);
    this->value = malloc(value_len);
    memcpy(this->value, value, value_len);
}

SeparateChainingHt::SeparateChainingHt(uint32_t num_buckets, double load_threshold) {
    this->num_buckets = num_buckets;
    bucket_array = new Node *[num_buckets]();
    this->load_threshold = load_threshold;
}

SeparateChainingHt::~SeparateChainingHt() {
    for (uint32_t i = 0; i < num_buckets; i++) {
        if (bucket_array[i] != NULL) {
            delete bucket_array[i];
        }
    }
}

bool SeparateChainingHt::add_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {

#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif

    uint32_t bucket_index = get_bucket_index(key, key_len, num_buckets);
    Node **results = find_item(bucket_array, bucket_index, key, key_len);

#ifdef DEBUG
    printf("add_item %.*s - %.*s: %d\n", key_len, key, value_len, value, bucket_index);
#endif

    Node *res = results[0];
    delete results;
    if (res != NULL) {
        return false;
    }
    Node *node = new Node(key, key_len, value, value_len);
    insert_node(bucket_index, node);
    num_items++;

#ifdef INSTRUMENT
    stats.add_time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -
                                                                           start);
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
    Node **results = find_item(bucket_array, bucket_index, key, key_len);

#ifdef DEBUG
    printf("set_item %.*s - %.*s: %d\n", key_len, key, value_len, value, bucket_index);
#endif

    Node *res = results[0];
    delete results;
    if (res != NULL) {
        res->replace(key, key_len, value, value_len);
        return;
    }
    Node *node = new Node(key, key_len, value, value_len);
    insert_node(bucket_index, node);
    num_items++;

#ifdef INSTRUMENT
    stats.set_time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -
                                                                           start);
#endif

    if ((double) num_items / num_buckets > load_threshold) {
        expand_table();
    }
}

const void *SeparateChainingHt::get_item(const void *key, uint32_t len) const {

#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif

    uint32_t bucket_index = get_bucket_index(key, len, num_buckets);

#ifdef DEBUG
    printf("get_item %.*s: %d\n", len, key, bucket_index);
#endif

    Node **results = find_item(bucket_array, bucket_index, key, len);
    Node *ret = results[0];
    delete results;
    if (ret == NULL) {
        return NULL;
    }

#ifdef INSTRUMENT
    stats.get_time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() -
                                                                           start);
#endif

    return ret->value;
}

void SeparateChainingHt::delete_item(const void *key, uint32_t len) {

#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif

    uint32_t bucket_index = get_bucket_index(key, len, num_buckets);
    Node **results = find_item(bucket_array, bucket_index, key, len);

#ifdef DEBUG
    printf("delete_item %.*s: %d\n", len, key, bucket_index);
#endif

    if (results[0] != NULL) {
        if (results[1] != NULL) {
            results[1]->next = results[0]->next;
        } else {
            bucket_array[bucket_index] = NULL;
        }
        delete results[0];
        num_items--;
    }
    delete results;

#ifdef INSTRUMENT
    stats.delete_time += std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start);
#endif

}

void SeparateChainingHt::expand_table() {

#ifdef INSTRUMENT
    auto start = std::chrono::high_resolution_clock::now();
#endif

    Node **old_array = bucket_array;
    uint32_t old_num = num_buckets;
    num_buckets *= 2;

#ifdef DEBUG
    printf("expand_table: %d -> %d\n", old_num, num_buckets);
#endif

    bucket_array = new Node *[num_buckets]();
    for (uint32_t i = 0; i < old_num; i++) {
        Node *node_ptr = old_array[i], *next_ptr = node_ptr == NULL ? NULL : node_ptr->next;
        while (node_ptr != NULL) {
            uint32_t bucket_index = get_bucket_index(node_ptr->key, node_ptr->key_len, num_buckets);

#ifdef DEBUG
            printf("expand_table %.*s: %d\n", node_ptr->key_len, node_ptr->key, bucket_index);
#endif

            insert_node(bucket_index, node_ptr);
            node_ptr = next_ptr;
            if (node_ptr != NULL) {
                next_ptr = next_ptr->next;
            }
        }
    }
    delete old_array;

#ifdef INSTRUMENT
    stats.expand_time += std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start);
#endif

}

void SeparateChainingHt::insert_node(uint32_t bucket_index, Node *node) {
    Node *old = bucket_array[bucket_index];
    bucket_array[bucket_index] = node;
    node->next = old;
}

const uint32_t SeparateChainingHt::get_bucket_index(const void *key, uint32_t key_len, uint32_t num_buckets) {
    uint64_t hash_out[2];
    MurmurHash3_x64_128(key, key_len, 0, &hash_out);
    return (uint32_t) (hash_out[0] % num_buckets);
}

Node **SeparateChainingHt::find_item(Node **bucket_array, uint32_t bucket_index, const void *key, uint32_t len) {
    Node **ret = new Node *[2]();
    ret[0] = bucket_array[bucket_index];
    while (ret[0] != NULL) {
        if (len == ret[0]->key_len && memcmp(ret[0]->key, key, len) == 0) {
            break;
        }
        ret[1] = ret[0];
        ret[0] = ret[0]->next;
    }
    return ret;
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

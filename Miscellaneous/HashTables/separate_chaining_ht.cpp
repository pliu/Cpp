//
// Created by Peng on 6/14/2017.
//

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "separate_chaining_ht.h"
#include "murmur3_hash.h"

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
    clear_bucket_array(bucket_array, num_buckets);
}

bool SeparateChainingHt::add_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
    uint32_t bucket_index = get_bucket_index(key, key_len, num_buckets);
    Node **results = find_item(bucket_array, bucket_index, key, key_len);
    if (results[0] != NULL) {
        return false;
    }
    Node *node = new Node(key, key_len, value, value_len);
    insert_node(bucket_index, node);
    num_items++;
    return true;
}

void SeparateChainingHt::set_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len) {
    uint32_t bucket_index = get_bucket_index(key, key_len, num_buckets);
    Node **results = find_item(bucket_array, bucket_index, key, key_len);
    if (results[0] != NULL) {
        results[0]->replace(key, key_len, value, value_len);
        return;
    }
    Node *node = new Node(key, key_len, value, value_len);
    insert_node(bucket_index, node);
    num_items++;
}

const void *SeparateChainingHt::get_item(const void *key, uint32_t len) {
    uint32_t bucket_index = get_bucket_index(key, len, num_buckets);
    Node **results = find_item(bucket_array, bucket_index, key, len);
    if (results[0] == NULL) {
        return NULL;
    }
    return results[0]->value;
}

void SeparateChainingHt::delete_item(const void *key, uint32_t len) {
    uint32_t bucket_index = get_bucket_index(key, len, num_buckets);
    Node **results = find_item(bucket_array, bucket_index, key, len);
    if (results[0] != NULL) {
        if (results[1] != NULL) {
            results[1]->next = results[0]->next;
        } else {
            bucket_array[bucket_index] = NULL;
        }
        delete results[0];
        num_items--;
    }
}

void SeparateChainingHt::insert_node(uint32_t bucket_index, Node *node) {
    Node *old = bucket_array[bucket_index];
    bucket_array[bucket_index] = node;
    node->next = old;
    if ((double) num_items / num_buckets > load_threshold) {
        expand_table();
    }
}

void SeparateChainingHt::expand_table() {
    printf("expand %d\n", num_items);
    Node **old_array = bucket_array;
    uint32_t old_num = num_buckets;
    num_buckets *= 2;
    bucket_array = new Node *[num_buckets];
    for (uint32_t i = 0; i < old_num; i++) {
        Node *node_ptr = old_array[i];
        while (node_ptr != NULL) {
            uint32_t bucket_index = get_bucket_index(node_ptr->key, node_ptr->key_len, num_buckets);
            insert_node(bucket_index, node_ptr);
            node_ptr = node_ptr->next;
        }
    }
}

uint32_t SeparateChainingHt::get_bucket_index(const void *key, uint32_t key_len, uint32_t num_buckets) {
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

void SeparateChainingHt::clear_bucket_array(Node **bucket_array, uint32_t num_buckets) {
    for (uint32_t i = 0; i < num_buckets; i++) {
        if (bucket_array[i] != NULL) {
            delete bucket_array[i];
        }
    }
}

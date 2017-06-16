//
// Created by Peng on 6/14/2017.
//

#ifndef CPP_ABSTRACT_HT_H
#define CPP_ABSTRACT_HT_H


class AbstractHt {
public:
    uint32_t size() { return num_items; }

    uint32_t buckets() { return num_buckets; }

    virtual bool add_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len) = 0;

    virtual void set_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len) = 0;

    virtual const void *get_item(const void *key, uint32_t len) const = 0;

    virtual void delete_item(const void *key, uint32_t len) = 0;

protected:
    uint32_t num_buckets;
    uint32_t num_items;
};


#endif //CPP_ABSTRACT_HT_H

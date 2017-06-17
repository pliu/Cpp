#ifndef CPP_ABSTRACT_HT_H
#define CPP_ABSTRACT_HT_H


#include <chrono>

#ifdef INSTRUMENT
struct Stats {
    std::chrono::nanoseconds get_time;
    std::chrono::nanoseconds add_time;
    std::chrono::nanoseconds set_time;
    std::chrono::nanoseconds delete_time;
    std::chrono::nanoseconds expand_time;
};
#endif

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
    double load_threshold;

    virtual void expand_table() = 0;
};


#endif //CPP_ABSTRACT_HT_H

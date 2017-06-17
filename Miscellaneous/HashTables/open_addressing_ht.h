//
// Created by Peng on 6/16/2017.
//

#ifndef CPP_OPEN_ADDRESSING_HT_H
#define CPP_OPEN_ADDRESSING_HT_H


class OpenAddressingHt : public AbstractHt {
public:
    OpenAddressingHt(uint32_t num_buckets, double load_threshold);

    ~OpenAddressingHt();

    bool add_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

    void set_item(const void *key, uint32_t key_len, const void *value, uint32_t value_len);

    const void *get_item(const void *key, uint32_t len) const;

    void delete_item(const void *key, uint32_t len);

private:
    void expand_table();
};


#endif //CPP_OPEN_ADDRESSING_HT_H

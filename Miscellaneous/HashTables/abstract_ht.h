#ifndef CPP_ABSTRACT_HT_H
#define CPP_ABSTRACT_HT_H


#include <chrono>


#ifdef INSTRUMENT

#include <iostream>
#include <vector>
#include <algorithm>

class Stats {
public:
    std::vector<std::chrono::nanoseconds> get_time;
    std::vector<std::chrono::nanoseconds> add_time;
    std::vector<std::chrono::nanoseconds> set_time;
    std::vector<std::chrono::nanoseconds> delete_time;
    std::vector<std::chrono::nanoseconds> expand_time;

    void printGetStats() {
        std::vector<std::chrono::nanoseconds> stats = getStats(&get_time);
        std::cout << "Get (mean, P9999, max, total): ";
        printStats(stats);
    }

    void printAddStats() {
        std::vector<std::chrono::nanoseconds> stats = getStats(&add_time);
        std::cout << "Add (mean, P9999, max, total): ";
        printStats(stats);
    }

    void printSetStats() {
        std::vector<std::chrono::nanoseconds> stats = getStats(&set_time);
        std::cout << "Set (mean, P9999, max, total): ";
        printStats(stats);
    }

    void printDeleteStats() {
        std::vector<std::chrono::nanoseconds> stats = getStats(&delete_time);
        std::cout << "Delete (mean, P9999, max, total): ";
        printStats(stats);
    }

    void printExpandStats() {
        std::chrono::nanoseconds total = getTotal(&expand_time);
        std::cout << "Expand (total): " << total.count() << std::endl;
    }

private:
    // Returns the mean, P9999, max, and total in a given record
    static std::vector<std::chrono::nanoseconds> getStats(std::vector<std::chrono::nanoseconds> *record) {
        std::vector<std::chrono::nanoseconds> ret;
        std::sort(record->begin(), record->end());
        std::chrono::nanoseconds total = getTotal(record);
        std::chrono::nanoseconds mean = total / record->size();
        ret.push_back(mean);
        std::chrono::nanoseconds p9999 = record->at(record->size() * 0.9999);
        ret.push_back(p9999);
        std::chrono::nanoseconds max = record->at(record->size() - 1);
        ret.push_back(max);
        ret.push_back(total);
        return ret;
    }

    static std::chrono::nanoseconds getTotal(std::vector<std::chrono::nanoseconds> *record) {
        std::chrono::nanoseconds total;
        for (std::vector<std::chrono::nanoseconds>::iterator it = record->begin(); it != record->end(); it++) {
            total += *it;
        }
        return total;
    }

    static void printStats(const std::vector<std::chrono::nanoseconds> &stats) {
        for (const std::chrono::nanoseconds &time : stats) {
            std::cout << time.count() << " | ";
        }
        std::cout << std::endl;
    }
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
    uint32_t num_items = 0;
};


#endif //CPP_ABSTRACT_HT_H

#include <cstdio>
#include <cstdint>
#include <vector>

class JumpHash {
public:
    explicit JumpHash(int32_t num_buckets) {
        buckets = new std::vector<uint64_t>[num_buckets];
        this->num_buckets = num_buckets;
    }

    ~JumpHash() {
        delete[] buckets;
    }

    void add_key(uint64_t key) {
        int32_t bucket_index = jump_hash(key);
        buckets[bucket_index].push_back(key);
    }

    bool key_exists(uint64_t key) {
        int32_t bucket_index = jump_hash(key);
        for (unsigned long &it : buckets[bucket_index]) {
            if (key == it) {
                return true;
            }
        }
        return false;
    }

    void add_buckets(int32_t num_add) {
        int moved = 0;
        num_buckets += num_add;
        auto *new_buckets = new std::vector<uint64_t>[num_buckets];
        for (int32_t i = 0; i < num_buckets - num_add; i++) {
            for (std::vector<uint64_t>::iterator it = buckets[i].begin(); it != buckets[i].end(); it++) {
                int32_t bucket_index = jump_hash(*it);
                if (i != bucket_index) {
                    moved++;
                }
                new_buckets[bucket_index].push_back(*it);
            }
        }
        printf("%d items moved\n", moved);
        delete[] buckets;
        buckets = new_buckets;
    }

    void print_sizes() {
        for (int32_t i = 0; i < num_buckets; i++) {
            printf("Bucket #%d: %lu\n", i, buckets[i].size());
        }
    }

private:
    std::vector<uint64_t> *buckets;
    int32_t num_buckets;

    int32_t jump_hash(uint64_t key) {
        int64_t b = -1, j = 0;
        while (j < num_buckets) {
            b = j;
            key = key * 2862933555777941757ULL + 1;
            j = (b + 1) * (double(1LL << 31) / double((key >> 33) + 1));
        }
        return b;
    }
};


int main() {
    auto *jh = new JumpHash(10);
    uint64_t num_keys = 100000ULL;
    for (uint64_t i = 0; i < num_keys; i++) {
        jh->add_key(i);
    }
    jh->print_sizes();
    jh->add_buckets(10);
    printf("*** AFTER BUCKET(S) ADDED ***\n");
    jh->print_sizes();
    for (uint64_t i = 0; i <= num_keys; i++) {
        if (!jh->key_exists(i)) {
            printf("Could not find %d", i);
        }
    }
}

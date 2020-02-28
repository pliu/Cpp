#include <cstdint>
#include <cstdio>

class FileIO {
   public:
    FileIO(char *path, uint32_t max_size, uint32_t page_size) {
        this->max_size = max_size;
        this->page_size = page_size;
        fp = fopen(path, "wb+");
    }

    ~FileIO() {
        fclose(fp);
    }

    void write(char *data, uint32_t size) {
        uint32_t cur = 0;
        while (cur < size) {
            uint32_t write_size = size - cur > page_size ? page_size : size - cur;
            fwrite(data + cur, write_size, 1, fp);
            cur += write_size;
            current_position += write_size;
            if (current_position >= max_size) {
                fseek(fp, 0, SEEK_SET);
                current_position = 0;
            }
        }
        uint32_t rem = current_position % page_size;
        if (rem != 0) {
            uint32_t buffer_size = page_size - rem;
            char buffer[buffer_size] = {NULL};
            current_position = (current_position + buffer_size) % max_size;
            fwrite(buffer, buffer_size, 1, fp);
        }
    }

    void read() {
        char in;
        for (uint32_t i = 0; i < max_size; i++) {
            fseek(fp, i, SEEK_SET);
            int check = fread(&in, 1, 1, fp);
            if (check != 1) {
                break;
            }
            printf("%c", in);
        }
        printf("\n");
        fseek(fp, current_position, SEEK_SET);
    }

   private:
    uint32_t max_size;
    uint32_t page_size;
    FILE *fp;
    uint32_t current_position = 0;
};

int main() {
    auto *fio = new FileIO("./tmp.test", 1 << 8, 1 << 3);
    fio->write("This is an initial test", 23);
    fio->write("This is an initial test2", 24);
    fio->read();
    for (uint32_t i = 0; i < 6; i++) {
        fio->write("abcdefghijklmnopqrstuvwxyz", 26);
    }
    fio->read();
    fio->write("abcdefghijklmnopqrstuvwxyz", 26);
    fio->write("abcdefghijklmnopqrstuvwxyz", 26);
    fio->read();
}

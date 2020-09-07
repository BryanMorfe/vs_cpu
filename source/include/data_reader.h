#ifndef _EV_DATA_READER_H_
#define _EV_DATA_READER_H_

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace evoluti {
class data_reader {
public:
    data_reader(const char* data_file);
    ~data_reader();

    void read();

    template <typename T>
    void get_vector(std::vector<T>& v) const;

    uint8_t* get_raw(std::size_t* size);

private:
    void realloc(std::size_t size);
    const char* filename;
    uint8_t* data;
    std::size_t data_size;
};
}  // namespace evoluti

template <typename T>
void evoluti::data_reader::get_vector(std::vector<T>& v) const {
    if (data_size % sizeof(T) != 0)
        std::runtime_error("Misaligned data for proposed vector type.");

    v.assign((T*)data, (T*)data + (data_size / sizeof(T)));
}

#endif /* _EV_DATA_READER_H_ */
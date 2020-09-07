#include "data_reader.h"

#include <fcntl.h>
#include <unistd.h>

#include <cstring>
#include <stdexcept>

evoluti::data_reader::data_reader(const char* data_file) : data(nullptr), data_size() {
    filename = data_file;

    if (access(filename, F_OK) == -1)
        throw std::runtime_error("File does not exist. Cannot continue.");
}

evoluti::data_reader::~data_reader() {
    if (data != nullptr)
        delete[] data;
}

void evoluti::data_reader::read() {
    int fd;
    ssize_t bytes_read;
    static const size_t READ_SIZE = 4096;
    size_t buf_size;

    if (data == nullptr)
    {
        realloc(READ_SIZE);
        buf_size = READ_SIZE;
    }

    fd = open(filename, O_RDONLY);

    if (fd < 0)
        throw std::runtime_error("Failed to open file for data_reader. Sufficient permissions?");

    while ((bytes_read = ::read(fd, data + data_size, READ_SIZE)) > 0)
    {
        data_size += bytes_read;
        if (data_size + READ_SIZE > buf_size)
        {
            buf_size += buf_size;
            realloc(buf_size);
        }
    }
}

uint8_t* evoluti::data_reader::get_raw(std::size_t* size) {
    *size = data_size;

    return data;
}

void evoluti::data_reader::realloc(std::size_t size) {
    if (data != nullptr)
    {
        uint8_t* tmp = new uint8_t[size];

        if (tmp == nullptr)
            throw std::runtime_error("unable to allocate sufficient memory for data_reader.");

        std::memcpy(tmp, data, size > data_size ? data_size : size);
        delete[] data;
        data = tmp;
    } else
    {
        data = new uint8_t[size];

        if (data == nullptr)
            throw std::runtime_error("unable to allocate sufficient memory for data_reader.");
    }
}
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_ITEMS (10485760)

template <typename T>
T get_rand(T max) {
    return (T)(rand() % ((int)max + 1));
}

int main() {
    int fd;
    uint8_t* data8;
    uint32_t* data32;
    float* dataFloat;
    double* dataDouble;
    ssize_t writtenSize;

    srand(time(NULL));

    data8 = new uint8_t[NUM_ITEMS]();

    if (data8 == nullptr)
        throw "can't allocate";

    fd = open("data.uint8", O_RDWR | O_CREAT, 0664);

    if (fd < 0)
        throw "failed to open|create data8 file";

    for (int i = 0; i < NUM_ITEMS; ++i)
    {
        data8[i] = get_rand<uint16_t>(255);
    }

    writtenSize = write(fd, data8, NUM_ITEMS);

    if (writtenSize != NUM_ITEMS)
        throw "failed to write data8";

    delete[] data8;

    //--------------------------------------------------

    data32 = new uint32_t[NUM_ITEMS]();

    if (data32 == nullptr)
        throw "can't allocate";

    fd = open("data.uint32", O_RDWR | O_CREAT, 0664);

    if (fd < 0)
        throw "failed to open|create data32 file";

    for (int i = 0; i < NUM_ITEMS; ++i)
    {
        data32[i] = get_rand<uint32_t>(10000);
    }

    writtenSize = write(fd, data32, NUM_ITEMS * sizeof(uint32_t));

    if (writtenSize != NUM_ITEMS * sizeof(uint32_t))
        throw "failed to write data32";

    delete[] data32;

    //--------------------------------------------------

    dataFloat = new float[NUM_ITEMS]();

    if (dataFloat == nullptr)
        throw "can't allocate";

    fd = open("data.float", O_RDWR | O_CREAT, 0664);

    if (fd < 0)
        throw "failed to open|create dataFloat file";

    for (int i = 0; i < NUM_ITEMS; ++i)
    {
        dataFloat[i] = get_rand<float>(1000000);
    }

    writtenSize = write(fd, dataFloat, NUM_ITEMS * sizeof(float));

    if (writtenSize != NUM_ITEMS * sizeof(float))
        throw "failed to write dataFloat";

    delete[] dataFloat;

    //--------------------------------------------------

    dataDouble = new double[NUM_ITEMS]();

    if (dataDouble == nullptr)
        throw "can't allocate";

    fd = open("data.double", O_RDWR | O_CREAT, 0664);

    if (fd < 0)
        throw "failed to open|create dataDouble file";

    for (int i = 0; i < NUM_ITEMS; ++i)
    {
        dataDouble[i] = get_rand<double>(1000000);
    }

    writtenSize = write(fd, dataDouble, NUM_ITEMS * sizeof(double));

    if (writtenSize != NUM_ITEMS * sizeof(double))
        throw "failed to write dataDouble";

    delete[] dataDouble;

    return 0;
}
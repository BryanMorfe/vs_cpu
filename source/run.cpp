#include <getopt.h>

#include <cstring>
#include <iostream>
#include <thread>

#include "data_reader.h"
#include "proc_info.h"
#include "runner.h"

#define MAX_ADDR_LEN 120

#define CLT_MODE_STR "client"
#define SRV_MODE_STR "server"

#define _auto_unused auto __attribute__((unused))

enum RunnerMode
{
    ClientMode,
    ServerMode,

    UnknownMode,
};

enum Group : int
{
    SortSingleThreaded,
    SortMultiThreaded,
    SearchSingleThreaded,
    SearchMultiThreaded,
    MultiplySingleThreaded,
    MultiplyMultiThreaded,
    VectorialSingleThreaded,
    VectorialMultiThreaded,
};

static constexpr const char* GROUP_NAMES[] = {
    [SortSingleThreaded] = "Sort Single Threaded",
    [SortMultiThreaded] = "Sort Multi Threaded",
    [SearchSingleThreaded] = "Search Single Threaded",
    [SearchMultiThreaded] = "Search Multi Threaded",
    [MultiplySingleThreaded] = "Multiply Single Threaded",
    [MultiplyMultiThreaded] = "Multiply Multi Threaded",
    [VectorialSingleThreaded] = "Vectorial Single Threaded",
    [VectorialMultiThreaded] = "Vectorial Multi Threaded",
};

static int n_iter = 1000;
static int port = 5050;
static char addr[MAX_ADDR_LEN];
static RunnerMode mode = ClientMode;

template <typename T>
void vector_dot(const std::vector<T>& v, std::size_t start, std::size_t len) {
    for (std::size_t i = start; i < len; ++i)
        _auto_unused _ = v[i] * v[i] + v[i];
}

void get_opts(int argc, char* argv[]) {
    struct option long_opts[] = {
        {"addr", required_argument, 0, 'a'},
        {"iter", required_argument, 0, 'i'},
        {"mode", required_argument, 0, 'm'},
        {"port", required_argument, 0, 'p'},
    };
    int opt_idx;

    while (1)
    {
        int c = getopt_long(argc, argv, "a:i:m:p:", long_opts, &opt_idx);

        if (c == -1)
            break;

        switch (c)
        {
            case 'a':
                strcpy(addr, optarg);
                break;
            case 'i':
                sscanf(optarg, "%d", &n_iter);
                break;
            case 'm':
                if (strcasecmp(optarg, CLT_MODE_STR) == 0)
                    mode = ClientMode;
                else if (strcasecmp(optarg, SRV_MODE_STR) == 0)
                    mode = ServerMode;
                else
                    mode = UnknownMode;

                break;
            case 'p':
                sscanf(optarg, "%d", &port);
                break;
            case '?':
            default:
                abort();
        }
    }
}

int main(int argc, char* argv[]) {
    get_opts(argc, argv);

    evoluti::data_reader uint8Reader("data/data.uint8");
    evoluti::data_reader floatReader("data/data.float");
    evoluti::data_reader uint32Reader("data/data.uint32");
    evoluti::data_reader doubleReader("data/data.double");

    struct evoluti::proc_info proc;

    evoluti::proc_info_get(&proc);

    uint8Reader.read();
    floatReader.read();
    uint32Reader.read();
    doubleReader.read();

    std::vector<uint8_t> uint8V;
    uint8Reader.get_vector(uint8V);

    std::vector<float> floatV;
    floatReader.get_vector(floatV);

    std::vector<uint32_t> uint32V;
    uint32Reader.get_vector(uint32V);

    std::vector<double> doubleV;
    doubleReader.get_vector(doubleV);

    evoluti::benchmark::mark uint8Mark(GROUP_NAMES[VectorialSingleThreaded], uint8V.size(), n_iter, [&uint8V] {
        vector_dot(uint8V, 0, uint8V.size());
    });

    evoluti::benchmark::mark floatMark(GROUP_NAMES[VectorialSingleThreaded], floatV.size(), n_iter, [&floatV] {
        vector_dot(floatV, 0, floatV.size());
    });

    evoluti::benchmark::mark uint32Mark(GROUP_NAMES[VectorialSingleThreaded], uint32V.size(), n_iter, [&uint32V] {
        vector_dot(uint32V, 0, uint32V.size());
    });

    evoluti::benchmark::mark doubleMark(GROUP_NAMES[VectorialSingleThreaded], doubleV.size(), n_iter, [&doubleV] {
        vector_dot(doubleV, 0, doubleV.size());
    });

    evoluti::benchmark::mark uint8MarkMt(GROUP_NAMES[VectorialMultiThreaded], uint8V.size(), n_iter, [&uint8V, &proc] {
        std::thread* threads = new std::thread[proc.nproc];
        std::size_t split_size = uint8V.size() / proc.nproc;
        std::size_t pos = 0;

        for (std::size_t i = 0; i < (std::size_t)proc.nproc; ++i)
        {
            if (i == (std::size_t)proc.nproc - 1)
                split_size += uint8V.size() - split_size * proc.nproc;

            threads[i] = std::thread(vector_dot<uint8_t>, uint8V, pos, split_size);
            pos += split_size;
        }

        for (int i = 0; i < proc.nproc; ++i)
            threads[i].join();

        delete[] threads;
    });

    evoluti::benchmark::mark floatMarkMt(GROUP_NAMES[VectorialMultiThreaded], floatV.size(), n_iter, [&floatV, &proc] {
        std::thread* threads = new std::thread[proc.nproc];
        std::size_t split_size = floatV.size() / proc.nproc;
        std::size_t pos = 0;

        for (std::size_t i = 0; i < (std::size_t)proc.nproc; ++i)
        {
            if (i == (std::size_t)proc.nproc - 1)
                split_size += floatV.size() - split_size * proc.nproc;

            threads[i] = std::thread(vector_dot<float>, floatV, pos, split_size);
            pos += split_size;
        }

        for (int i = 0; i < proc.nproc; ++i)
            threads[i].join();

        delete[] threads;
    });

    evoluti::benchmark::mark uint32MarkMt(
        GROUP_NAMES[VectorialMultiThreaded], uint32V.size(), n_iter, [&uint32V, &proc] {
            std::thread* threads = new std::thread[proc.nproc];
            std::size_t split_size = uint32V.size() / proc.nproc;
            std::size_t pos = 0;

            for (std::size_t i = 0; i < (std::size_t)proc.nproc; ++i)
            {
                if (i == (std::size_t)proc.nproc - 1)
                    split_size += uint32V.size() - split_size * proc.nproc;

                threads[i] = std::thread(vector_dot<uint32_t>, uint32V, pos, split_size);
                pos += split_size;
            }

            for (int i = 0; i < proc.nproc; ++i)
                threads[i].join();

            delete[] threads;
        });

    evoluti::benchmark::mark doubleMarkMt(
        GROUP_NAMES[VectorialMultiThreaded], doubleV.size(), n_iter, [&doubleV, &proc] {
            std::thread* threads = new std::thread[proc.nproc];
            std::size_t split_size = doubleV.size() / proc.nproc;
            std::size_t pos = 0;

            for (std::size_t i = 0; i < (std::size_t)proc.nproc; ++i)
            {
                if (i == (std::size_t)proc.nproc - 1)
                    split_size += doubleV.size() - split_size * proc.nproc;

                threads[i] = std::thread(vector_dot<double>, doubleV, pos, split_size);
                pos += split_size;
            }

            for (int i = 0; i < proc.nproc; ++i)
                threads[i].join();

            delete[] threads;
        });

    evoluti::benchmark::runner runner({
        &uint8Mark,
        &floatMark,
        &uint32Mark,
        &doubleMark,
        &uint8MarkMt,
        &floatMarkMt,
        &uint32MarkMt,
        &doubleMarkMt,
    });

    runner.run();

    return 0;
}
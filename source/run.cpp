#include <iostream>

#include "data_reader.h"
#include "runner.h"

int main(int argc, char* argv[]) {
    evoluti::data_reader floatReader("data/data.float");
    evoluti::data_reader uint32Reader("data/data.uint32");
    evoluti::data_reader doubleReader("data/data.double");

    floatReader.read();
    uint32Reader.read();
    doubleReader.read();

    std::vector<float> floatV;
    floatReader.get_vector(floatV);

    std::vector<uint32_t> uint32V;
    uint32Reader.get_vector(uint32V);

    std::vector<double> doubleV;
    doubleReader.get_vector(doubleV);

    evoluti::benchmark::mark floatMark(floatV.size(), 1000, [&floatV] {
        for (std::size_t i = 0; i < floatV.size(); ++i)
        {
            floatV[i] = floatV[i] * floatV[i] + floatV[i];
        }
    });

    evoluti::benchmark::mark uint32Mark(uint32V.size(), 1000, [&uint32V] {
        for (std::size_t i = 0; i < uint32V.size(); ++i)
        {
            uint32V[i] = uint32V[i] * uint32V[i] + uint32V[i];
        }
    });

    evoluti::benchmark::mark doubleMark(doubleV.size(), 1000, [&doubleV] {
        for (std::size_t i = 0; i < doubleV.size(); ++i)
        {
            doubleV[i] = doubleV[i] * doubleV[i] + doubleV[i];
        }
    });

    evoluti::benchmark::runner runner({
        &floatMark,
        &uint32Mark,
        &doubleMark,
    });

    runner.runAll();

    return 0;
}
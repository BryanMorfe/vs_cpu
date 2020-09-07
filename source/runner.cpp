#include "runner.h"

#include <iomanip>
#include <iostream>
#include <string>

#include "proc_info.h"

namespace evoluti {
const char* black = "\033[0;30m";
const char* bold_black = "\033[1;30m";

const char* red = "\033[0;31m";
const char* bold_red = "\033[1;31m";

const char* green = "\033[0;32m";
const char* bold_green = "\033[1;32m";

const char* yellow = "\033[0;33m";
const char* bold_yellow = "\033[1;33m";

const char* blue = "\033[0;34m";
const char* bold_blue = "\033[1;34m";

const char* end_color = "\033[0m";
}  // namespace evoluti

evoluti::benchmark::runner::runner(const std::vector<mark*>& marks) : _marks(marks) {
}

evoluti::benchmark::runner::runner(std::vector<mark*>&& marks) : _marks(marks) {
}

void evoluti::benchmark::runner::set_marks(const std::vector<mark*>& marks) {
    _marks = marks;
}

void evoluti::benchmark::runner::set_marks(std::vector<mark*>&& marks) {
    _marks = marks;
}

void evoluti::benchmark::runner::runAll() const {
    int total_progress;
    uint64_t total_units = 0;
    int progress = 1;
    double res = 0;
    double total = 0;

    struct proc_info proc;
    proc_info_get(&proc);

    std::cout << green << "Running test for Intel Core i7-6820HQ x" << proc.nproc << end_color << std::endl;

    std::cout << green << "Tests about to begin..." << end_color << std::endl;

    std::cout << std::endl;

    for (auto& m : _marks)
    {
        total_progress = m->get_n_iters();
        std::cout << "\r"
                  << "[  0%]" << bold_green << " >                     [0.00upus 0us]" << end_color;
        fflush(stdout);
        while (res != -1)
        {
            total_units += m->get_n_units();

            res = m->run();

            if (res != -1)
            {
                total += res;
                std::cout << "\r"
                          << "[" << std::right << std::setw(3) << 100 * progress / total_progress << "%] " << bold_green
                          << std::left << std::setw(21) << std::string(20 * progress / total_progress, '=') + '>'
                          << " [" << std::fixed << std::setprecision(2) << total_units / total << "upus " << (int)total
                          << "us]" << end_color;
                fflush(stdout);
                progress++;
            }
        }

        std::cout << std::endl;

        res = 0;
        total = 0;
        progress = 1;
        total_units = 0;
    }
}
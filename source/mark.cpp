#include "mark.h"

#include <stdexcept>

evoluti::benchmark::mark::mark(int n_units, int n_iter, const std::function<void(void)>& _mark) : cl(_mark) {
    if (n_iter < 1)
        throw std::logic_error("number of iterations for the mark must be greater than 0.");

    num_iter = n_iter;

    if (n_units < 1)
        throw std::logic_error("number of units for the mark must be greater than 0.");

    num_units = n_units;
}

evoluti::benchmark::mark::mark(int n_units, int n_iter, std::function<void(void)>&& _mark) : cl(_mark) {
    if (n_iter < 1)
        throw std::logic_error("number of iterations for the mark must be greater than 0.");

    num_iter = n_iter;

    if (n_units < 1)
        throw std::logic_error("number of units for the mark must be greater than 0.");

    num_units = n_units;
}

void evoluti::benchmark::mark::set_n_units(int n_units) {
    if (n_units < 1)
        throw std::logic_error("number of units for the mark must be greater than 0.");

    num_units = n_units;
}

void evoluti::benchmark::mark::set_n_iters(int n_iter) {
    if (n_iter < 1)
        throw std::logic_error("number of iterations for the mark must be greater than 0.");

    num_iter = n_iter;
}

void evoluti::benchmark::mark::set_mark(const std::function<void(void)>& _mark) {
    cl.set(_mark);
}

void evoluti::benchmark::mark::set_mark(std::function<void(void)>&& _mark) {
    cl.set(_mark);
}

int evoluti::benchmark::mark::get_n_units() const {
    return num_units;
}

int evoluti::benchmark::mark::get_n_iters() const {
    return num_iter;
}

double evoluti::benchmark::mark::run() {
    double _time = -1;

    if (num_iter > 0)
    {
        cl.run();
        _time = cl.duration_micro();
        num_iter--;
    }

    return _time;
}
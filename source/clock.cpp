#include "clock.h"

evoluti::benchmark::clock::clock(std::function<void(void)>&& f, bool auto_run) : func(f) {
    if (auto_run)
    {
        t0 = high_resolution_clock::now();
        func();
        t1 = high_resolution_clock::now();
    }
}

evoluti::benchmark::clock::clock(const std::function<void(void)>& f, bool auto_run) : func(f) {
    if (auto_run)
    {
        t0 = high_resolution_clock::now();
        func();
        t1 = high_resolution_clock::now();
    }
}

void evoluti::benchmark::clock::set(std::function<void(void)>&& f) {
    func = f;
}

void evoluti::benchmark::clock::set(const std::function<void(void)>& f) {
    func = f;
}

void evoluti::benchmark::clock::run() {
    t0 = high_resolution_clock::now();
    func();
    t1 = high_resolution_clock::now();
}

double evoluti::benchmark::clock::duration_hours() const noexcept {
    return duration_cast<hours>(t1 - t0).count();
}

double evoluti::benchmark::clock::duration_minutes() const noexcept {
    return duration_cast<minutes>(t1 - t0).count();
}

double evoluti::benchmark::clock::duration_seconds() const noexcept {
    return duration_cast<seconds>(t1 - t0).count();
}

double evoluti::benchmark::clock::duration_milli() const noexcept {
    return duration_cast<milliseconds>(t1 - t0).count();
}

double evoluti::benchmark::clock::duration_micro() const noexcept {
    return duration_cast<microseconds>(t1 - t0).count();
}

double evoluti::benchmark::clock::duration_nano() const noexcept {
    return duration_cast<nanoseconds>(t1 - t0).count();
}
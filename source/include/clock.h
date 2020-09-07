#ifndef _EV_CLOCK_H_
#define _EV_CLOCK_H_

#include <chrono>
#include <functional>

namespace evoluti {
namespace benchmark {
using namespace std::chrono;
class clock {
public:
    clock() = default;
    clock(std::function<void(void)>&& f, bool auto_run = false);
    clock(const std::function<void(void)>& f, bool auto_run = false);

    void set(std::function<void(void)>&& f);
    void set(const std::function<void(void)>& f);

    void run();

    double duration_hours() const noexcept;
    double duration_minutes() const noexcept;
    double duration_seconds() const noexcept;
    double duration_milli() const noexcept;
    double duration_micro() const noexcept;
    double duration_nano() const noexcept;

private:
    high_resolution_clock::time_point t0;
    high_resolution_clock::time_point t1;
    std::function<void(void)> func;
};
}  // namespace benchmark
}  // namespace evoluti

#endif /* _EV_CLOCK_H_ */

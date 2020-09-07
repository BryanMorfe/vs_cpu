#ifndef _EV_MARK_H_
#define _EV_MARK_H_

#include "clock.h"

namespace evoluti {
namespace benchmark {
class mark {
public:
    mark() = default;
    mark(int n_units, int n_iter, const std::function<void(void)>& _mark);
    mark(int n_units, int n_iter, std::function<void(void)>&& _mark);

    void set_n_units(int n_units);
    void set_n_iters(int n_iter);
    void set_mark(const std::function<void(void)>& _mark);
    void set_mark(std::function<void(void)>&& _mark);

    int get_n_units() const;
    int get_n_iters() const;

    // Runs an iterations of the test
    // returns time for iteratio, or -1 when done
    double run();

private:
    clock cl;
    int num_iter;
    int num_units;
};
}  // namespace benchmark
}  // namespace evoluti

#endif /* _EV_MARK_H_ */
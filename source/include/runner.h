#ifndef _EV_RUNNER_H_
#define _EV_RUNNER_H_

#include <vector>

#include "mark.h"

namespace evoluti {
namespace benchmark {
class runner {
public:
    runner() = default;
    runner(const std::vector<mark*>& marks);
    runner(std::vector<mark*>&& marks);

    void set_marks(const std::vector<mark*>& marks);
    void set_marks(std::vector<mark*>&& marks);

    void run() const;

private:
    std::vector<mark*> _marks;
};
}  // namespace benchmark
}  // namespace evoluti

#endif /* _EV_RUNNER_H_ */
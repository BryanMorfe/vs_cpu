#include <iostream>
#include <bm_utests.h>
#include <unistd.h>
#include <cmath>

#include "clock.h"

#define WAIT_TIME_S  (1)
#define WAIT_TIME_US (WAIT_TIME_S * 1000000)

bool test_clock()
{
    TEST_BEGIN();
    evoluti::benchmark::clock c1;

    c1.set([] {
        // Adjust by some time for drift and wakeup time
        usleep(WAIT_TIME_US - 200);
    });

    c1.run();

    ASSERT_EQUAL_FLOAT(c1.duration_micro() - WAIT_TIME_US, 1.0, 2);

    return TEST_END();
}

int main()
{
    RUN_TEST(ClockTest, test_clock());
    return 0;
}

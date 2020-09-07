#include <bm_utests.h>

#include <iostream>

#include "mark.h"

bool test_mark() {
    TEST_BEGIN();
    static const int N_ITER = 10000000;
    float A_ARR[] = {5.9, 3.8, 9.6, 10.4, 4.86, 11.3, 7.5, 2.33, 0.19, 11.3};
    const float W_ARR[] = {9.5, 8.3, 6.9, 4.1, 86.4, 3.11, 5.7, 33.2, 19.0, 3.11};
    const float B_ARR[] = {14.9, 11.8, 15.6, 14.4, 10.86, 14.3, 12.5, 5.33, 9.19, 14.3};
    const int ARR_SIZE = sizeof(A_ARR) / sizeof(A_ARR[0]);

    int iters_ran = 0;
    double res = 0;
    double total = 0;

    evoluti::benchmark::mark m(N_ITER, [&A_ARR, &W_ARR, &B_ARR] {
        for (int i = 0; i < ARR_SIZE; ++i)
        {
            A_ARR[i] = A_ARR[i] * W_ARR[i] + B_ARR[i];
        }
    });

    while (res != -1)
    {
        res = m.run();

        if (res != -1)
        {
            iters_ran++;
            total += res;
        }
    }

    ASSERT_EQUAL_INT(N_ITER, iters_ran);

    std::cout << "Total ms: " << total << std::endl;

    return TEST_END();
}

int main() {
    RUN_TEST(TestMark, test_mark());
    return 0;
}

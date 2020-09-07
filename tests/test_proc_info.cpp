#include <iostream>
#include <bm_utests.h>

#include "proc_info.h"

bool test_proc_info()
{
    TEST_BEGIN();
    struct evoluti::proc_info proc;

    evoluti::proc_info_get(&proc);

    ASSERT_GREATER_THAN_INT(proc.nproc, 0);
    ASSERT_GREATER_THAN_INT(proc.nproc_avail, 0);

    std::cout << "N Proc: " << proc.nproc << std::endl;
    std::cout << "N Proc Avail: " << proc.nproc_avail << std::endl;

    return TEST_END();
}

int main()
{
    RUN_TEST(ProcInfoTest, test_proc_info());
    return 0;
}

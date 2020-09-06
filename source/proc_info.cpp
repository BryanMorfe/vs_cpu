#include "proc_info.h"
#include <assert.h>
#include <sys/sysinfo.h>

void proc_info_get(struct proc_info* pi)
{
    assert(pi != nullptr);

    pi->nproc = get_nprocs_conf();
    pi->nproc_avail = get_nprocs();
}
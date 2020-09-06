#ifndef _PROC_INFO_H_
#define _PROC_INFO_H_

struct proc_info
{
    const char* proc_desc;
    int nproc;
    int nproc_avail;
};

void proc_info_get(struct proc_info* pi);

#endif /* _PROC_INFO_H_ */
#ifndef TUNGUSSKA_SYS_H
#define TUNGUSSKA_SYS_H

#include "sys/types.h"
#include "sys/sysinfo.h"
#include <sys/resource.h>

#include "../Log.h"

class System
{
public:
    struct sysinfo memInfo;

    System();
    ~System();

    int getRam() {
        struct rusage r_usage;
        getrusage(RUSAGE_SELF,&r_usage);
        return r_usage.ru_maxrss;
    };
};

#endif
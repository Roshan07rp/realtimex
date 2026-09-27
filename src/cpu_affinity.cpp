#include "cpu_affinity.h"
#include <sched.h>

bool set_cpu_affinity(int cpu) {
    if (cpu < 0 || cpu >= CPU_SETSIZE) return false;
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(cpu, &set);
    return sched_setaffinity(0, sizeof(set), &set) == 0;
}

int current_cpu() {
    return sched_getcpu();
}

#include "scheduler.h"
#include <sched.h>

namespace {
int policy_from_name(const std::string& name) {
    if (name == "SCHED_FIFO") return SCHED_FIFO;
    if (name == "SCHED_RR") return SCHED_RR;
    return SCHED_OTHER;
}
}

bool apply_scheduler(const SchedulerConfig& config) {
    int policy = policy_from_name(config.policy);
    sched_param params{};
    params.sched_priority = policy == SCHED_OTHER ? 0 : config.priority;
    return sched_setscheduler(0, policy, &params) == 0;
}

std::string scheduler_policy_name() {
    int policy = sched_getscheduler(0);
    if (policy == SCHED_FIFO) return "SCHED_FIFO";
    if (policy == SCHED_RR) return "SCHED_RR";
    if (policy == SCHED_OTHER) return "SCHED_OTHER";
    return "UNKNOWN";
}

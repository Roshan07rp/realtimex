#pragma once
#include <string>

struct SchedulerConfig {
    std::string policy{"SCHED_OTHER"};
    int priority{0};
};

bool apply_scheduler(const SchedulerConfig& config);
std::string scheduler_policy_name();

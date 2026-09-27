#pragma once
#include <string>

struct SystemInfo {
    std::string kernel_release;
    bool preempt_rt{false};
    int cpu_count{0};
};

SystemInfo get_system_info();

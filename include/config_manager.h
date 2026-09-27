#pragma once
#include "rt_task.h"
#include <string>

struct AppConfig {
    RtTaskConfig task;
    int cpu{-1};
    std::string csv_output{"realtimex_results.csv"};
};

bool load_config(const std::string& path, AppConfig& config);

#pragma once
#include "latency_analyzer.h"
#include "scheduler.h"

struct RtTaskConfig {
    long period_us{1000};
    int iterations{10000};
    long deadline_us{1000};
    SchedulerConfig scheduler;
};

bool run_periodic_task(const RtTaskConfig& config, LatencyAnalyzer& analyzer);

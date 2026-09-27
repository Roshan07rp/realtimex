#include "rt_task.h"
#include <ctime>

namespace {
std::int64_t ns(const timespec& ts) {
    return static_cast<std::int64_t>(ts.tv_sec) * 1000000000LL + ts.tv_nsec;
}
void add_us(timespec& ts, long us) {
    ts.tv_nsec += us * 1000L;
    while (ts.tv_nsec >= 1000000000L) {
        ts.tv_nsec -= 1000000000L;
        ++ts.tv_sec;
    }
}
}

bool run_periodic_task(const RtTaskConfig& config, LatencyAnalyzer& analyzer) {
    if (!apply_scheduler(config.scheduler)) return false;

    timespec next{};
    if (clock_gettime(CLOCK_MONOTONIC, &next) != 0) return false;
    add_us(next, config.period_us);

    for (int i = 0; i < config.iterations; ++i) {
        if (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next, nullptr) != 0)
            return false;

        timespec now{};
        if (clock_gettime(CLOCK_MONOTONIC, &now) != 0) return false;

        analyzer.add_sample(ns(now) - ns(next));
        add_us(next, config.period_us);
    }
    return true;
}

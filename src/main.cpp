#include "config_manager.h"
#include "cpu_affinity.h"
#include "latency_analyzer.h"
#include "logger.h"
#include "rt_task.h"
#include "scheduler.h"
#include "system_info.h"
#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string config_path = "config/realtime_config.json";
    if (argc >= 3 && std::string(argv[1]) == "--config") config_path = argv[2];

    AppConfig config;
    if (!load_config(config_path, config)) {
        Logger::error("Failed to load configuration: " + config_path);
        return 1;
    }

    const SystemInfo info = get_system_info();

    std::cout << "\n========================================\n"
              << " RealtimeX - Latency Analyzer\n"
              << "========================================\n"
              << "Kernel          : " << info.kernel_release << '\n'
              << "PREEMPT_RT      : " << (info.preempt_rt ? "ENABLED" : "NOT DETECTED") << '\n'
              << "CPU Cores       : " << info.cpu_count << '\n';

    if (config.cpu >= 0 && !set_cpu_affinity(config.cpu))
        Logger::warning("Could not set requested CPU affinity.");

    LatencyAnalyzer analyzer(static_cast<std::int64_t>(config.task.deadline_us) * 1000LL);

    std::cout << "Requested Policy : " << config.task.scheduler.policy << '\n'
              << "Priority         : " << config.task.scheduler.priority << '\n'
              << "CPU              : " << current_cpu() << '\n'
              << "Period           : " << config.task.period_us << " us\n"
              << "Iterations       : " << config.task.iterations << '\n'
              << "Deadline         : " << config.task.deadline_us << " us\n";

    if (!run_periodic_task(config.task, analyzer)) {
        Logger::error("Periodic task failed. SCHED_FIFO/SCHED_RR may require privileges.");
        return 2;
    }

    const auto stats = analyzer.statistics();

    std::cout << "\n----------- Results -----------\n"
              << std::fixed << std::setprecision(2)
              << "Active Policy    : " << scheduler_policy_name() << '\n'
              << "Minimum Latency  : " << stats.min_ns / 1000.0 << " us\n"
              << "Average Latency  : " << stats.average_ns / 1000.0 << " us\n"
              << "Maximum Latency  : " << stats.max_ns / 1000.0 << " us\n"
              << "P95 Latency      : " << stats.p95_ns / 1000.0 << " us\n"
              << "P99 Latency      : " << stats.p99_ns / 1000.0 << " us\n"
              << "Deadline Misses  : " << stats.deadline_misses << '\n';

    if (analyzer.write_csv(config.csv_output))
        std::cout << "CSV Output       : " << config.csv_output << '\n';
    else
        Logger::warning("Could not write CSV output.");

    std::cout << "================================\n";
    return 0;
}

#pragma once
#include <cstdint>
#include <string>
#include <vector>

struct LatencyStats {
    std::int64_t min_ns{0};
    std::int64_t max_ns{0};
    double average_ns{0.0};
    double p95_ns{0.0};
    double p99_ns{0.0};
    std::uint64_t deadline_misses{0};
    std::size_t samples{0};
};

class LatencyAnalyzer {
public:
    explicit LatencyAnalyzer(std::int64_t deadline_ns);
    void add_sample(std::int64_t latency_ns);
    LatencyStats statistics() const;
    bool write_csv(const std::string& path) const;
private:
    std::int64_t deadline_ns_;
    std::vector<std::int64_t> samples_;
};

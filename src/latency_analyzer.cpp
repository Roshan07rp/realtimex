#include "latency_analyzer.h"
#include <algorithm>
#include <fstream>
#include <numeric>

LatencyAnalyzer::LatencyAnalyzer(std::int64_t deadline_ns) : deadline_ns_(deadline_ns) {}

void LatencyAnalyzer::add_sample(std::int64_t latency_ns) {
    samples_.push_back(latency_ns);
}

LatencyStats LatencyAnalyzer::statistics() const {
    LatencyStats result;
    result.samples = samples_.size();
    if (samples_.empty()) return result;

    std::vector<std::int64_t> sorted = samples_;
    std::sort(sorted.begin(), sorted.end());
    result.min_ns = sorted.front();
    result.max_ns = sorted.back();

    const auto sum = std::accumulate(sorted.begin(), sorted.end(), 0.0L);
    result.average_ns = static_cast<double>(sum / sorted.size());

    auto percentile = [&sorted](double p) {
        double index = p * static_cast<double>(sorted.size() - 1);
        auto lower = static_cast<std::size_t>(index);
        auto upper = std::min(lower + 1, sorted.size() - 1);
        double fraction = index - static_cast<double>(lower);
        return sorted[lower] + (sorted[upper] - sorted[lower]) * fraction;
    };

    result.p95_ns = percentile(0.95);
    result.p99_ns = percentile(0.99);

    for (auto sample : samples_)
        if (sample > deadline_ns_) ++result.deadline_misses;

    return result;
}

bool LatencyAnalyzer::write_csv(const std::string& path) const {
    std::ofstream file(path);
    if (!file) return false;
    file << "sample,latency_ns\n";
    for (std::size_t i = 0; i < samples_.size(); ++i)
        file << i << "," << samples_[i] << "\n";
    return true;
}

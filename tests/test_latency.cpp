#include "latency_analyzer.h"
#include <cassert>
#include <iostream>
int main() {
    LatencyAnalyzer analyzer(100);
    analyzer.add_sample(10);
    analyzer.add_sample(20);
    analyzer.add_sample(150);
    auto s = analyzer.statistics();
    assert(s.samples == 3);
    assert(s.min_ns == 10);
    assert(s.max_ns == 150);
    assert(s.deadline_misses == 1);
    std::cout << "Latency analyzer test passed.\n";
}

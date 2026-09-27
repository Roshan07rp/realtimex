#include "scheduler.h"
#include <cassert>
#include <iostream>
int main() {
    SchedulerConfig c;
    c.policy = "SCHED_OTHER";
    c.priority = 0;
    assert(apply_scheduler(c));
    assert(scheduler_policy_name() == "SCHED_OTHER");
    std::cout << "Scheduler test passed.\n";
}

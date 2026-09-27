#include "config_manager.h"
#include <cassert>
#include <iostream>
int main() {
    AppConfig c;
    assert(load_config("../config/realtime_config.json", c));
    assert(c.task.period_us > 0);
    assert(c.task.iterations > 0);
    assert(!c.task.scheduler.policy.empty());
    std::cout << "Config test passed.\n";
}

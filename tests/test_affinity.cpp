#include "cpu_affinity.h"
#include <cassert>
#include <iostream>
int main() {
    int cpu = current_cpu();
    assert(cpu >= 0);
    std::cout << "Affinity test passed on CPU " << cpu << ".\n";
}

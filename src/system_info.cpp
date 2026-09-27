#include "system_info.h"
#include <fstream>
#include <thread>
#include <sys/utsname.h>

SystemInfo get_system_info() {
    SystemInfo info;
    struct utsname uts{};
    if (uname(&uts) == 0) info.kernel_release = uts.release;
    info.cpu_count = static_cast<int>(std::thread::hardware_concurrency());

    std::ifstream realtime("/sys/kernel/realtime");
    int value = 0;
    if (realtime >> value)
        info.preempt_rt = value == 1;
    else
        info.preempt_rt = info.kernel_release.find("-rt") != std::string::npos;

    return info;
}

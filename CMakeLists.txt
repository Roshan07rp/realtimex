cmake_minimum_required(VERSION 3.16)
project(realtimex VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(realtimex_lib
    src/latency_analyzer.cpp
    src/rt_task.cpp
    src/scheduler.cpp
    src/cpu_affinity.cpp
    src/system_info.cpp
    src/logger.cpp
    src/config_manager.cpp
)
target_include_directories(realtimex_lib PUBLIC include)
target_compile_options(realtimex_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(realtimex src/main.cpp)
target_link_libraries(realtimex PRIVATE realtimex_lib pthread rt)

enable_testing()

add_executable(test_latency tests/test_latency.cpp)
target_link_libraries(test_latency PRIVATE realtimex_lib pthread rt)
add_test(NAME Latency_Analyzer COMMAND test_latency)

add_executable(test_scheduler tests/test_scheduler.cpp)
target_link_libraries(test_scheduler PRIVATE realtimex_lib pthread rt)
add_test(NAME Scheduler COMMAND test_scheduler)

add_executable(test_config tests/test_config.cpp)
target_link_libraries(test_config PRIVATE realtimex_lib pthread rt)
add_test(NAME Config_Manager COMMAND test_config)

add_executable(test_affinity tests/test_affinity.cpp)
target_link_libraries(test_affinity PRIVATE realtimex_lib pthread rt)
add_test(NAME CPU_Affinity COMMAND test_affinity)

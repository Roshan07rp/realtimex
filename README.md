# RealtimeX — PREEMPT_RT Latency Analyzer & Deterministic Task Scheduling Framework

RealtimeX is a Linux/C++17 framework for measuring periodic wake-up latency and experimenting with Linux real-time scheduling.

> Results depend on hardware, workload, kernel configuration, privileges, and whether PREEMPT_RT is actually enabled. RealtimeX reports detected state; it does not claim RT behavior when unavailable.

## Features

- PREEMPT_RT detection
- Periodic wake-up latency measurement
- Minimum, average, maximum, P95 and P99 latency
- Deadline-miss counting
- SCHED_OTHER, SCHED_FIFO and SCHED_RR support
- Optional CPU affinity
- Configurable period, iterations, priority and deadline
- CSV benchmark output
- systemd service template
- Unit tests
- CPU stress comparison script

## Structure

```text
realtimex/
├── README.md
├── CMakeLists.txt
├── .gitignore
├── config/
│   └── realtime_config.json
├── include/
│   ├── latency_analyzer.h
│   ├── rt_task.h
│   ├── scheduler.h
│   ├── cpu_affinity.h
│   ├── system_info.h
│   ├── logger.h
│   └── config_manager.h
├── src/
│   ├── main.cpp
│   ├── latency_analyzer.cpp
│   ├── rt_task.cpp
│   ├── scheduler.cpp
│   ├── cpu_affinity.cpp
│   ├── system_info.cpp
│   ├── logger.cpp
│   └── config_manager.cpp
├── scripts/
│   ├── check_rt_kernel.sh
│   ├── setup_realtime.sh
│   ├── run_benchmark.sh
│   └── stress_test.sh
├── tests/
│   ├── test_latency.cpp
│   ├── test_scheduler.cpp
│   ├── test_config.cpp
│   └── test_affinity.cpp
├── systemd/
│   └── realtime-monitor.service
└── docs/
    ├── architecture.md
    ├── realtime-concepts.md
    └── benchmark-report.md
```

## Build

```bash
sudo apt update
sudo apt install build-essential cmake git
cmake -S . -B build
cmake --build build -j$(nproc)
```

## Check RT kernel

```bash
./scripts/check_rt_kernel.sh
```

## Run

Default configuration uses SCHED_OTHER so it can run without real-time privileges:

```bash
./build/realtimex --config config/realtime_config.json
```

For SCHED_FIFO/SCHED_RR, use appropriate Linux privileges:

```bash
sudo ./build/realtimex --config config/realtime_config.json
```

## Tests

```bash
ctest --test-dir build --output-on-failure
```

## Stress test

```bash
sudo ./scripts/setup_realtime.sh
sudo ./scripts/stress_test.sh
```

The exact latency values are machine-dependent.

## Configuration

`config/realtime_config.json` controls period, iterations, deadline, scheduler policy, priority, CPU affinity and CSV output.

## systemd

The included unit is a template for a one-shot benchmark:

```bash
sudo cp systemd/realtime-monitor.service /etc/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable realtime-monitor
```

Run it with:

```bash
sudo systemctl start realtime-monitor
```

## Safety and interpretation

Do not claim hard real-time guarantees from a small benchmark. Record kernel, hardware, load, CPU affinity, scheduling policy and test conditions when comparing runs.

## License

MIT

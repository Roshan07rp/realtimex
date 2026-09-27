# RealtimeX Architecture

```text
System Info + Kernel Check
          |
          v
     Configuration
          |
          v
 Scheduler + CPU Affinity
          |
          v
    Periodic RT Task
          |
          v
 CLOCK_MONOTONIC / nanosleep
          |
          v
   Latency Analyzer
          |
    +-----+-----+
    |     |     |
   Min  P95/P99 Max
          |
          v
      CSV Report
```

The periodic task uses absolute `clock_nanosleep()` deadlines to reduce timing drift. Each sample is the difference between actual and scheduled wake-up time.

Scheduling policies supported: SCHED_OTHER, SCHED_FIFO and SCHED_RR. Real-time policies require suitable Linux privileges.

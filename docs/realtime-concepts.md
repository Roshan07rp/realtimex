# Real-Time Linux Concepts

## PREEMPT_RT

PREEMPT_RT is intended to reduce and make kernel preemption latency more predictable for suitable workloads. RealtimeX checks the running system rather than assuming RT behavior.

## Scheduling

SCHED_FIFO is a fixed-priority real-time policy. SCHED_RR provides round-robin behavior among equal-priority real-time tasks. SCHED_OTHER is the normal Linux scheduling policy.

## Latency

For each periodic wake-up:

```text
latency = actual_wakeup_time - scheduled_wakeup_time
```

Tail latency and maximum latency are important when studying timing behavior.

## Determinism

A low average latency does not prove hard real-time guarantees. Repeat tests under controlled conditions and document kernel, hardware, load, CPU affinity and scheduler configuration.

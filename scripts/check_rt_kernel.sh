#!/bin/bash
set -u
echo "=== RealtimeX PREEMPT_RT Kernel Check ==="
echo "Kernel: $(uname -r)"
if [[ -f /sys/kernel/realtime ]]; then
    value=$(cat /sys/kernel/realtime)
    [[ "$value" == "1" ]] && echo "PREEMPT_RT: ENABLED" || echo "PREEMPT_RT: NOT DETECTED"
else
    if uname -r | grep -q -- "-rt"; then
        echo "PREEMPT_RT: likely enabled (kernel release contains -rt)"
    else
        echo "PREEMPT_RT: NOT DETECTED"
    fi
fi
echo "Real-time priority limit: $(ulimit -r)"

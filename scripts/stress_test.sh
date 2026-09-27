#!/bin/bash
set -e
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cmake -S "$ROOT" -B "$ROOT/build"
cmake --build "$ROOT/build" -j"$(nproc)"
echo "=== Baseline ==="
"$ROOT/build/realtimex" --config "$ROOT/config/realtime_config.json"
if command -v stress-ng >/dev/null 2>&1; then
    echo "=== Under CPU load ==="
    stress-ng --cpu "$(nproc)" --timeout 20s &
    PID=$!
    sleep 2
    "$ROOT/build/realtimex" --config "$ROOT/config/realtime_config.json" || true
    wait "$PID" || true
else
    echo "Install stress-ng with: sudo apt install stress-ng"
fi

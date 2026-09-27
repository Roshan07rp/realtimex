#!/bin/bash
set -e
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cmake -S "$ROOT" -B "$ROOT/build"
cmake --build "$ROOT/build" -j"$(nproc)"
"$ROOT/scripts/check_rt_kernel.sh"
"$ROOT/build/realtimex" --config "$ROOT/config/realtime_config.json"

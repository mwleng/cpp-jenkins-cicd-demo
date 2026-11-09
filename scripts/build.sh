#!/usr/bin/env bash
set -euo pipefail

build_dir="${1:-build}"
./scripts/configure.sh "$build_dir" "${2:-gcc}"
cmake --build "$build_dir" --parallel


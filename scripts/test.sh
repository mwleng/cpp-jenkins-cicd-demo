#!/usr/bin/env bash
set -euo pipefail

build_dir="${1:-build}"
./scripts/build.sh "$build_dir" "${2:-gcc}"
ctest --test-dir "$build_dir" --output-on-failure


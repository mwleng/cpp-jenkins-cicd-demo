#!/usr/bin/env bash
set -euo pipefail

build_dir="${1:-build}"
compiler="${2:-gcc}"

case "$compiler" in
  gcc) cxx="${CXX:-g++}" ;;
  clang) cxx="${CXX:-clang++}" ;;
  *) echo "Unsupported compiler: $compiler" >&2; exit 2 ;;
esac

cmake -S . -B "$build_dir" -G "${CMAKE_GENERATOR:-Ninja}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_COMPILER="$cxx" \
  -DFILECHECK_BUILD_TESTS=ON


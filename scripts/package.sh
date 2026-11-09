#!/usr/bin/env bash
set -euo pipefail

build_dir="${1:-build-package}"
./scripts/build.sh "$build_dir" gcc
cmake --install "$build_dir" --prefix "${PWD}/dist/stage"
cmake --build "$build_dir" --target package
mkdir -p dist
find "$build_dir" -maxdepth 1 -type f \( -name '*.tar.gz' -o -name '*.zip' \) -exec cp {} dist/ \;


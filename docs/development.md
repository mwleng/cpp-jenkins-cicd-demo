# Development

## Ubuntu WSL2 prerequisites

```bash
sudo apt update
sudo apt install -y build-essential clang cmake ninja-build
```

## Local build and tests

```bash
./scripts/test.sh build-gcc gcc
./scripts/test.sh build-clang clang
```

To create CPack archives:

```bash
./scripts/package.sh
```

The generated packages are placed in `dist/`.

## Jenkins agent expectations

The example `Jenkinsfile` expects an Ubuntu agent labelled `ubuntu` with `gcc`,
`clang`, CMake, Ninja, and CTest available on `PATH`. It runs the same build and
test flow for both compilers and archives the CPack output.


# cpp-jenkins-cicd-demo

A small C++17 `filecheck` command-line application used to demonstrate a Jenkins
CI/CD pipeline on an Ubuntu agent.

The project demonstrates:

- CMake configuration and installation
- GCC and Clang builds
- CTest unit-test execution
- CPack TGZ and ZIP release artifacts
- A Jenkins matrix pipeline defined in `Jenkinsfile`

## Quick start on Ubuntu WSL2

Install the prerequisites described in [docs/development.md](docs/development.md),
then run:

```bash
./scripts/test.sh build-gcc gcc
./build-gcc/filecheck README.md
```

The command exits with status `0` only when every supplied path is a regular file.
It prints `file`, `missing`, or `not-regular-file` for each path.

## Repository layout

```text
include/       Public library header
src/           CLI and library implementation
tests/         CTest unit test
scripts/       WSL/Linux build, test, and packaging helpers
docs/          Development and Jenkins-agent notes
Jenkinsfile    GCC/Clang matrix pipeline
```

## GitHub setup

This starter directory is intentionally local. After reviewing it, create the
public GitHub repository and push it with:

```bash
gh repo create cpp-jenkins-cicd-demo --public --source . --remote origin
git add .
git commit -m "Initial C++ Jenkins CI/CD demo"
git push -u origin main
```

If the default branch is not yet configured locally, run `git branch -M main`
before the push. The `gh repo create` command requires an authenticated GitHub
CLI session.


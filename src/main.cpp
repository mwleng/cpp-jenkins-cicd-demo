#include "filecheck/checker.hpp"

#include <iostream>

namespace {

void print_usage(const char* program) {
    std::cerr << "Usage: " << program << " <path> [path ...]\n";
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 2;
    }

    int failures = 0;
    for (int index = 1; index < argc; ++index) {
        const auto result = filecheck::check_path(argv[index]);
        std::cout << argv[index] << ": " << filecheck::to_string(result) << '\n';
        if (result != filecheck::CheckResult::file) {
            ++failures;
        }
    }
    return failures == 0 ? 0 : 1;
}


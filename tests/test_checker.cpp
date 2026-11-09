#include "filecheck/checker.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>

int main() {
    const auto unique_suffix =
        std::chrono::steady_clock::now().time_since_epoch().count();

    const auto test_root =
        std::filesystem::temp_directory_path() /
        ("cpp-filecheck-test-" + std::to_string(unique_suffix));

    std::error_code error;
    std::filesystem::remove_all(test_root, error);
    assert(!error);

    std::filesystem::create_directories(test_root / "directory");
    std::ofstream(test_root / "sample.txt") << "sample\n";

    assert(filecheck::check_path(test_root / "sample.txt") == filecheck::CheckResult::file);
    assert(filecheck::check_path(test_root / "missing.txt") == filecheck::CheckResult::missing);
    assert(filecheck::check_path(test_root / "directory") == filecheck::CheckResult::not_regular_file);
    assert(filecheck::to_string(filecheck::CheckResult::file) == "file");
    assert(filecheck::to_string(filecheck::CheckResult::missing) == "missing");

    std::filesystem::remove_all(test_root, error);
    assert(!error);
    return 0;
}


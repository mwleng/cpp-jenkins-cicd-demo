#include "filecheck/checker.hpp"

#include <cassert>
#include <filesystem>
#include <fstream>

int main() {
    const auto test_root = std::filesystem::temp_directory_path() / "cpp-filecheck-test";
    std::filesystem::remove_all(test_root);
    std::filesystem::create_directories(test_root / "directory");
    std::ofstream(test_root / "sample.txt") << "sample\n";

    assert(filecheck::check_path(test_root / "sample.txt") == filecheck::CheckResult::file);
    assert(filecheck::check_path(test_root / "missing.txt") == filecheck::CheckResult::missing);
    assert(filecheck::check_path(test_root / "directory") == filecheck::CheckResult::not_regular_file);
    assert(filecheck::to_string(filecheck::CheckResult::file) == "file");
    assert(filecheck::to_string(filecheck::CheckResult::missing) == "missing");

    std::filesystem::remove_all(test_root);
    return 0;
}


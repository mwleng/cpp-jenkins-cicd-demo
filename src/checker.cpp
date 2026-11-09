#include "filecheck/checker.hpp"

namespace filecheck {

CheckResult check_path(const std::filesystem::path& path) {
    std::error_code error;
    const bool exists = std::filesystem::exists(path, error);
    if (error || !exists) {
        return CheckResult::missing;
    }

    return std::filesystem::is_regular_file(path, error) && !error
               ? CheckResult::file
               : CheckResult::not_regular_file;
}

std::string to_string(const CheckResult result) {
    switch (result) {
    case CheckResult::file:
        return "file";
    case CheckResult::missing:
        return "missing";
    case CheckResult::not_regular_file:
        return "not-regular-file";
    }
    return "unknown";
}

}  // namespace filecheck


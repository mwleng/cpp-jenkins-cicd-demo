#pragma once

#include <filesystem>
#include <string>

namespace filecheck {

enum class CheckResult { file, missing, not_regular_file };

CheckResult check_path(const std::filesystem::path& path);
std::string to_string(CheckResult result);

}  // namespace filecheck


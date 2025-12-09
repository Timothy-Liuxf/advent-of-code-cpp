#ifndef ADVENT_OF_CODE_CPP_UTILS_IO_HPP
#define ADVENT_OF_CODE_CPP_UTILS_IO_HPP

#include <filesystem>
#include <string>

#include "common.hpp"

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_BEGIN

[[nodiscard]] std::string GetContentsFromUrl(const std::string& url);
[[nodiscard]] std::string GetContentsFromFile(const std::filesystem::path& path);

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_END

#endif  // ADVENT_OF_CODE_CPP_UTILS_IO_HPP

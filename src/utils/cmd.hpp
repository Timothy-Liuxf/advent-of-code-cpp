#ifndef ADVENT_OF_CODE_CPP_UTILS_CMD_HPP
#define ADVENT_OF_CODE_CPP_UTILS_CMD_HPP

#include <config.h>

#include <cstdint>
#include <string>
#include <string_view>

#include "common.hpp"

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_BEGIN

using SolveFunctionType = std::string (*)(std::uint64_t, std::string_view);

[[nodiscard]] int SolveProblemFromArgs(int argc, char* argv[], const std::string& title,
                                       SolveFunctionType solver) noexcept;

#define ADVENT_OF_CODE_CPP_MAIN_FUNCTION(year, day, solve_func)                                                        \
    int main(int argc, char* argv[]) {                                                                                 \
        return ADVENT_OF_CODE_CPP_UTILS_NAMESPACE::SolveProblemFromArgs(                                               \
            argc, argv, PACKAGE_NAME ": year" #year " day" #day, solve_func);                                          \
    }

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_END

#endif  // ADVENT_OF_CODE_CPP_UTILS_CMD_HPP

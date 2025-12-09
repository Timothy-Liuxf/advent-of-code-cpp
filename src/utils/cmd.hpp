#ifndef ADVENT_OF_CODE_CPP_UTILS_CMD_HPP
#define ADVENT_OF_CODE_CPP_UTILS_CMD_HPP

#include <cstdio>     // Required in the Macro ADVENT_OF_CODE_CPP_MAIN_FUNCTION
#include <exception>  // Required in the Macro ADVENT_OF_CODE_CPP_MAIN_FUNCTION
#include <functional>
#include <string_view>

#include <tclap/CmdLine.h>

#include "common.hpp"

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_BEGIN

void SolveProblemFromArgs(int argc, char* argv[], std::function<std::string(std::uint64_t, std::string_view)> solver);

#define ADVENT_OF_CODE_CPP_MAIN_FUNCTION(solve_func)                                                                   \
    int main(int argc, char* argv[]) {                                                                                 \
        try {                                                                                                          \
            ADVENT_OF_CODE_CPP_UTILS_NAMESPACE::SolveProblemFromArgs(argc, argv, solve_func);                          \
        } catch (std::exception & e) {                                                                                 \
            std::fprintf(stderr, "Error: %s\n", e.what());                                                             \
            return 1;                                                                                                  \
        } catch (...) {                                                                                                \
            std::fprintf(stderr, "Unknown error occurred.\n");                                                         \
            return 1;                                                                                                  \
        }                                                                                                              \
        return 0;                                                                                                      \
    }

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_END

#endif  // ADVENT_OF_CODE_CPP_UTILS_CMD_HPP

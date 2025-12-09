#ifndef ADVENT_OF_CODE_CPP_UTILS_CMD_HPP
#define ADVENT_OF_CODE_CPP_UTILS_CMD_HPP

#include <config.h>  // Required by the Macro function ADVENT_OF_CODE_CPP_MAIN_FUNCTION

#include <cstdio>     // Required by the Macro function ADVENT_OF_CODE_CPP_MAIN_FUNCTION
#include <exception>  // Required by the Macro funtion ADVENT_OF_CODE_CPP_MAIN_FUNCTION
#include <functional>
#include <string_view>

#include <tclap/CmdLine.h>

#include "common.hpp"

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_BEGIN

void SolveProblemFromArgs(int argc, char* argv[], const std::string& title,
                          std::function<std::string(std::uint64_t, std::string_view)> solver);

#define ADVENT_OF_CODE_CPP_MAIN_FUNCTION(year, day, solve_func)                                                        \
    int main(int argc, char* argv[]) {                                                                                 \
        try {                                                                                                          \
            ADVENT_OF_CODE_CPP_UTILS_NAMESPACE::SolveProblemFromArgs(                                                  \
                argc, argv, PACKAGE_NAME ": year" #year " day" #day, solve_func);                                      \
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

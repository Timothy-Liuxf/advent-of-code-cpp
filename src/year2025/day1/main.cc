#include <config.h>

#include <algorithm>
#include <charconv>
#include <cstdio>
#include <format>
#include <iostream>
#include <print>
#include <ranges>
#include <stdexcept>
#include <string_view>

#include <tclap/CmdLine.h>

#include <common/common.hpp>
#include <utils/cmd.hpp>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;
using namespace ADVENT_OF_CODE_CPP_NAMESPACE;

static void Solve(std::string_view input) {
    int current_pos = 50;
    int count       = 0;
    std::ranges::for_each(std::views::split(input, "\n"sv), [&current_pos, &count](auto &&operation) {
        // get the string_view of each line
        auto line_sv = std::string_view(&*operation.begin(), std::ranges::distance(operation));
        if (line_sv.empty()) [[unlikely]] {
            return;
        }

        int  step = 0;
        auto res  = std::from_chars(line_sv.data() + 1, line_sv.data() + line_sv.size(), step, 10);
        if (res.ec != std::errc {}) [[unlikely]] {
            throw std::runtime_error(std::format("Invalid number in operation: {}", line_sv));
        }

        if (line_sv[0] == 'R') {
            current_pos = (current_pos + step) % 100;
        } else {
            current_pos = (current_pos - step + 100) % 100;
        }
        if (current_pos == 0) {
            ++count;
        }
    });
    std::println(std::cout, "{}", count);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(Solve)

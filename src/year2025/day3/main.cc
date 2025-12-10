#include <config.h>

#include <algorithm>
#include <ranges>
#include <string>
#include <string_view>

#include <common/common.hpp>
#include <utils/cmd.hpp>
#include <utils/strconv.hpp>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;
using namespace ADVENT_OF_CODE_CPP_NAMESPACE;

static std::string Solve(std::uint64_t part, std::string_view input) {
    std::uint64_t joltage = 0;
    std::ranges::for_each(std::views::split(input, "\n"sv), [&joltage, part](auto &&line) {
        auto line_sv = std::string_view(line);
        if (line_sv.empty()) [[unlikely]] {
            return;
        }

        if (part == 1) {
            // Part 1
            auto first  = std::max_element(line_sv.begin(), line_sv.end() - 1);
            auto second = std::max_element(first + 1, line_sv.end());
            joltage += (*first - '0') * 10 + (*second - '0');
        } else {
            // Part 2
            auto          current_pos     = line_sv.cend();
            std::uint64_t current_joltage = 0;
            for (int i = 0; i < 12; ++i) {
                std::string_view::const_iterator start_pos;
                if (current_pos == line_sv.cend()) [[unlikely]] {
                    start_pos = line_sv.cbegin();
                } else {
                    start_pos = current_pos + 1;
                }
                current_pos     = std::max_element(start_pos, line_sv.end() - 11 + i);
                current_joltage = current_joltage * 10 + (*current_pos - '0');
            }
            joltage += current_joltage;
        }
    });
    return std::to_string(joltage);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 3, Solve)

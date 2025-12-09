#include <config.h>

#include <algorithm>
#include <ranges>
#include <stdexcept>
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
        auto line_sv = std::string_view(&*line.begin(), std::ranges::distance(line));
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
            throw std::runtime_error("Part 2 has not been implemented.");
        }
    });
    return std::to_string(joltage);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(Solve)

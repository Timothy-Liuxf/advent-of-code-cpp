#include <config.h>

#include <algorithm>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <common/common.hpp>
#include <utils/cmd.hpp>
#include <utils/strconv.hpp>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;
using namespace ADVENT_OF_CODE_CPP_NAMESPACE;

[[nodiscard]] static std::string SolvePart1(const std::string& input) {
    std::istringstream sin(input);
    std::string        line;
    std::int64_t       result = 0;

    std::vector<std::vector<std::int64_t>> numbers;

    bool is_first = true;
    while (std::getline(sin, line)) {
        if (line.empty()) [[unlikely]] {
            continue;
        }
        std::istringstream line_sin(line);
        if (line[0] != '*' && line[0] != '+') {
            std::int64_t number = 0;
            if (is_first) [[unlikely]] {
                while (line_sin >> number) {
                    numbers.emplace_back(std::vector<std::int64_t> {number});
                }
                is_first = false;
            } else {
                for (auto& vec : numbers) {
                    line_sin >> number;
                    vec.emplace_back(number);
                }
            }
        } else {
            char ch;
            for (auto& vec : numbers) {
                line_sin >> ch;
                result += std::ranges::fold_left(vec, (std::int64_t)(ch == '*'), ch == '*' ? [](std::int64_t acc, std::int64_t n) noexcept {
                    return acc * n;
                } : [](std::int64_t acc, std::int64_t n) noexcept {
                            return acc + n;
                        });
            }
        }
    }
    return std::to_string(result);
}

[[nodiscard]] static std::string SolvePart2(const std::string& input) {
    auto numbers = input | std::views::split('\n') | std::views::filter([](auto&& line) {
                       return !line.empty();
                   }) |
                   std::views::transform([](auto&& line) {
                       return std::string(std::string_view(line));
                   }) |
                   std::ranges::to<std::vector<std::string>>();
    const auto operators = numbers.back() | std::views::filter([](const char ch) {
                               return ch != ' ';
                           }) |
                           std::ranges::to<std::vector<char>>();
    numbers.pop_back();
    const auto   ncol   = numbers[0].size();
    std::int64_t result = 0, current_value = 0;
    auto         op_pos = operators.size() - 1;

    for (std::int64_t i = (std::int64_t)ncol - 1; i >= 0;) {
        bool is_reading_number = false;
        current_value          = operators[op_pos] == '+' ? 0 : 1;
        for (; i >= 0; --i) {
            std::int64_t number   = 0;
            bool         is_blank = true;
            for (const auto& row : numbers) {
                if (row[i] != ' ') {
                    number   = number * 10 + row[i] - '0';
                    is_blank = false;
                }
            }
            if (is_blank) {
                if (!is_reading_number) {
                    continue;
                } else {
                    result += current_value;
                    current_value = 0;
                    --i;
                    --op_pos;
                    break;
                }
            } else {
                is_reading_number = true;
                current_value     = operators[op_pos] == '+' ? current_value + number : current_value * number;
            }
        }
    }
    return std::to_string(result + current_value);
}

static std::string Solve(std::uint64_t part, const std::string& input) {
    if (part == 1) {
        return SolvePart1(input);
    } else {
        return SolvePart2(input);
    }
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 6, Solve)

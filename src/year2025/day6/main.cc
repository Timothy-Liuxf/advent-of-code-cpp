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

static std::string Solve(std::uint64_t part, const std::string& input) {
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
    if (part == 1) {
        // Part 1
        return std::to_string(result);
    } else {
        // Part 2
        throw std::runtime_error("Not implemented yet.");
    }
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 6, Solve)

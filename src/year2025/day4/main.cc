#include <config.h>

#include <algorithm>
#include <array>
#include <ranges>
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

static std::string Solve(std::uint64_t part, std::string_view input) {
    const auto diagram = std::views::split(input, "\n"sv) | std::views::filter([](auto &&line) {
                             return std::ranges::distance(line) != 0;
                         }) |
                         std::views::transform([](auto &&line) {
                             return line | std::views::transform([](auto ch) {
                                        return ch == '@' ? 1 : 0;
                                    }) |
                                    std::ranges::to<std::vector<int>>();
                         }) |
                         std::ranges::to<std::vector<std::vector<int>>>();
    const auto nrow     = (int)diagram.size();
    const auto ncol     = (int)diagram[0].size();
    const auto in_range = [nrow, ncol](int row, int col) {
        return row >= 0 && row < nrow && col >= 0 && col < ncol;
    };
    const std::array<std::pair<int, int>, 8> directions = {{
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0, -1},
        {0, 1},
        {1, -1},
        {1, 0},
        {1, 1},
    }};
    if (part == 1) {
        // Part 1
        std::uint64_t result = 0;
        for (int i = 0; i < nrow; ++i) {
            for (int j = 0; j < ncol; ++j) {
                if (diagram[i][j] == 0) {
                    continue;
                }
                std::uint64_t cnt = 0;
                for (const auto &direct : directions) {
                    const auto x = i + direct.first, y = j + direct.second;
                    if (in_range(x, y)) [[likely]] {
                        cnt += diagram[x][y];
                    }
                }
                if (cnt < 4) {
                    ++result;
                }
            }
        }
        return std::to_string(result);
    } else {
        // Part 2
        throw std::runtime_error("Part 2 not implemented.");
    }
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(Solve)

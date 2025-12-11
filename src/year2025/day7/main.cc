#include <config.h>

#include <algorithm>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include <common/common.hpp>
#include <utils/cmd.hpp>
#include <utils/strconv.hpp>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;
using namespace ADVENT_OF_CODE_CPP_NAMESPACE;

static std::string Solve(std::uint64_t part, std::string_view input) {
    auto diagram = input | std::views::split('\n') | std::views::filter([](auto&& line) {
                       return !line.empty();
                   }) |
                   std::views::transform([](auto&& line) {
                       return std::string(std::string_view(line));
                   }) |
                   std::ranges::to<std::vector<std::string>>();
    const auto nrow = diagram.size(), ncol = diagram[0].size();
    const auto [start_row, start_col] = [&]() {
        for (std::size_t i = 0; i < nrow; ++i) {
            for (std::size_t j = 0; j < ncol; ++j) {
                if (diagram[i][j] == 'S') {
                    return std::make_pair(i, j);
                }
            }
        }
        throw std::runtime_error("Start position not found");
    }();

    auto beams  = std::unordered_map<std::size_t, std::size_t> {{start_col, 1}};
    auto nsplit = 0uz;
    for (auto i = start_row + 1; i < nrow; ++i) {
        auto next_beams = std::unordered_map<std::size_t, std::size_t> {};
        for (const auto [j, ntime] : beams) {
            if (diagram[i][j] == '^') {
                if ((std::int64_t)j - 1 >= 0) {
                    next_beams[j - 1] += ntime;
                }
                if (j + 1 < ncol) {
                    next_beams[j + 1] += ntime;
                }
                ++nsplit;
            } else {
                next_beams[j] += ntime;
            }
        }
        beams = std::move(next_beams);
    }
    auto result = part == 1 ? nsplit : std::ranges::fold_left(beams, 0uz, [](std::size_t acc, auto&& beam) {
        return acc + beam.second;
    });
    return std::to_string(result);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 7, Solve)

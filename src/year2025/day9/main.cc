#include <config.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <exception>
#include <ranges>
#include <span>
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

using Coord = std::pair<std::int64_t, std::int64_t>;

[[nodiscard]] static ADVENT_OF_CODE_CPP_ALWAYS_INLINE std::int64_t GetRectArea(const Coord& point1,
                                                                               const Coord& point2) {
    return std::abs(point1.first - point2.first + 1) * std::abs(point1.second - point2.second + 1);
}

[[nodiscard]]

static std::string Solve(std::uint64_t part, std::string_view input) {
    if (part != 1) {
        std::terminate();
    }

    auto red_tiles =
        input | std::views::split('\n') | std::views::filter([](auto&& line) {
            return !line.empty();
        }) |
        std::views::transform([](auto&& line) {
            // return coord a vector<pair<int64, int64>>, and avoid vector<int64>
            auto coord = std::array<std::int64_t, 2uz> {};
            for (const auto [i, val] : line | std::views::split(',') | std::views::transform([](auto&& number) {
                                           return utils::StringViewToIntegral<std::int64_t>(std::string_view(number));
                                       }) | std::views::enumerate) {
                coord[i] = val;
            }
            return std::make_pair(coord[0], coord[1]);
        }) |
        std::ranges::to<std::vector<Coord>>();
    auto areas = red_tiles | std::views::enumerate | std::views::transform([&red_tiles](auto&& indexed_tile) {
                     const auto [i, tile] = indexed_tile;
                     return std::span<Coord>(red_tiles.begin() + i + 1, red_tiles.end()) |
                            std::views::transform([&tile](const auto& other_tile) {
                                return GetRectArea(tile, other_tile);
                            });
                 }) |
                 std::views::join;
    const auto result = std::ranges::max(areas);
    return std::to_string(result);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 9, Solve)

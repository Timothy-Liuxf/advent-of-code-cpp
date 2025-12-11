#include <config.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <format>
#include <ranges>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

#include <common/common.hpp>
#include <utils/cmd.hpp>
#include <utils/strconv.hpp>
#include <utils/types.hpp>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;
using namespace ADVENT_OF_CODE_CPP_NAMESPACE;

using Coord = std::pair<std::int64_t, std::int64_t>;

struct VerticalEdge {
    std::int64_t y;
    std::int64_t x1;
    std::int64_t x2;

    VerticalEdge(const Coord& start, const Coord& end) {
        if (start.second == end.second) {
            this->y  = start.second;
            this->x1 = std::min(start.first, end.first);
            this->x2 = std::max(start.first, end.first);
        } else {
            throw std::invalid_argument(std::format("Not a vertical edge: ({}, {}) to ({}, {})", start.first,
                                                    start.second, end.first, end.second));
        }
    }
};

struct HorizontalEdge {
    std::int64_t x;
    std::int64_t y1;
    std::int64_t y2;

    HorizontalEdge(const Coord& start, const Coord& end) {
        if (start.first == end.first) {
            this->x  = start.first;
            this->y1 = std::min(start.second, end.second);
            this->y2 = std::max(start.second, end.second);
        } else {
            throw std::invalid_argument(std::format("Not a horizontal edge: ({}, {}) to ({}, {})", start.first,
                                                    start.second, end.first, end.second));
        }
    }
};

[[nodiscard]] ADVENT_OF_CODE_CPP_ALWAYS_INLINE static std::variant<VerticalEdge, HorizontalEdge> CreateEdge(
    const Coord& start, const Coord& end) {
    if (start.first == end.first) {
        return HorizontalEdge(start, end);
    } else if (start.second == end.second) {
        return VerticalEdge(start, end);
    }
    throw std::invalid_argument(std::format("Not a vertical or horizontal edge: ({}, {}) to ({}, {})", start.first,
                                            start.second, end.first, end.second));
}

[[nodiscard]] ADVENT_OF_CODE_CPP_ALWAYS_INLINE static bool RightIntersect(const Coord&        point,
                                                                          const VerticalEdge& constraint) noexcept {
    return point.first >= constraint.x1 && point.first < constraint.x2 && point.second < constraint.y;
}

[[nodiscard]] ADVENT_OF_CODE_CPP_ALWAYS_INLINE static bool OnEdge(const Coord&        point,
                                                                  const VerticalEdge& constraint) noexcept {
    return point.second == constraint.y && point.first >= constraint.x1 && point.first <= constraint.x2;
}

[[nodiscard]] ADVENT_OF_CODE_CPP_ALWAYS_INLINE static bool OnEdge(const Coord&          point,
                                                                  const HorizontalEdge& constraint) noexcept {
    return point.first == constraint.x && point.second >= constraint.y1 && point.second <= constraint.y2;
}

[[nodiscard]] ADVENT_OF_CODE_CPP_ALWAYS_INLINE static bool EdgeIntersects(const HorizontalEdge& edge1,
                                                                          const VerticalEdge&   edge2) noexcept {
    return edge2.x1 < edge1.x && edge1.x < edge2.x2 && edge1.y1 < edge2.y && edge2.y < edge1.y2;
}

[[nodiscard]] ADVENT_OF_CODE_CPP_ALWAYS_INLINE static bool EdgeIntersects(const VerticalEdge&   edge1,
                                                                          const HorizontalEdge& edge2) noexcept {
    return EdgeIntersects(edge2, edge1);
}

[[nodiscard]] static ADVENT_OF_CODE_CPP_ALWAYS_INLINE std::int64_t GetRectArea(const Coord& point1,
                                                                               const Coord& point2) {
    return (std::abs(point1.first - point2.first) + 1) * (std::abs(point1.second - point2.second) + 1);
}

[[nodiscard]] static std::string SolvePart1(std::vector<Coord> red_tiles);
[[nodiscard]] static std::string SolvePart2(std::vector<Coord> red_tiles);

static std::string Solve(std::uint64_t part, std::string_view input) {
    auto red_tiles =
        input | std::views::split('\n') | std::views::filter([](auto&& line) {
            return !line.empty();
        }) |
        std::views::transform([](auto&& line) {
            auto coord = std::array<std::int64_t, 2uz> {};
            for (const auto [i, val] : line | std::views::split(',') | std::views::transform([](auto&& number) {
                                           return utils::StringViewToIntegral<std::int64_t>(std::string_view(number));
                                       }) | std::views::enumerate) {
                coord[i] = val;
            }
            return std::make_pair(coord[0], coord[1]);
        }) |
        std::ranges::to<std::vector<Coord>>();
    return part == 1 ? SolvePart1(std::move(red_tiles)) : SolvePart2(std::move(red_tiles));
}

[[nodiscard]] static std::string SolvePart1(std::vector<Coord> red_tiles) {
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

[[nodiscard]] static std::string SolvePart2(std::vector<Coord> red_tiles) {
    auto vertical_edges   = std::vector<VerticalEdge> {};
    auto horizontal_edges = std::vector<HorizontalEdge> {};
    for (const auto i : std::views::iota(0uz, red_tiles.size())) {
        const auto start_tile = red_tiles[i];
        const auto end_tile   = red_tiles[(i + 1) % red_tiles.size()];
        std::visit(utils::Overloaded {[&](const VerticalEdge& ve) {
                                          vertical_edges.emplace_back(ve);
                                      },
                                      [&](const HorizontalEdge& he) {
                                          horizontal_edges.emplace_back(he);
                                      }},
                   CreateEdge(start_tile, end_tile));
    }

    auto max_area = 0z;
    for (auto i = 0uz; i < red_tiles.size(); ++i) {
        const auto& tile = red_tiles[i];
        for (auto j = i + 1uz; j < red_tiles.size(); ++j) {
            const auto& other_tile = red_tiles[j];
            const auto  area       = GetRectArea(tile, other_tile);
            if (area <= max_area) {
                continue;
            }

            const auto other_vertices = std::array<Coord, 2> {{
                Coord {tile.first, other_tile.second},
                Coord {other_tile.first, tile.second},
            }};

            const auto point_on_edge = [&](const Coord& point, const auto& edge) {
                if (OnEdge(point, edge)) [[unlikely]] {
                    return true;
                }
                return false;
            };
            const auto in_range = [&](const Coord& point) {
                const auto on_edge = [&](const auto& edge) {
                    return point_on_edge(point, edge);
                };
                if (std::ranges::any_of(horizontal_edges, on_edge) || std::ranges::any_of(vertical_edges, on_edge))
                    [[unlikely]] {
                    return true;
                }
                const auto intersect_count = std::ranges::count_if(vertical_edges, [&](const auto& edge) {
                    return RightIntersect(point, edge);
                });
                if ((intersect_count & 1) == 0) {
                    return false;
                }
                return true;
            };

            bool valid = true;

            {
                /*
                 * Step 1: check the other two vertices
                 */
                if (std::ranges::any_of(other_vertices, [&](const auto& vertice) {
                        return !in_range(vertice);
                    })) {
                    valid = false;
                    goto check_validation;
                }
            }

            {
                /*
                 * Step 2: a special case of Step 3.
                 *   To prevent exceptions:
                 *     the boundary may coincides with the side of the rectangle.
                 *   Therefore, check middle points of each side.
                 */
                const auto mid_points = std::array<Coord, 4> {{
                    Coord {(tile.first + other_tile.first) / 2, tile.second},
                    Coord {(tile.first + other_tile.first) / 2, other_tile.second},
                    Coord {tile.first, (tile.second + other_tile.second) / 2},
                    Coord {other_tile.first, (tile.second + other_tile.second) / 2},
                }};
                if (std::ranges::any_of(mid_points, [&](const auto& mid_point) {
                        return !in_range(mid_point);
                    })) {
                    valid = false;
                    goto check_validation;
                }
            }

            {
                /*
                 * Step 3: check whether the four edges intersect with any boundary edges.
                 */
                const auto rect_edges = std::array<std::variant<VerticalEdge, HorizontalEdge>, 4> {{
                    HorizontalEdge {Coord {tile.first, tile.second}, Coord {tile.first, other_tile.second}},
                    HorizontalEdge {Coord {other_tile.first, tile.second}, Coord {other_tile.first, other_tile.second}},
                    VerticalEdge {Coord {tile.first, tile.second}, Coord {other_tile.first, tile.second}},
                    VerticalEdge {Coord {tile.first, other_tile.second}, Coord {other_tile.first, other_tile.second}},
                }};
                for (const auto& rect_edge : rect_edges) {
                    const auto intersects = std::visit(
                        utils::Overloaded {[&](const VerticalEdge& ve) {
                                               return std::ranges::any_of(horizontal_edges, [&](const auto& he) {
                                                   return EdgeIntersects(ve, he);
                                               });
                                           },
                                           [&](const HorizontalEdge& he) {
                                               return std::ranges::any_of(vertical_edges, [&](const auto& ve) {
                                                   return EdgeIntersects(he, ve);
                                               });
                                           }},
                        rect_edge);
                    if (intersects) {
                        valid = false;
                        goto check_validation;
                    }
                }
            }

            {
                /*
                 * Step 4: check whether red_tiles in rectagle
                 */
                for (const auto& check_tile : red_tiles) {
                    if (check_tile.first > std::min(tile.first, other_tile.first) &&
                        check_tile.first < std::max(tile.first, other_tile.first) &&
                        check_tile.second > std::min(tile.second, other_tile.second) &&
                        check_tile.second < std::max(tile.second, other_tile.second)) {
                        valid = false;
                        goto check_validation;
                    }
                }
            }
        check_validation:
            if (valid) {
                max_area = area;
            }
        }
    }
    return std::to_string(max_area);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 9, Solve)

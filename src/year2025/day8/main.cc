#include <config.h>

#include <algorithm>
#include <ranges>
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

struct Coord {
    std::int64_t x;
    std::int64_t y;
    std::int64_t z;
};

[[nodiscard]] static ADVENT_OF_CODE_CPP_ALWAYS_INLINE std::int64_t SquaredDistance(const Coord& a,
                                                                                   const Coord& b) noexcept {
    const auto dx = a.x - b.x;
    const auto dy = a.y - b.y;
    const auto dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

class UnionFind {
public:
    explicit UnionFind(std::size_t n) : parent_(n), rank_(n) {
        for (auto i = 0uz; i < n; ++i) {
            this->parent_[i] = i;
            this->rank_[i]   = 1;
        }
    }

    std::size_t Find(std::size_t x) noexcept {
        return parent_[x] == x ? x : this->parent_[x] = this->Find(parent_[x]);
    }

    std::size_t Union(std::size_t x, std::size_t y) noexcept {
        const auto root_x = this->Find(x);
        const auto root_y = this->Find(y);
        if (root_x != root_y) {
            this->parent_[root_y] = root_x;
            this->rank_[root_x] += this->rank_[root_y];
        }
        return this->rank_[root_x];
    }

    const std::vector<std::size_t>& GetParents() const noexcept {
        return this->parent_;
    }

private:
    std::vector<std::size_t> parent_;
    std::vector<std::size_t> rank_;
};

static std::string Solve(std::uint64_t part, std::string_view input) {
    const auto points =
        input | std::views::split("\n"sv) | std::views::filter([](auto&& line) {
            return !line.empty();
        }) |
        std::views::transform([](auto&& line) {
            auto coord = std::string_view(line) | std::views::split(',') | std::views::transform([](auto&& number_str) {
                             return utils::StringViewToIntegral<std::int64_t>(std::string_view(number_str));
                         });
            // coord[0] is x, coord[1] is y, coord[2] is z
            auto itr = coord.begin();
            return Coord {*itr++, *itr++, *itr++};
        }) |
        std::ranges::to<std::vector<Coord>>();

    /*
     * Here I use Brute Force to connect the closest 1000 edges.
     * However, this can be optimized using some spatial partitioning methods,
     *   such as k-d tree: https://en.wikipedia.org/wiki/K-d_tree
     */
    auto edges = std::vector<std::pair<std::int64_t, std::pair<std::size_t, std::size_t>>> {};
    edges.reserve(points.size() * points.size() / 2uz + 1uz);
    for (auto i = 0uz; i < points.size(); ++i) {
        for (auto j = i + 1uz; j < points.size(); ++j) {
            const auto dist = SquaredDistance(points[i], points[j]);
            edges.emplace_back(dist, std::make_pair(i, j));
        }
    }
    std::ranges::sort(edges, [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    UnionFind uf(points.size());
    if (part != 1) {
        // Part 2
        for (const auto& edge : edges) {
            const auto [i, j] = edge.second;
            const auto rank   = uf.Union(i, j);
            if (rank == points.size()) {
                return std::to_string(points[i].x * points[j].x);
            }
        }
        std::unreachable();
    }

    constexpr std::size_t kConnectEdges  = 1000uz;
    constexpr std::size_t kCountCircuits = 3uz;
    for (auto k = 0uz; k < kConnectEdges; ++k) {
        const auto [i, j] = edges[k].second;
        uf.Union(i, j);
    }

    std::vector<std::pair<std::size_t, std::size_t>> circuit_sizes(points.size());
    for (auto i = 0uz; i < points.size(); ++i) {
        circuit_sizes[i].first = i;
        ++circuit_sizes[uf.Find(i)].second;
    }
    std::ranges::sort(circuit_sizes, [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    std::size_t result = 1;
    for (auto i = 0uz; i < kCountCircuits; ++i) {
        result *= circuit_sizes[i].second;
    }
    return std::to_string(result);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 8, Solve)

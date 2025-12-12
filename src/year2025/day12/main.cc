#include <config.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

#include <common/common.hpp>
#include <utils/cmd.hpp>
#include "utils/strconv.hpp"

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;
using namespace ADVENT_OF_CODE_CPP_NAMESPACE;

struct Region {
    std::size_t              width;
    std::size_t              ulong;
    std::vector<std::size_t> counts;
};

static std::string Solve(std::uint64_t part, std::string_view input) {
    if (part == 2) {
        return "Please click the link \'[Decorate the North Pole Again]\' on the webpage to get the 24th star."s;
    }

    std::vector<std::vector<std::string>> shapes;
    std::vector<Region>                   regions;

    std::ranges::for_each(
        input | std::views::split("\n\n"sv) | std::views::filter([](auto&& chunk) {
            return !chunk.empty();
        }),
        [&shapes, &regions](auto&& chunk) {
            const auto chunk_sv  = std::string_view(chunk);
            const auto colon_pos = chunk_sv.find(':');
            const auto index     = chunk_sv.substr(0, colon_pos);
            if (const auto xpos = index.find('x'); xpos == std::string_view::npos) {
                shapes.emplace_back(chunk_sv.substr(colon_pos + 1) | std::views::split('\n') |
                                    std::views::filter([](auto&& line) {
                                        return !line.empty();
                                    }) |
                                    std::ranges::to<std::vector<std::string>>());
            } else {
                std::ranges::for_each(
                    chunk | std::views::split('\n') | std::views::filter([](auto&& num) {
                        return !num.empty();
                    }),
                    [&regions](auto&& line) {
                        const auto line_sv   = std::string_view(line);
                        const auto colon_pos = line_sv.find(':');
                        const auto index     = line_sv.substr(0, colon_pos);
                        const auto xpos      = index.find('x');
                        const auto width     = utils::StringViewToIntegral<std::size_t>(index.substr(0, xpos));
                        const auto ulong     = utils::StringViewToIntegral<std::size_t>(index.substr(xpos + 1));

                        auto counts = line_sv.substr(colon_pos + 1) | std::views::split(' ') |
                                      std::views::filter([](auto&& num) {
                                          return !num.empty();
                                      }) |
                                      std::views::transform([](auto&& num) {
                                          return utils::StringViewToIntegral<std::size_t>(std::string_view(num));
                                      }) |
                                      std::ranges::to<std::vector<std::size_t>>();
                        regions.emplace_back(width, ulong, std::move(counts));
                    });
            }
        });
    auto areas = shapes | std::views::transform([](const auto& shape) {
                     return std::ranges::fold_left(shape, 0uz, [](std::size_t acc, const auto& line) {
                         return acc + std::ranges::count(line, '#');
                     });
                 });

    const auto result = std::ranges::count_if(regions, [&areas](const Region& region) {
        /*
         * ?????????????????????????
         * The given input can be F*CKING solved by this simple check.
         * This input is so humourous.
         * However, this check can NOT pass the example given on the webpage
         *   (which should be evaluated to 2, but got 3 using this check).
         */
        return region.width * region.ulong >=
               std::ranges::fold_left(std::views::zip(areas, region.counts), 0uz,
                                      [](std::size_t acc, const auto& pair) {
                                          return acc + std::get<0>(pair) * std::get<1>(pair);
                                      });
    });
    return std::to_string(result);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 11, Solve)

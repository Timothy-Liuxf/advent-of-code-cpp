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

using ID      = std::uint64_t;
using IDRange = std::pair<ID, ID>;

[[nodiscard]] static ADVENT_OF_CODE_CPP_ALWAYS_INLINE std::vector<IDRange> SortAndMergeRanges(
    std::vector<IDRange>& ranges) {
    std::ranges::sort(ranges, [](const IDRange& range1, const IDRange& range2) {
        return range1.first < range2.first;
    });
    std::vector<IDRange> merged_ranges;
    merged_ranges.reserve(ranges.size());
    merged_ranges.emplace_back(ranges[0]);
    for (auto i = 1uz; i < ranges.size(); ++i) {
        if (ranges[i].first > merged_ranges.back().second) {
            merged_ranges.emplace_back(ranges[i]);
        } else {
            merged_ranges.back().second = std::max(merged_ranges.back().second, ranges[i].second);
        }
    }
    return merged_ranges;
}

static std::string Solve(std::uint64_t part, std::string_view input) {
    (void)input;
    if (part == 1) {
        // Part 1
        std::vector<IDRange> ranges;
        std::vector<IDRange> merged_ranges;
        auto                 result = std::ranges::count_if(
            std::views::split(input, "\n"sv) | std::views::drop_while([&ranges, &merged_ranges](auto&& line) {
                std::string_view line_sv = std::string_view(&*line.begin(), std::ranges::distance(line));
                const bool       is_empty = line_sv.empty();
                if (!is_empty) [[likely]] {
                    if (const auto dash_pos = line_sv.find('-'); dash_pos == std::string_view::npos) [[unlikely]] {
                        throw std::runtime_error(std::format("Invalid id range: {}", line_sv));
                    } else {
                        const auto start_id = utils::StringViewToIntegral<ID>(line_sv.substr(0, dash_pos));
                        const auto end_id = utils::StringViewToIntegral<ID>(line_sv.substr(dash_pos + 1));
                        ranges.emplace_back(start_id, end_id);
                    }
                    return true;
                } else {
                    merged_ranges = SortAndMergeRanges(ranges);
                    return false;
                }
            }),
            [&merged_ranges](auto&& line) {
                auto line_sv = std::string_view(&*line.begin(), std::ranges::distance(line));
                if (line_sv.empty()) [[unlikely]] {
                    return false;
                }
                auto id = utils::StringViewToIntegral<ID>(line_sv);
                return id <= merged_ranges.back().second &&
                       std::lower_bound(
                           merged_ranges.begin(), merged_ranges.end(), id, [](const IDRange& range, ID id) {
                               return range.second < id;
                           })->first <= id;
            });
        return std::to_string(result);
    } else {
        // Part 2
        auto ranges = std::views::split(input, "\n"sv) | std::views::take_while([](auto&& line) {
                          return !line.empty();
                      }) |
                      std::views::transform([](auto&& line) {
                          std::string_view line_sv  = std::string_view(&*line.begin(), std::ranges::distance(line));
                          const auto       dash_pos = line_sv.find('-');
                          if (dash_pos == std::string_view::npos) [[unlikely]] {
                              throw std::runtime_error(std::format("Invalid id range: {}", line_sv));
                          }
                          const auto start_id = utils::StringViewToIntegral<ID>(line_sv.substr(0, dash_pos));
                          const auto end_id   = utils::StringViewToIntegral<ID>(line_sv.substr(dash_pos + 1));
                          return std::make_pair(start_id, end_id);
                      }) |
                      std::ranges::to<std::vector<IDRange>>();
        auto       merged_ranges = SortAndMergeRanges(ranges);
        const auto result = std::ranges::fold_left(merged_ranges, 0uz, [](std::uint64_t acc, const IDRange& range) {
            return acc + (range.second - range.first + 1);
        });
        return std::to_string(result);
    }
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 5, Solve)

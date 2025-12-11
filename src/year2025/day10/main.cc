#include <config.h>

#include <algorithm>
#include <cmath>
#include <format>
#include <functional>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <common/common.hpp>
#include <utils/cmd.hpp>
#include <utils/strconv.hpp>
#include <utils/types.hpp>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;
using namespace ADVENT_OF_CODE_CPP_NAMESPACE;

static std::string Solve(std::uint64_t part, std::string_view input) {
    if (part == 2) {
        throw std::invalid_argument("Part 2 not implemented yet");
    }

    auto result = std::ranges::fold_left(
        input | std::views::split('\n') | std::views::filter([](auto&& record) {
            return !record.empty();
        }) | std::views::transform([](auto&& record) {
            const auto record_sv = std::string_view(record);
            const auto diag_pos  = record_sv.find(']');
            if (diag_pos == std::string::npos) {
                throw std::invalid_argument(std::format("Invalid input: {}", record_sv));
            }

            std::uint64_t diagram = 0;
            for (auto [i, ch] :
                 std::string_view {record_sv.begin() + 1, record_sv.begin() + diag_pos} | std::views::enumerate) {
                diagram |= (((std::uint64_t)ch == '#' ? 1 : 0) << i);
            }

            const auto joltage_req_pos = record_sv.find('{');
            if (joltage_req_pos == std::string::npos) {
                throw std::invalid_argument(std::format("Invalid input: {}", record_sv));
            }

            const auto schema_sv =
                std::string_view {record_sv.begin() + diag_pos + 1, record_sv.begin() + joltage_req_pos};
            const auto buttons =
                schema_sv | std::views::split(' ') | std::views::filter([](auto&& line) {
                    return !line.empty();
                }) |
                std::views::transform([](auto&& line) {
                    const auto line_sv = std::string_view(line);
                    if (line_sv.front() != '(' || line_sv.back() != ')') {
                        throw std::invalid_argument(std::format("Invalid button schema: {}", line_sv));
                    }
                    const auto    button_sv  = std::string_view {line_sv.begin() + 1, line_sv.end() - 1};
                    std::uint64_t press_mask = 0;
                    std::ranges::for_each(
                        button_sv | std::views::split(',') | std::views::transform([](auto&& number) {
                            return utils::StringViewToIntegral<std::uint64_t>(std::string_view(number));
                        }),
                        [&press_mask](std::uint64_t number) {
                            press_mask |= (1u << number);
                        });
                    return press_mask;
                }) |
                std::ranges::to<std::vector<std::uint64_t>>();

            std::size_t min_npress = buttons.size() + 1uz;

            const auto mask_end = 1uz << buttons.size();
            for (auto mask = 0uz; mask < mask_end; ++mask) {
                std::uint64_t current_diag = 0;

                auto current_mask = mask;
                auto npress       = 0uz;
                while (current_mask != 0) {
                    const auto lowest_set_bit = current_mask & -current_mask;
                    const auto button_index   = (std::size_t)__builtin_ctzll(lowest_set_bit);
                    current_diag ^= buttons[button_index];
                    current_mask &= ~lowest_set_bit;
                    ++npress;
                }
                if (current_diag == diagram && npress < min_npress) {
                    min_npress = npress;
                }
            }
            return min_npress;
        }),
        0uz, std::plus {});
    return std::to_string(result);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 10, Solve)

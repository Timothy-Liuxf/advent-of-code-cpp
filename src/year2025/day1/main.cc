#include <config.h>

#include <algorithm>
#include <concepts>
#include <ranges>
#include <string>
#include <string_view>

#include <common/common.hpp>
#include <utils/cmd.hpp>
#include <utils/strconv.hpp>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;
using namespace ADVENT_OF_CODE_CPP_NAMESPACE;

static std::string Solve(std::uint64_t part, std::string_view input) {
    int current_pos = 50;
    int count       = 0;
    std::ranges::for_each(std::views::split(input, "\n"sv), [&current_pos, &count, part](auto &&operation) {
        // get the string_view of each line
        auto line_sv = std::string_view(&*operation.begin(), std::ranges::distance(operation));
        if (line_sv.empty()) [[unlikely]] {
            return;
        }

        const int  step      = utils::StringViewToIntegral<int>(line_sv.substr(1));
        const char direction = line_sv[0];
        if (part == 1) {
            // Part 1
            if (direction == 'R') {
                current_pos = (current_pos + step) % 100;
            } else {
                current_pos = (current_pos - step + 100) % 100;
            }
            if (current_pos == 0) {
                ++count;
            }
        } else {
            // Part 2
            if (direction == 'R') {
                auto next_pos = current_pos + step;
                if (next_pos >= 100) {
                    count += next_pos / 100;
                    current_pos = next_pos % 100;
                } else {
                    current_pos = next_pos;
                }
            } else {
                auto next_pos = current_pos - step;
                if (next_pos <= 0) {
                    count += (step - current_pos) / 100 + !!current_pos;
                    current_pos = ((next_pos % 100) + 100) % 100;
                } else {
                    current_pos = next_pos;
                }
            }
        }
    });
    return std::to_string(count);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(Solve)

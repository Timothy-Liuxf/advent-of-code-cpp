#include <config.h>

#include <algorithm>
#include <cstdint>
#include <format>
#include <ranges>
#include <stdexcept>
#include <string_view>

#include <tclap/CmdLine.h>

#include <common/common.hpp>
#include <utils/cmd.hpp>
#include <utils/strconv.hpp>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;
using namespace ADVENT_OF_CODE_CPP_NAMESPACE;

using ID = std::uint64_t;

/*
 * The solution to Part 2 can be seen on LeetCode:
 *     https://leetcode.com/problems/repeated-substring-pattern/
 * The offical Chinese (Simplified) website:
 *     https://leetcode.cn/problems/repeated-substring-pattern/solutions/386481/zhong-fu-de-zi-zi-fu-chuan-by-leetcode-solution/
 *   provided four different solutions.
 * Here I adopted the simpliest solution (the 2nd solution).
 * However, the fastest solution is the 4th solution, as below:
 *     bool KMP(const string& pattern) {
 *         int n = pattern.size();
 *         vector<int> fail(n, -1);
 *         for (int i = 1; i < n; ++i) {
 *             int j = fail[i - 1];
 *             while (j != -1 && pattern[j + 1] != pattern[i]) {
 *                 j = fail[j];
 *             }
 *             if (pattern[j + 1] == pattern[i]) {
 *                 fail[i] = j + 1;
 *             }
 *         }
 *         return fail[n - 1] != -1 && n % (n - fail[n - 1] - 1) == 0;
 *     }
 *
 *     bool IsInvalidID(ID id) {
 *         return KMP(to_string(id));
 *     }
 */

[[nodiscard]] static ID IsInvalidID(ID id, std::uint64_t part) {
    auto id_str = std::to_string(id);
    if (part == 2) {
        // Part 2
        return (id_str + id_str).find(id_str, 1) != id_str.size();
    }

    // Part 1
    if (id_str.size() & 1) {
        return false;
    }
    auto id_sv = std::string_view(id_str);
    return id_sv.substr(0, id_sv.size() / 2) == id_sv.substr(id_sv.size() / 2);
}

static std::string Solve(std::uint64_t part, std::string_view input) {
    ID result = 0;
    std::ranges::for_each(std::views::split(input, ","sv), [part, &result](auto &&operation) {
        // get the string_view of each line
        auto id_range_sv = std::string_view(&*operation.begin(), std::ranges::distance(operation));
        if (auto dash_pos = id_range_sv.find('-'); dash_pos == std::string_view::npos) [[unlikely]] {
            throw std::runtime_error(std::format("Invalid id range: {}", id_range_sv));
        } else {
            auto start_id = utils::StringViewToIntegral<ID>(id_range_sv.substr(0, dash_pos));
            auto end_id   = utils::StringViewToIntegral<ID>(id_range_sv.substr(dash_pos + 1));
            for (auto id = start_id; id <= end_id; ++id) {
                if (IsInvalidID(id, part)) {
                    result += id;
                }
            }
        }
    });
    return std::to_string(result);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 2, Solve)

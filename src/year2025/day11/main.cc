#include <config.h>

#include <algorithm>
#include <cmath>
#include <format>
#include <functional>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include <common/common.hpp>
#include <utils/cmd.hpp>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;
using namespace ADVENT_OF_CODE_CPP_NAMESPACE;

struct Device {
    std::string              name;
    std::vector<std::string> outputs;
};

static std::string Solve(std::uint64_t part, std::string_view input) {
    if (part == 2) {
        throw std::runtime_error("Part 2 not implemented yet");
    }

    auto    devices     = std::unordered_map<std::string, std::unique_ptr<Device>> {};
    Device* root_device = nullptr;
    std::ranges::for_each(
        input | std::views::split('\n') | std::views::filter([](auto&& line) {
            return !line.empty();
        }) | std::views::transform([](auto&& line) {
            return std::string_view(line);
        }),
        [&](std::string_view line) {
            const auto colon_pos = line.find(':');
            if (colon_pos == std::string_view::npos) {
                throw std::runtime_error(std::format("Invalid line: {}", line));
            }

            const auto device_name = std::string(line.substr(0, colon_pos));
            const auto ptr =
                (devices[device_name] = std::make_unique<Device>(
                     device_name,
                     line.substr(colon_pos + 1) | std::views::split(' ') | std::views::filter([](auto&& output) {
                         return !output.empty();
                     }) | std::views::transform([](auto&& output) {
                         return std::string(std::string_view(output));
                     }) | std::ranges::to<std::vector<std::string>>()))
                    .get();
            if (device_name == "you"sv) {
                root_device = ptr;
            }
        });

    if (root_device == nullptr) {
        throw std::runtime_error("No 'you' device found");
    }

    auto result = 0uz;

    std::function<void(Device*)> dfs = [&](Device* device) {
        for (const auto& output : device->outputs) {
            if (output == "out"sv) {
                ++result;
            } else {
                dfs(devices[output].get());
            }
        }
    };
    dfs(root_device);

    return std::to_string(result);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 11, Solve)

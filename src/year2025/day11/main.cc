#include <config.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
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
    bool                     visited            = false;
    std::size_t              out_path_count     = 0;
    std::size_t              fft_path_count     = 0;
    std::size_t              dac_path_count     = 0;
    std::size_t              fft_dac_path_count = 0;
};

static std::string Solve(std::uint64_t part, std::string_view input) {
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
                     }) | std::ranges::to<std::vector<std::string>>(),
                     false))
                    .get();
            if (part == 1) {
                if (device_name == "you"sv) {
                    root_device = ptr;
                }
            } else {
                if (device_name == "svr"sv) {
                    root_device = ptr;
                }
            }
        });

    if (root_device == nullptr) {
        throw std::runtime_error("No 'you' or 'svr' device found");
    }

    std::function<void(Device*)> dfs = [&](Device* device) {
        device->visited = true;
        for (const auto& output : device->outputs) {
            if (output == "out"sv) {
                ++device->out_path_count;
            } else {
                auto output_device = devices[output].get();
                if (!output_device->visited) {
                    dfs(output_device);
                }
                device->out_path_count += output_device->out_path_count;
                if (output == "dac"sv) {
                    device->dac_path_count += output_device->out_path_count;
                    device->fft_dac_path_count += output_device->fft_path_count;
                    device->fft_path_count += output_device->fft_path_count;
                } else if (output == "fft"sv) {
                    device->fft_path_count += output_device->out_path_count;
                    device->dac_path_count += output_device->dac_path_count;
                    device->fft_dac_path_count += output_device->dac_path_count;
                } else {
                    device->dac_path_count += output_device->dac_path_count;
                    device->fft_path_count += output_device->fft_path_count;
                    device->fft_dac_path_count += output_device->fft_dac_path_count;
                }
            }
        }
    };
    dfs(root_device);

    const auto result = part == 1 ? root_device->out_path_count : root_device->fft_dac_path_count;
    return std::to_string(result);
}

ADVENT_OF_CODE_CPP_MAIN_FUNCTION(2025, 11, Solve)

#ifndef ADVENT_OF_CODE_CPP_UTILS_STRCONV_HPP
#define ADVENT_OF_CODE_CPP_UTILS_STRCONV_HPP

#include <charconv>
#include <concepts>
#include <format>
#include <stdexcept>
#include <string_view>

#include "common.hpp"

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_BEGIN

template <std::integral T>
[[nodiscard]] T StringViewToIntegral(std::string_view sv, int base = 10) {
    T    val = 0;
    auto res = std::from_chars(sv.data(), sv.data() + sv.size(), val, base);
    if (res.ec != std::errc {}) [[unlikely]] {
        throw std::runtime_error(std::format("Invalid number: {}, length: {}", sv, sv.size()));
    }
    return val;
}

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_END

#endif  // ADVENT_OF_CODE_CPP_UTILS_STRCONV_HPP

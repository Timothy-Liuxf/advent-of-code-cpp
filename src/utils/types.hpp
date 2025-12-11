#ifndef ADVENT_OF_CODE_CPP_UTILS_TYPES_HPP
#define ADVENT_OF_CODE_CPP_UTILS_TYPES_HPP

#include "common.hpp"

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_BEGIN

template <typename T>
constexpr T& Temporary(T&& x) {
    return static_cast<T&>(x);
}

template <typename T>
constexpr T& Temporary(T&) = delete;

template <typename... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};

#if defined(__cpp_deduction_guides) && __cpp_deduction_guides < 201907L

template <typename... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

#endif

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_END

#endif  // ADVENT_OF_CODE_CPP_UTILS_TYPES_HPP

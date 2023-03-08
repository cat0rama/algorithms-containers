#ifndef DEFINES_HPP_
#define DEFINES_HPP_

#include <cstdint>
#include <type_traits>

namespace own::defines {
    constexpr std::size_t DEFAULT_CAPACITY = 5;
    constexpr std::size_t FACTOR = 2;
    constexpr std::size_t CNULL = 0;
    constexpr bool NON_CONST = false;
    constexpr bool CONST = true;
}

#endif

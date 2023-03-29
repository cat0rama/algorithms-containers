#ifndef DEFINES_HPP_
#define DEFINES_HPP_

#include <cstdint>
#include <type_traits>

#define THROW_FURTHER throw

namespace own::defines {
constexpr int DEFAULT_HEIGHT = 1; 
constexpr std::size_t DEFAULT_CAPACITY = 5;
constexpr std::size_t FACTOR = 2;
constexpr bool NON_CONST = false;
constexpr bool CONST = true;
} // namespace own::defines

#endif

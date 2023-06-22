#ifndef DEFINES_HPP_
#define DEFINES_HPP_

#include <cstdint>
#include <type_traits>
#include <algorithm>
#include <initializer_list>
#include <exception>

// потом сделать через флаг в cmake
#define SWITCH_MODIFIRE
#define THROW_FURTHER throw

/*
 * дефайн для того чтобы в тестах можно было унаследоваться от класса
 * и получить доступ к его приватным функциям и членам
 */

#ifdef SWITCH_MODIFIRE
#define MODIFIRE public
#else
#define MODIFIRE private
#endif

namespace s21::defines {
constexpr int DEFAULT_HEIGHT = 1;
constexpr std::size_t DEFAULT_TABLE_SIZE = 32;
constexpr std::size_t DEFAULT_CAPACITY = 5;
constexpr std::size_t FACTOR = 2;
constexpr bool NON_CONST = false;
constexpr bool CONST = true;
} // namespace own::defines

#endif

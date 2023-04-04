#ifndef TYPE_TRAITS_HPP_
#define TYPE_TRAITS_HPP_

#include <cstddef>
#include <type_traits>

namespace own {
template <typename T> struct base_traits {
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_pointer = const T*;
    using const_reference = const T&;
    using difference_type = std::ptrdiff_t;
};

template <class T, class = void>
struct is_iterator : std::false_type { };

template <class T>
struct is_iterator<T, std::void_t<
    typename std::iterator_traits<T>::iterator_category
>> : std::true_type { };

} // namespace own

#endif

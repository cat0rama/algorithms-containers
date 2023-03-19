#ifndef TYPE_TRAITS_HPP_
#define TYPE_TRAITS_HPP_

#include <cstddef>

template <typename T> struct base_traits {
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_pointer = const T*;
    using const_reference = const T&;
    using difference_type = std::ptrdiff_t;
};

#endif

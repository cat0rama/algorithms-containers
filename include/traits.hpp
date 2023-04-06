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

template<typename T, typename = void>
struct is_iterator
        {
        static constexpr bool value = false;
    };

    template<typename T>
    struct is_iterator<T, typename std::enable_if
            <!std::is_same<typename std::iterator_traits<T>::value_type, void>::value>::type>
    {
        static constexpr bool value = true;
    };

    template <typename T>
    struct is_iterator_v {
        static constexpr bool value = is_iterator<T>::value;
    };

} // namespace own

#endif

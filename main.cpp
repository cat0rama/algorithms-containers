#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <type_traits>

#include "iterator.hpp"

// https://en.cppreference.com/w/cpp/container/vector
// Сборная солянка из моего и STL кода.
// Спасибо Мещерину за лекции :)

namespace own 
{
    template <class T, class Allocator = std::allocator<T>>
    class vector {
    public:
        using value_type = T;
        using allocator_type = Allocator;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const reference;
        using pointer = typename Allocator::pointer;
        using const_pointer = typename Allocator::const_pointer;
    public:
        template <bool IsIterConst>
        struct iterator_wrapper {
            using iterator_category = std::random_access_iterator_tag;
            using meta_pointer = std::conditional_t<IsIterConst, const_pointer, pointer>;
            using meta_reference = std::conditional_t<IsIterConst, const_reference, reference>;
        public:
            iterator_wrapper() noexcept : m_data(nullptr) {}

            iterator_wrapper(const iterator_wrapper& t_iter) noexcept : m_data(t_iter.m_data) {}
        public:
            meta_reference func() noexcept {
                static int a = 3;
                return a;
            }
        private:
            meta_pointer m_data;
    };
    public:
        using iterator = iterator_wrapper<false>;
        using const_iterator = iterator_wrapper<true>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    public:
        vector() = default;
    private:
        value_type m_data;
    };
}

using namespace own;

int main() {
    // Компайл тайм тестики
    static_assert(std::is_same_v<vector<int>::const_pointer, const int*>);
    static_assert(std::is_same_v<vector<int>::const_iterator::meta_pointer, const int*>);
}

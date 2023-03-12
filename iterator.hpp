#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

#include <iterator>

namespace own {

template<class It>
class reverse_iterator
{
protected:
    It current = It();
public:
    reverse_iterator() = default;
    constexpr explicit reverse_iterator(It itr) noexcept: current(itr) {}

    constexpr reverse_iterator& operator++() { --current; return *this; }

    constexpr reverse_iterator operator++(int) { auto tmp = *this; ++(*this); return tmp; }

    constexpr reverse_iterator& operator--() { ++current; return *this; }

    constexpr reverse_iterator operator--(int) { auto tmp = *this; --(*this); return tmp; }

    constexpr decltype(auto) operator*() const
    {
            return *current; // <== returns the content of prev
    }

    constexpr It base() const { return current; }

    friend constexpr bool operator==(const reverse_iterator& t_rhs, const reverse_iterator& t_lhs) noexcept {
        return t_rhs.m_data == t_lhs.m_data;
    }

    friend constexpr bool operator!=(const reverse_iterator& t_rhs, const reverse_iterator& t_lhs) noexcept {
        return t_rhs.base() != t_lhs.base();
    }

    friend constexpr bool operator>(const reverse_iterator& t_rhs, const reverse_iterator& t_lhs) noexcept {
        return t_rhs.m_data > t_lhs.m_data;
    }

    friend constexpr bool operator<(const reverse_iterator& t_rhs, const reverse_iterator& t_lhs) noexcept {
        return t_rhs.m_data < t_lhs.m_data;
    }

    friend constexpr bool operator>=(const reverse_iterator& t_rhs, const reverse_iterator& t_lhs) noexcept {
        return t_rhs.m_data >= t_lhs.m_data;
    }

    friend constexpr bool operator<=(const reverse_iterator& t_rhs, const reverse_iterator& t_lhs) noexcept {
        return t_rhs.m_data <= t_lhs.m_data;
    }
};
}

#endif

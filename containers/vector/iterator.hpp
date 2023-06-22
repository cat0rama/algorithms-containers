#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

#include <cstddef>
#include <iterator>

namespace s21 {
template <typename T, bool IsIterConst>
struct iterator_wrapper {
 protected:
  using iterator = iterator_wrapper;

 public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using const_pointer = const T*;
  using const_reference = const T&;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;
  using meta_pointer = std::conditional_t<IsIterConst, const_pointer, pointer>;
  using meta_reference =
      std::conditional_t<IsIterConst, const_reference, reference>;

 public:
  constexpr iterator_wrapper() noexcept : m_data(nullptr) {}

  constexpr iterator_wrapper(pointer t_ptr) noexcept : m_data(t_ptr) {}

  constexpr iterator_wrapper(const iterator_wrapper<T, false>& t_iter)
      : m_data(&(*t_iter)) {}

  constexpr iterator_wrapper(const iterator_wrapper<T, true>& t_iter)
      : m_data(const_cast<T*>(&(*t_iter))) {}

 public:
  constexpr iterator& operator++() noexcept {
    m_data++;
    return *this;
  }

  constexpr iterator operator++(int) noexcept {
    auto tmp = *this;
    ++(*this);
    return tmp;
  }

  constexpr iterator& operator--() noexcept {
    m_data++;
    return *this;
  }

  constexpr iterator operator--(int) noexcept {
    auto tmp = *this;
    ++(*this);
    return tmp;
  }

  constexpr meta_pointer operator->() const noexcept { return m_data; }

  constexpr meta_reference operator*() const noexcept { return *m_data; }

  constexpr meta_reference operator[](difference_type t_index) const noexcept {
    return m_data[t_index];
  }

  constexpr iterator& operator+=(difference_type t_rhs) const noexcept {
    m_data += t_rhs;
    return *this;
  }

  constexpr iterator& operator-=(difference_type t_rhs) const noexcept {
    m_data -= t_rhs;
    return *this;
  }

  constexpr iterator operator+(difference_type t_rhs) const noexcept {
    return iterator(m_data + t_rhs);
  }

  constexpr iterator operator-(difference_type t_rhs) const noexcept {
    return iterator(m_data - t_rhs);
  }

  friend constexpr iterator operator+(difference_type t_lhs,
                                      const iterator& t_rhs) noexcept {
    return iterator(t_lhs + t_rhs.m_data);
  }

  friend constexpr difference_type operator+(const iterator& t_lhs,
                                             const iterator& t_rhs) noexcept {
    return t_lhs.m_data + t_rhs.m_data;
  }
  
  friend constexpr difference_type operator-(const iterator& t_lhs,
                                             const iterator& t_rhs) noexcept {
    return t_lhs.m_data - t_rhs.m_data;
  }

  friend constexpr iterator operator-(difference_type t_lhs,
                                      const iterator& t_rhs) noexcept {
    return iterator(t_lhs - t_rhs.m_data);
  }

  friend constexpr bool operator==(const iterator& t_rhs,
                                   const iterator& t_lhs) noexcept {
    return t_rhs.m_data == t_lhs.m_data;
  }

  friend constexpr bool operator!=(const iterator& t_rhs,
                                   const iterator& t_lhs) noexcept {
    return t_rhs.m_data != t_lhs.m_data;
  }

  friend constexpr bool operator>(const iterator& t_rhs,
                                  const iterator& t_lhs) noexcept {
    return t_rhs.m_data > t_lhs.m_data;
  }

  friend constexpr bool operator<(const iterator& t_rhs,
                                  const iterator& t_lhs) noexcept {
    return t_rhs.m_data < t_lhs.m_data;
  }

  friend constexpr bool operator>=(const iterator& t_rhs,
                                   const iterator& t_lhs) noexcept {
    return t_rhs.m_data >= t_lhs.m_data;
  }

  friend constexpr bool operator<=(const iterator& t_rhs,
                                   const iterator& t_lhs) noexcept {
    return t_rhs.m_data <= t_lhs.m_data;
  }

 protected:
  meta_pointer m_data;
};

template <typename It>
class reverse_iterator {
 public:
  reverse_iterator() : m_current(It()) {}

  constexpr explicit reverse_iterator(It t_it) noexcept : m_current(t_it) {}

  constexpr reverse_iterator& operator++() {
    --m_current;
    return *this;
  }

  constexpr reverse_iterator operator++(int) {
    auto tmp = *this;
    ++(*this);
    return tmp;
  }

  constexpr reverse_iterator& operator--() {
    ++m_current;
    return *this;
  }

  constexpr reverse_iterator operator--(int) {
    auto tmp = *this;
    --(*this);
    return tmp;
  }

  constexpr decltype(auto) operator*() const { return *m_current; }

  constexpr It base() const { return m_current; }

  friend constexpr bool operator==(const reverse_iterator& t_rhs,
                                   const reverse_iterator& t_lhs) noexcept {
    return t_rhs.m_data == t_lhs.m_data;
  }

  friend constexpr bool operator!=(const reverse_iterator& t_rhs,
                                   const reverse_iterator& t_lhs) noexcept {
    return t_rhs.base() != t_lhs.base();
  }

  friend constexpr bool operator>(const reverse_iterator& t_rhs,
                                  const reverse_iterator& t_lhs) noexcept {
    return t_rhs.base() > t_lhs.base();
  }

  friend constexpr bool operator<(const reverse_iterator& t_rhs,
                                  const reverse_iterator& t_lhs) noexcept {
    return t_rhs.base() < t_lhs.base();
  }

  friend constexpr bool operator>=(const reverse_iterator& t_rhs,
                                   const reverse_iterator& t_lhs) noexcept {
    return t_rhs.base() >= t_lhs.base();
  }

  friend constexpr bool operator<=(const reverse_iterator& t_rhs,
                                   const reverse_iterator& t_lhs) noexcept {
    return t_rhs.base() <= t_lhs.base();
  }

 protected:
  It m_current;
};
}  // namespace s21

#endif

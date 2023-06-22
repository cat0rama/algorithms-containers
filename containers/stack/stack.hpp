#ifndef STACK_HPP_
#define STACK_HPP_

#include <deque>

#include "../utils/defines.hpp"

namespace s21 {
template <typename T, typename Container = std::deque<T>>
class stack {
 public:
  using value_type = T;
  using size_type = typename Container::size_type;
  using difference_type = typename Container::difference_type;
  using const_reference = typename Container::const_reference;
  using reference = typename Container::reference;
  using iterator = typename Container::iterator;
  using const_iterator = typename Container::const_iterator;

 public:
  stack() = default;

  constexpr stack(const std::initializer_list<T>& t_list) {
    std::transform(
        t_list.begin(), t_list.end(), std::back_inserter(m_data),
        [](auto&& t_elem) { return std::forward<decltype(t_elem)>(t_elem); });
  }

  template <typename Y, typename = std::enable_if_t<
                            std::is_same_v<stack, std::remove_reference_t<Y>>>>
  constexpr explicit stack(Y&& t_stack) {
    initialize(std::forward<Y>(t_stack));
  }

  ~stack() = default;

 public:
  template <typename Y, typename = std::enable_if_t<
                            std::is_same_v<stack, std::remove_reference_t<Y>>>>
  stack& operator=(Y&& t_stack) {
    if (this != &t_stack) {
      initialize(std::forward<Y>(t_stack));
    }

    return *this;
  }

 public:
  template <typename L>
  void push(L&& t_elem) {
    m_data.push_back(std::forward<L>(t_elem));
  }

  void pop() {
    if (empty()) {
      throw std::underflow_error("stack is empty.\n");
    }
    m_data.pop_back();
  }

  reference top() {
    if (empty()) {
      throw std::underflow_error("stack is empty.\n");
    }

    return m_data.back();
  }

  const_reference top() const {
    if (empty()) {
      throw std::underflow_error("stack is empty.\n");
    }

    return m_data.back();
  }

  void swap(stack<T>& t_stack) { std::swap(m_data, t_stack.m_data); }

  [[nodiscard]] constexpr bool empty() const noexcept { return m_data.empty(); }

  [[nodiscard]] constexpr std::size_t size() const noexcept {
    return m_data.size();
  }

  [[nodiscard]] constexpr iterator begin() noexcept { return m_data.begin(); }

  [[nodiscard]] constexpr iterator end() noexcept { return m_data.end(); }

  [[nodiscard]] constexpr const_iterator begin() const noexcept {
    return m_data.begin();
  }

  [[nodiscard]] constexpr const_iterator end() const noexcept {
    return m_data.end();
  }

  [[nodiscard]] constexpr const_iterator cbegin() const noexcept {
    return m_data.cbegin();
  }

  [[nodiscard]] constexpr const_iterator cend() const noexcept {
    return m_data.cend();
  }

 protected:
  template <typename Y>
  void initialize(Y&& t_stack) noexcept(!std::is_lvalue_reference_v<Y>) {
    if constexpr (std::is_lvalue_reference_v<Y>) {
      m_data = t_stack.m_data;
    } else {
      m_data = std::exchange(t_stack.m_data, Container());
    }
  }

 private:
  Container m_data;
};
}  // namespace s21

#endif

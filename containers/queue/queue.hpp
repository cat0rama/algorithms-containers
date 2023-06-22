#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include <deque>

#include "../utils/defines.hpp"

namespace s21 {
template <typename T, typename Container = std::deque<T>>
class queue {
 public:
  using value_type = T;
  using size_type = typename Container::size_type;
  using difference_type = typename Container::difference_type;
  using const_reference = typename Container::const_reference;
  using reference = typename Container::reference;
  using iterator = typename Container::iterator;
  using const_iterator = typename Container::const_iterator;

 public:
  queue() = default;

  constexpr queue(const std::initializer_list<T>& t_list) {
    std::transform(
        t_list.begin(), t_list.end(), std::back_inserter(m_data),
        [](auto&& t_elem) { return std::forward<decltype(t_elem)>(t_elem); });
  }

  template <typename Y, typename = std::enable_if_t<
                            std::is_same_v<queue, std::remove_reference_t<Y>>>>
  constexpr explicit queue(Y&& t_queue) {
    initialize(std::forward<Y>(t_queue));
  }

  ~queue() = default;

 public:
  template <typename Y, typename = std::enable_if_t<
                            std::is_same_v<queue, std::remove_reference_t<Y>>>>
  queue& operator=(Y&& t_queue) {
    if (this != &t_queue) {
      initialize(std::forward<Y>(t_queue));
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
      throw std::underflow_error("queue is empty.\n");
    }
    m_data.pop_front();
  }

  [[nodiscard]] reference front() {
    if (empty()) {
      throw std::underflow_error("queue is empty.\n");
    }

    return m_data.front();
  }

  [[nodiscard]] const_reference front() const {
    if (empty()) {
      throw std::underflow_error("queue is empty.\n");
    }

    return m_data.front();
  }

  [[nodiscard]] reference back() {
    if (empty()) {
      throw std::underflow_error("queue is empty.\n");
    }

    return m_data.back();
  }

  [[nodiscard]] const_reference back() const {
    if (empty()) {
      throw std::underflow_error("queue is empty.\n");
    }

    return m_data.back();
  }

  void swap(queue<T>& t_queue) { std::swap(m_data, t_queue.m_data); }

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
  void initialize(Y&& t_queue) noexcept(!std::is_lvalue_reference_v<Y>) {
    if constexpr (std::is_lvalue_reference_v<Y>) {
      m_data = t_queue.m_data;
    } else {
      m_data = std::exchange(t_queue.m_data, Container());
    }
  }

 private:
  Container m_data;
};
}  // namespace s21

#endif

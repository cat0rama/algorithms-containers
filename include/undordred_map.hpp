#ifndef UNORDERED_MAP_HPP_
#define UNORDERED_MAP_HPP_

#include <algorithm>
#include <forward_list>
#include <memory>
#include <utility>

#include "defines.hpp"
#include "vector.hpp"

// дописать
namespace own {
template <typename Key, typename T, 
          typename Hash = std::hash<Key>,
          typename Equal = std::equal_to<Key>, 
          typename Allocator = std::allocator<T>>
class unordered_map {
public:
    using hasher = Hash;
    using allocator_type = Allocator;
    using size_type = typename Allocator::size_type;
    using difference_type = typename Allocator::difference_type;
    using reference = typename Allocator::reference;
    using const_reference = typename Allocator::const_reference;
    using pointer = typename Allocator::pointer;
    using const_pointer = typename Allocator::const_pointer;
    using value_type = std::pair<const Key, T>;

  public:
    unordered_map(std::size_t t_capacity = DEFAULT_TABLE_SIZE): 
    m_capacity(t_capacity), m_size(0) {
        m_table.resize(m_capacity);
    }

    ~unordered_map() = default;

  public:
    template <typename U> std::pair<int, bool> insert(U&& t_pair) { 
        auto index = get_index(t_pair.first);

        if (!m_table[index].empty()) {
            return {0, false};
        }

        m_table[index].push_front(std::forward<U>(t_pair));
        m_size++;
        return {1, true};
    }

    // возвращает индекс по модулю размера от хеша
    [[nodiscard]] constexpr std::size_t get_index(const T& t_key) const noexcept {
        return hash(t_key) % m_capacity;
    }

  public:
      T& operator[](const T& t_key) {
          auto &elem = m_table[get_index(t_key)];
          if (elem.empty()) {
            insert(value_type(t_key, T()));
          }

          return elem.front().second;
      }

      const T& operator[](const T& t_key) const {
          auto& elem = m_table[get_index(t_key)];
          if (elem.empty()) {
            insert(value_type(t_key, T()));
          }

          return elem.front().second;
      }
  private:
    // обертка над std::hash
    [[nodiscard]] constexpr std::size_t hash(const T& t_key) const noexcept {
        return std::hash<T>()(t_key);
    }

  private:
    std::vector<std::forward_list<value_type>> m_table;
    std::size_t m_capacity;
    std::size_t m_size;
};
} // namespace own

#endif

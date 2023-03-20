#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <algorithm>
#include <iterator>
#include <memory>

#include "defines.hpp"
#include "iterator.hpp"

// https://en.cppreference.com/w/cpp/container/vector
// дописать
namespace own {
using namespace defines;
template <class T, class Allocator = std::allocator<T>> class vector final {
  public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = typename Allocator::size_type;
    using difference_type = typename Allocator::difference_type;
    using reference = typename Allocator::reference;
    using const_reference = typename Allocator::const_reference;
    using pointer = typename Allocator::pointer;
    using const_pointer = typename Allocator::const_pointer;

  public:
    using iterator = iterator_wrapper<T, NON_CONST>;
    using const_iterator = iterator_wrapper<T, CONST>;
    using reverse_iterator = own::reverse_iterator<iterator>;
    using const_reverse_iterator = own::reverse_iterator<const_iterator>;

  public:
    constexpr vector() : m_capacity(DEFAULT_CAPACITY), m_size(0) {
        m_data = m_allocator.allocate(m_capacity);
    }

    explicit constexpr vector(std::size_t t_capacity) : m_size(0), m_capacity(t_capacity * FACTOR) {
        m_data = m_allocator.allocate(m_capacity);
    }

    constexpr vector(std::size_t t_size, const_reference t_element)
        : m_size(t_size), m_capacity(t_size * FACTOR) {
        m_data = m_allocator.allocate(m_capacity);
        std::fill(m_data, m_data + m_capacity, t_element);
    }

    template <typename InputIt>
    constexpr vector(InputIt t_first, InputIt t_last): vector(std::distance(t_first, t_last)) {
        std::transform(t_first, t_last, std::back_inserter(*this), [](auto&& t_elem){return t_elem;});
    }

    template <typename CC,
              typename = std::enable_if_t<std::is_same_v<vector, std::remove_reference_t<CC>>>>
    constexpr vector(CC&& t_vector) {
        Initialize(std::forward<CC>(t_vector));
    }

    ~vector() { m_allocator.deallocate(m_data, m_capacity); }

  public:
    template <typename TT,
              typename = std::enable_if_t<std::is_same_v<vector, std::remove_reference_t<TT>>>>
    constexpr vector& operator=(TT&& t_vector) {
        if (this != &t_vector) {
            m_allocator.deallocate(m_data, m_size);
            Initialize(std::forward<TT>(t_vector));
        }
        return *this;
    }

  private:
    template <typename Iter> void safe_cpy(Iter t_from, Iter t_to, std::size_t t_size) {
        if (t_from == nullptr) {
            fprintf(stderr, "invalid pointer provided.\n");
            return;
        }

        try {
            std::uninitialized_copy(t_from, t_from + t_size, t_to);
        } catch (...) {
            if (t_to) {
                m_allocator.deallocate(t_to, t_size); // delete mem and call destructor
            }
            THROW_FURTHER;
        }
    }

    template <typename Y>
    constexpr void Initialize(Y&& t_vector) noexcept(!std::is_lvalue_reference_v<Y>) {
        if constexpr (std::is_lvalue_reference_v<Y>) {
            m_size = t_vector.m_size;
            m_capacity = t_vector.m_capacity;
            m_allocator = t_vector.m_allocator;
            m_data = m_allocator.allocate(m_capacity);
            safe_cpy(t_vector.m_data, m_data, m_size);
        } else {
            m_size = std::exchange(t_vector.m_size, 0);
            m_capacity = std::exchange(t_vector.m_capacity, 0);
            m_data = std::exchange(t_vector.m_data, nullptr);
            std::swap(m_allocator, t_vector.m_allocator);
        }
    }

  public:
    void fill(const_reference t_value) { std::fill(m_data, m_data + m_size, t_value); }

    pointer data() const noexcept { return m_data; }

    iterator begin() const noexcept { return iterator(m_data); }

    iterator end() const noexcept { return iterator(m_data + m_size); }

    const_iterator cbegin() const noexcept { return const_iterator(m_data); }

    const_iterator cend() const noexcept { return const_iterator(m_data + m_size); }

    reverse_iterator rbegin() const noexcept { return reverse_iterator(m_data + m_size); }

    reverse_iterator rend() const noexcept { return reverse_iterator(m_data); }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(m_data + m_size);
    }

    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(m_data); }

    template <typename... Args> reference emplace_back(Args&&... t_args) {
        if (m_capacity == m_size) {
            reserve(m_size * FACTOR);
        }
        // don't use allocator.construct for practice with placement new.
        return *new (m_data + m_size++) T(std::forward<Args>(t_args)...);
    }

    template <typename PP> void push_back(PP&& t_elem) {
        if (m_capacity == m_size) {
            reserve(m_size * FACTOR);
        }
        new (m_data + m_size++) T(std::forward<PP>(t_elem));
    }

    void pop_back() {
        if (m_size == 0) {
            throw std::underflow_error("vector is empty.\n");
        }
        m_size--;
        (m_data + m_size)->~T();
    }

    void resize(std::size_t t_size) {
        if (t_size > m_capacity) {
            reserve(t_size);
        }
        m_size = t_size;
    }

    void reserve(std::size_t t_size) {
        if (m_capacity >= t_size) {
            return;
        }
        auto new_arr =
            m_allocator.allocate(t_size); // allocate memory without call default constructor

        safe_cpy(m_data, new_arr, m_size);
        m_allocator.deallocate(m_data, m_capacity);

        m_data = std::exchange(new_arr, nullptr);
        m_capacity = t_size;
    }

    constexpr std::size_t size() const noexcept { return m_size; }

    constexpr std::size_t capacity() const noexcept { return m_capacity; }

  private:
    pointer m_data;
    std::size_t m_size;
    std::size_t m_capacity;
    Allocator m_allocator;
};

// deduction hint для того чтобы вектор вывел тип от итератора
template <typename InputIt>
vector(InputIt t_first, InputIt t_last) -> vector<typename std::iterator_traits<InputIt>::value_type>;

} // namespace own

#endif

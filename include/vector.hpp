#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <algorithm>
#include <iterator>
#include <limits>
#include <memory>

#include "defines.hpp"
#include "iterator.hpp"
#include "traits.hpp"

// https://en.cppreference.com/w/cpp/container/vector
// ДОПИСАТЬ!
namespace own {
//пока что убрал final(для тестов), потом надо будет вернуть на место
using namespace defines;
template <typename T, typename Allocator = std::allocator<T>> class vector {
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
        fill(t_element);
    }

    constexpr vector(const std::initializer_list<T>& t_list)
        : vector(std::distance(t_list.begin(), t_list.end())) {
        std::transform(t_list.begin(), t_list.end(), std::back_inserter(*this),
                       [](auto&& t_elem) { return std::forward<decltype(t_elem)>(t_elem); });
    }

    // проверяю тип на итератор при помощи неявного преобразования InputIt к категории итератора.
    template <typename InputIt, typename = std::enable_if_t<std::is_convertible<
                                    typename std::iterator_traits<InputIt>::iterator_category,
                                    std::input_iterator_tag>::value>>
    constexpr vector(InputIt t_first, InputIt t_last) : vector(std::distance(t_first, t_last)) {
        std::transform(t_first, t_last, std::back_inserter(*this),
                       // Если не форвардить обьект, то будет вызываться лишний консутрктор
                       // копирования https://godbolt.org/z/9Kj48r5ab
                       [](auto&& t_elem) { return std::forward<decltype(t_elem)>(t_elem); });
    }

    template <typename CC,
              typename = std::enable_if_t<std::is_same_v<vector, std::remove_reference_t<CC>>>>
    constexpr explicit vector(CC&& t_vector) {
        initialize(std::forward<CC>(t_vector));
    }

    ~vector() { m_allocator.deallocate(m_data, m_capacity); }

  public:
    template <typename TT,
              typename = std::enable_if_t<std::is_same_v<vector, std::remove_reference_t<TT>>>>
    constexpr vector& operator=(TT&& t_vector) {
        if (this != &t_vector) {
            m_allocator.deallocate(m_data, m_size);
            initialize(std::forward<TT>(t_vector));
        }

        return *this;
    }

    const_reference operator[](size_type t_i) const {
        if (t_i >= m_size) {
            throw std::out_of_range("index out of range.\n");
        }

        return m_data[t_i];
    }

    reference operator[](size_type t_i) {
        if (t_i >= m_size) {
            throw std::out_of_range("index out of range.\n");
        }

        return m_data[t_i];
    }

    MODIFIRE : template <typename Iter> void safe_cpy(Iter t_from, Iter t_to, std::size_t t_size) {
        if (!t_from || !t_to) {
            throw std::invalid_argument("invalid iterator provided.\n");
        }

        try {
            std::uninitialized_copy(t_from, t_from + t_size, t_to);
        } catch (...) {
            // удаляю память через deallocate, который вызовет деструкторы у обьектов
            m_allocator.deallocate(t_to, t_size);
            THROW_FURTHER;
        }
    }

    template <typename Y>
    constexpr void initialize(Y&& t_vector) noexcept(!std::is_lvalue_reference_v<Y>) {
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
    constexpr const T& at(std::size_t t_i) const {
        if (t_i >= m_size) {
            throw std::out_of_range("index out of range.\n");
        }

        return m_data[t_i];
    }

    constexpr T& at(std::size_t t_i) {
        if (t_i >= m_size) {
            throw std::out_of_range("index out of range.\n");
        }

        return m_data[t_i];
    }

    constexpr void fill(const_reference t_value) { std::fill(begin(), end(), t_value); }

    constexpr pointer data() noexcept { return m_data; }

    constexpr const_pointer data() const noexcept { return m_data; }

    constexpr iterator begin() const noexcept { return iterator(m_data); }

    constexpr iterator end() const noexcept { return iterator(m_data + m_size); }

    constexpr const_iterator cbegin() const noexcept { return const_iterator(m_data); }

    constexpr const_iterator cend() const noexcept { return const_iterator(m_data + m_size); }

    constexpr reverse_iterator rbegin() const noexcept { return reverse_iterator(m_data + m_size); }

    constexpr reverse_iterator rend() const noexcept { return reverse_iterator(m_data); }

    constexpr const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(m_data + m_size);
    }

    constexpr const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(m_data);
    }

    [[nodiscard]] constexpr reference back() { return m_data[m_size - 1]; }

    [[nodiscard]] constexpr reference front() { return m_data[0]; }

    [[nodiscard]] constexpr const_reference back() const { return m_data[m_size - 1]; }

    [[nodiscard]] constexpr const_reference front() const { return m_data[0]; }

    [[nodiscard]] constexpr std::size_t size() const noexcept { return m_size; }

    [[nodiscard]] constexpr std::size_t capacity() const noexcept { return m_capacity; }

    [[nodiscard]] constexpr bool empty() const noexcept { return begin() == end(); }

    [[nodiscard]] constexpr size_t max_size() const noexcept {
        // тк аллокатор выделяет память, надо брать значения у него
        return m_allocator.max_size();
        /* вычисляется по формуле: (2^SYS_BITS)/SIZE_TYPE - 1 где:
         * SYS_BITS - это битность OC
         * SIZE_TYPE - это размер типа, размером с который выделяется память
         */
    }

    template <typename... Args> constexpr 
    reference emplace_back(Args&&... t_args) {
        if (m_capacity == m_size) {
            reserve(m_size * FACTOR);
        }
        // не использую allocator.construct для практики с new placement
        return *new (m_data + m_size++) T(std::forward<Args>(t_args)...);
    }

    template <typename PP> void push_back(PP&& t_elem) {
        if (m_capacity == m_size) {
            reserve(m_size * FACTOR);
        }
        new (m_data + m_size++) T(std::forward<PP>(t_elem));
    }

    constexpr void pop_back() {
        if (m_size == 0) {
            throw std::underflow_error("vector is empty.\n");
        }
        (m_data + --m_size)->~T();
    }

    constexpr void resize(std::size_t t_size) {
        if (t_size > m_capacity) {
            reserve(t_size);
        }
        m_size = t_size;
    }

    constexpr void reserve(std::size_t t_size) {
        auto new_arr = m_allocator.allocate(t_size);
        safe_cpy(m_data, new_arr, m_size);
        m_allocator.deallocate(m_data, m_capacity);
        m_data = std::exchange(new_arr, nullptr);
        m_capacity = t_size;
    }

    constexpr void shrink_to_fit() {
        if (m_size == 0) {
            throw std::runtime_error("size is equal to zero.\n");
        }

        reserve(m_size);
    }

    template <typename II> iterator insert(iterator t_pos, II&& t_elem) {
        auto pos = std::distance(begin(), t_pos);
        if (pos > m_size) {
            throw std::out_of_range("iterator position are out of range.\n");
        }

        const auto new_size = m_size + 1;
        if (new_size > m_capacity) {
            reserve(new_size * FACTOR);
        }

        for (auto i = m_size; i > pos; --i) {
            m_data[i] = std::move(m_data[i - 1]);
        };
        new (m_data + pos) T(std::forward<II>(t_elem));
        m_size++;
        return iterator(m_data + pos);
    }

    void erase(iterator t_pos) noexcept {
        auto pos = std::distance(begin(), t_pos);
        if (pos > m_size) {
            throw std::out_of_range("iterator position are out of range.\n");
        }

        for (auto i = pos; i < m_size - 1; i++) {
            m_data[i] = std::move(m_data[i + 1]);
        }
        m_size--;
    }

    template <typename... Args>
    iterator emplace(const_iterator t_pos, Args&&... t_args) {
        auto pos = std::distance(cbegin(), t_pos);
        if (pos > m_size) {
            throw std::out_of_range("iterator position are out of range.\n");
        }
        
        for (auto i = m_size; i > pos; --i) {
            m_data[i] = std::move(m_data[i - 1]);
        };
        new (m_data + pos) T(std::forward<Args>(t_args)...);
        m_size++;
        return iterator(m_data + pos);
    }

    constexpr void clear() noexcept {
        // вызывает деструкторы у всех обьектов в диапозоне
        std::destroy(begin(), end());
        m_size = 0;
    }

    MODIFIRE : pointer m_data;
    std::size_t m_size;
    std::size_t m_capacity;
    Allocator m_allocator;
};

// deduction hint для того чтобы вектор вывел тип от итератора через трейты
template <typename InputIt>
vector(InputIt t_first, InputIt t_last)
    -> vector<typename std::iterator_traits<InputIt>::value_type>;

} // namespace own

#endif

#include <algorithm>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>
#include <memory>

#include "defines.hpp"
#include "iterator.hpp"

// https://en.cppreference.com/w/cpp/container/vector

namespace own {
using namespace defines;
template <class T, class Allocator = std::allocator<T>>
class vector final {
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
    template <bool IsIterConst> struct iterator_wrapper {
      private:
        using iterator = iterator_wrapper;

      public:
        using cdifference_type = const difference_type;
        using iterator_category = std::random_access_iterator_tag;
        using meta_pointer = std::conditional_t<IsIterConst, const_pointer, pointer>;
        using meta_reference = std::conditional_t<IsIterConst, const_reference, reference>;

      public:
        constexpr iterator_wrapper() noexcept : m_data(nullptr) {}

        constexpr iterator_wrapper(pointer t_ptr) noexcept : m_data(t_ptr) {}

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

        constexpr meta_reference operator[](cdifference_type t_index) const noexcept {
            return m_data[t_index];
        }

        constexpr iterator& operator+=(cdifference_type t_rhs) const noexcept {
            m_data += t_rhs;
            return *this;
        }

        constexpr iterator& operator-=(cdifference_type t_rhs) const noexcept {
            m_data -= t_rhs;
            return *this;
        }

        constexpr iterator operator+(cdifference_type t_rhs) const noexcept {
            return iterator(m_data + t_rhs);
        }

        constexpr iterator operator-(cdifference_type t_rhs) const noexcept {
            return iterator(m_data - t_rhs);
        }

        friend constexpr iterator operator+(cdifference_type t_lhs,
                                            const iterator& t_rhs) noexcept {
            return iterator(t_lhs + t_rhs.m_data);
        }

        friend constexpr iterator operator-(cdifference_type t_lhs,
                                            const iterator& t_rhs) noexcept {
            return iterator(t_lhs - t_rhs.m_data);
        }

        friend constexpr bool operator==(const iterator& t_rhs, const iterator& t_lhs) noexcept {
            return t_rhs.m_data == t_lhs.m_data;
        }

        friend constexpr bool operator!=(const iterator& t_rhs, const iterator& t_lhs) noexcept {
            return t_rhs.m_data != t_lhs.m_data;
        }

        friend constexpr bool operator>(const iterator& t_rhs, const iterator& t_lhs) noexcept {
            return t_rhs.m_data > t_lhs.m_data;
        }

        friend constexpr bool operator<(const iterator& t_rhs, const iterator& t_lhs) noexcept {
            return t_rhs.m_data < t_lhs.m_data;
        }

        friend constexpr bool operator>=(const iterator& t_rhs, const iterator& t_lhs) noexcept {
            return t_rhs.m_data >= t_lhs.m_data;
        }

        friend constexpr bool operator<=(const iterator& t_rhs, const iterator& t_lhs) noexcept {
            return t_rhs.m_data <= t_lhs.m_data;
        }

      private:
        meta_pointer m_data;
    };

  public:
    using iterator = iterator_wrapper<NON_CONST>;
    using const_iterator = iterator_wrapper<CONST>;
    using reverse_iterator = own::reverse_iterator<iterator>;
    using const_reverse_iterator = own::reverse_iterator<const_iterator>;

  public:
    constexpr vector() : m_capacity(DEFAULT_CAPACITY), m_size(CNULL) {
        m_data = m_allocator.allocate(m_capacity);
    }

    explicit constexpr vector(std::size_t t_capacity) : m_size(CNULL), m_capacity(t_capacity * FACTOR) {
        m_data = m_allocator.allocate(m_capacity);
    }

    constexpr vector(std::size_t t_size, const_reference t_element)
        : m_size(t_size), m_capacity(t_size * FACTOR) {
        m_data = m_allocator.allocate(m_capacity);
        std::fill(m_data, m_data + m_capacity, t_element);
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
    template <typename Y>
    constexpr void Initialize(Y&& t_vector) noexcept(!std::is_lvalue_reference_v<Y>) {
        if constexpr (std::is_lvalue_reference_v<Y>) {
            m_size = t_vector.m_size;
            m_capacity = t_vector.m_capacity;
            m_allocator = t_vector.m_allocator;
            m_data = m_allocator.allocate(m_capacity);
            std::copy(t_vector.m_data, t_vector.m_data + m_size, m_data);
        } else {
            m_size = std::exchange(t_vector.m_size, CNULL);
            m_capacity = std::exchange(t_vector.m_capacity, CNULL);
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

    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(m_data + m_size); }

    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(m_data); }

    template<typename ...Args>
    reference emplace_back(Args&&... t_args) {
        if  (m_capacity == m_size) {
            reserve(m_size * FACTOR);
        }
        // don't use allocator.construct for practice with placement new.
        return *new (m_data + m_size++) T(std::forward<Args>(t_args)...);
    }

    template<typename PP>
    void push_back(PP&& t_elem) {
        if  (m_capacity == m_size) {
            reserve(m_size * FACTOR);
        }
        new (m_data + m_size++) T(std::forward<PP>(t_elem));
    }

    void pop_back() noexcept {
        m_size--;
        (m_data + m_size)->~T();
    }

    void resize(std::size_t t_size, const_reference = T()) {
        if (t_size > m_capacity) {
            reserve(t_size);
        }
        m_size = t_size;
    }

    void reserve(std::size_t t_size) {
        if (m_capacity >= t_size) {
            return;
        }

        auto new_arr = m_allocator.allocate(t_size);  // allocate memory without call default constructor

        try {
            std::uninitialized_move(m_data, m_data + m_size, new_arr);
        }  catch (...) {
            m_allocator.deallocate(new_arr, t_size);    // delete mem and call destructor
            THROW_FURTHER;
        }

        m_allocator.deallocate(m_data, m_capacity);
        m_data = std::exchange(new_arr, nullptr);
        m_capacity = t_size;
    }

    constexpr std::size_t size() const noexcept {
        return m_size;
    }

    constexpr std::size_t capacity() const noexcept {
        return m_capacity;
    }

  private:
    pointer m_data;
    std::size_t m_size;
    std::size_t m_capacity;
    Allocator m_allocator;
};
} // namespace own

using namespace own;

class Test {
public:
    Test(int _a, std::string): a(_a) {
        a = _a;
    }


    int getA() {
        return a;
    }

    ~Test() {
    }
public:
    int *ptr;
    int a;
};

int main() {
    // Компайл тайм тестики
    static_assert(std::is_same_v<vector<int>::const_pointer, const int*>);
    static_assert(std::is_same_v<vector<int>::const_iterator::meta_pointer, const int*>);
    static_assert(std::is_same_v<vector<int>::iterator::meta_reference, int&>);

    //    vector<double> d(5);

    //    d.Fill(4);

    //    vector<double> l(d);

    //    d = l;

    //    vector<double> f(200, 5);

    //    l = vector<double>(10) = f;

    //    std::vector<int> k;

    //    auto c = k.begin();
    //    c = std::move(k.end());

    //    auto n = l.begin();
    //    auto m = l.end();
    //    n = m;

    //    vector<int> i(10, 4);

    //    i.data()[10] = 9;

//    vector<int> a(10);
//    a = vector<int>(23);

//    vector<int> l(20);

//    a = l;
//    a = vector<int>(5, 3);
//    a.fill(10);

//    std::for_each(a.begin(), a.end(), [](int a) { std::cout << a; });


    vector<Test> a(10);

    a.emplace_back(3, "hello");
    a.emplace_back(10, "lol");

    std::for_each(a.begin(), a.end(), [](auto& a) { std::cout << a.a << ' '; });
}

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>

#include "defines.hpp"
#include "iterator.hpp"

// https://en.cppreference.com/w/cpp/container/vector
// Сборная солянка из моего и STL кода.
// Спасибо Мещерину за лекции :)
// Сделать тесты(Gtest)

namespace own 
{
    template <class T, class Allocator = std::allocator<T>>
    class vector {
    public:
        using value_type = T;
        using allocator_type = Allocator;
        using size_type = typename Allocator::size_type;
        using difference_type = typename Allocator::difference_type;
        using reference = typename Allocator::reference;
        using const_reference =  typename Allocator::const_reference;
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

            iterator_wrapper(pointer t_ptr) noexcept : m_data(t_ptr) {}

            iterator_wrapper(const iterator_wrapper& t_iter) noexcept : m_data(t_iter.m_data) {}
        public:

        private:
            meta_pointer m_data;
    };
    public:
        using iterator = iterator_wrapper<NON_CONST>;
        using const_iterator = iterator_wrapper<CONST>;
        using reverse_iterator = std::reverse_iterator<iterator>; // Пока что stdшный итератор
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    public:
        constexpr vector(): m_capacity(DEFAULT_CAPACITY), m_size(CNULL) {
            m_data = m_allocator.allocate(m_capacity);
        }

        constexpr vector(std::size_t t_size): m_size(t_size), m_capacity(t_size * FACTOR) {
            m_data = m_allocator.allocate(m_capacity);
        }

        constexpr vector(std::size_t t_size, const T& t_element): m_size(t_size), m_capacity(t_size * FACTOR) {
            m_data = m_allocator.allocate(m_capacity);
            std::fill(m_data, m_data + m_capacity, t_element);
        }

        template <typename InputIter>
        constexpr vector(InputIter t_first, InputIter t_last, const Allocator& = Allocator()):
                         m_capacity(DEFAULT_CAPACITY * FACTOR) {
            m_data = m_allocator.allocate(m_capacity);
            // vector_fill();
        }

        ~vector() {
            m_allocator.deallocate(m_data, m_capacity);
        }

        vector(const vector& t_vector) {
            Initialize(t_vector);
        }

        vector(vector&& t_vector) noexcept {
            Initialize(std::move(t_vector));
        }
    public:
        vector& operator=(const vector& t_vector) {
            if (this != &t_vector) {
                m_allocator.deallocate(m_data, m_size);
                Initialize(t_vector);
            }
            return *this;
        }

        vector& operator=(vector&& t_vector) {
            if (this != &t_vector) {
                m_allocator.deallocate(m_data, m_size);
                Initialize(std::move(t_vector));
            }

            return *this;
        }
    public:
        void Fill(const T& value) {
            for (std::size_t i = 0; i < m_size; i++) {
                m_data[i] = value;
            }
        }

        void Out() {
            for (std::size_t i = 0; i < m_size; i++) {
                std::cout << m_data[i];
            }
        }
    private:
        template <typename Y>
        void Initialize(Y&& t_vector) noexcept(std::is_rvalue_reference_v<decltype(t_vector)>) {
            if constexpr (std::is_rvalue_reference_v<decltype(t_vector)>) {
                m_size = std::exchange(t_vector.m_size, 0);
                m_capacity = std::exchange(t_vector.m_capacity, 0);
                m_data = std::exchange(t_vector.m_data, nullptr);
                std::swap(m_allocator, t_vector.m_allocator);
            } else {
                m_size = t_vector.m_size;
                m_capacity = t_vector.m_capacity;
                m_allocator = t_vector.m_allocator;
                m_data = m_allocator.allocate(m_capacity);
                std::copy(t_vector.m_data, t_vector.m_data + m_capacity, m_data);
            }
        }
    private:
        pointer m_data;
        std::size_t m_size;
        std::size_t m_capacity;
        Allocator m_allocator;
    };
}

using namespace own;

int main() {
    // Компайл тайм тестики
    static_assert(std::is_same_v<vector<int>::const_pointer, const int*>);
    static_assert(std::is_same_v<vector<int>::const_iterator::meta_pointer, const int*>);
    static_assert(std::is_same_v<vector<int>::iterator::meta_reference, int&>);

    vector<double> d(5);

    d.Fill(4);

    vector<double> l(d);

    d = l;

    vector<double> f(200, 5);

    l = vector<double>(10) = f;

    l.Out();
}

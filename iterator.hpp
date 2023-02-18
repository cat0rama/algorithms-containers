#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

// Школьные проекты заставляют меня имитировать стандартную библиотеку...

namespace own {
    // struct random_access_iterator_tag {};

    // template <class T>
    // struct vector_iter_proto {
    //     using pointer = T*;
    //     using reference = T&;
    //     using const_pointer = const pointer;
    //     using const_reference = const reference;
    //     using iterator_category = random_access_iterator_tag;
    //     using difference_type = std::ptrdiff_t;
    // };

    // template <typename Iter>
    // struct iterator_traits {
    //     using pointer = typename Iter::pointer;
    //     using reference = typename Iter::reference;
    //     using const_pointer = const pointer;
    //     using const_reference = const reference;
    //     using iterator_category = typename Iter::iterator_category;
    //     using difference_type = typename Iter::difference_type;
    // };

    template <typename Iter>
    struct reverse_iterator {
    public:

    private:
        Iter m_iterator;
    };
}

#endif
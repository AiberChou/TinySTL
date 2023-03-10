#pragma once

#include <cstddef>

namespace TinySTL{
    
    // for tag type
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag : public input_iterator_tag{}; //if there is no matching function, call function matchs "input_iterator_tag" 
    struct bidirectional_iterator_tag : public forward_iterator_tag{};
    struct random_access_iterator_tag : public bidirectional_iterator_tag{};
    

    template <class Category, class T, class Distance = ptrdiff_t, 
              class Pointer = T*, class Reference = T& >
    struct iterator
    {
        typedef Category    iterator_category;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
    };
    

    // traits
    template <class Iterator>
    struct iterator_traits{
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
    };

    // partial specialization for native pointer 
    template <class T>
    struct iterator_traits<T*>{
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };
    
    // partial specialization for const native pointer 
    template <class T>
    struct iterator_traits<const T*>{
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
    };
    

    template <class Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator& It){
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return category();
    }

    template <class Iterator>
    inline typename iterator_traits<Iterator>::difference_type*
    distance_type(const Iterator& It){
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
    }
    
    template <class Iterator>
    inline typename iterator_traits<Iterator>::value_type* 
    value_type(const Iterator& It){
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }
}
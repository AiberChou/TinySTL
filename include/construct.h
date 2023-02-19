#pragma once

#include <new>  // for placement new
#include "iterator.h"
#include "traits.h"


namespace TinySTL{
    
    template <class T1, class T2>
    inline void construct(T1* p, const T2& value){
        // Call T1::T1(value) to initialize, with the address starting at p
        new(p) T1(value);
    }

    template<class T>
    inline void destroy(T* pointer){
        pointer->~T();
    }

    // if "value_type" has non-trivial destructor, that is "value_type" has 
    // its own defined destructor, we need to call this function. Otherwise,
    // the destructor is trivial, calls it many times will influence speed
    template<class ForwardIterator>
    inline void __destroy_aux(ForwardIterator first,ForwardIterator last,_false_type trait){
        for(;first<last;++first){
            destroy(&*first);
        }
    }

    template<class ForwardIterator>
    inline void __destroy_aux(ForwardIterator first,ForwardIterator last,_true_type trait){

    }

    template<class ForwardIterator, class T>
    inline void __destroy(ForwardIterator first, ForwardIterator last, T* trait){
        typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
        __destroy_aux(first,last,trivial_destructor());
    }

    template<class ForwardIterator>
    inline void destroy(ForwardIterator first, ForwardIterator last){
        __destroy(first, last, value_type(first)); 
    }
}


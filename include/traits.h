#pragma once

namespace TinySTL{

    struct _true_type{};
    struct _false_type{};
    
    template<class T>
    struct __type_traits{
        typedef _false_type has_trivial_default_constructor;
        typedef _false_type has_trivial_copy_constructor;
        typedef _false_type has_trivial_assignment_operator; 
        typedef _false_type has_trivial_destructor;
        typedef _false_type is_POD_type;
    };

    template<class I>
    struct Iter_traits{
        typedef typename I::iterator_category   iterator_category;
        typedef typename I::value_type          value_type;
        typedef typename I::difference_type     difference_type;
        typedef typename I::pointer             pointer;
        typedef typename I::reference           reference;
    };
    
}
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

    template<>
    struct __type_traits<char>{
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    
    template<>
    struct __type_traits<signed char>{
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    
    template<>
    struct __type_traits<unsigned char>{
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct __type_traits<short>{
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct __type_traits<unsigned short>{
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct __type_traits<int>{
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct __type_traits<unsigned int>{
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct __type_traits<long>{
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct __type_traits<unsigned long>{
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct __type_traits<float>{
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct __type_traits<double>{
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct __type_traits<long double>{
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    // for native pointer
    template<class T>
    struct __type_traits<T*>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator; 
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
}
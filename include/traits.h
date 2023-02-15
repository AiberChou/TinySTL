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
}
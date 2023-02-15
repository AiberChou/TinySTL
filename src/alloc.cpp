#include <cstdlib>
#include "../include/alloc.h"

namespace TinySTL{
    
    // static declare in class, initialize out of class
    template <int inst>
    void (* __malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = nullptr;

    template <int inst>
    void* __malloc_alloc_template<inst>::oom_malloc(size_t n){
        void (*my_malloc_handler)();
        void* result;

        for(;;){
            my_malloc_handler = __malloc_alloc_oom_handler;
            if(my_malloc_handler == nullptr) {
                cerr<<"out of memory"<<endl;
                exit(1);
            }
            (*my_malloc_handler)(); // handle for out of memory
            result = malloc(n);
            if(result) return result;
        }
    }

    template <int inst>
    void* __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n){
        void (*my_malloc_handler)();
        void* result;

        for(;;){
            my_malloc_handler = __malloc_alloc_oom_handler;
            if(my_malloc_handler == nullptr) {
                cerr<<"out of memory"<<endl;
                exit(1);
            }
            (*my_malloc_handler)(); // handle for out of memory
            result = realloc(p,n);
            if(result) return result;
        }
    }

    typedef __malloc_alloc_template<0> malloc_alloc;
}
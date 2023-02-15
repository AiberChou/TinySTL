#pragma once

#include <new>
#include <cstdlib>
#include "iostream.h"


namespace TinySTL{
    
    // First-level allocator, "inst" is for different specialization, 
    // such as debug using inst = 0, while release using inst = 1
    template <int inst>
    class __malloc_alloc_template{
    private:
        typedef void(*ptr)();
        static void *oom_malloc(size_t n);
        static void *oom_realloc(void* p, size_t n);
        static void (* __malloc_alloc_oom_handler)();
    public:
        static void* allocate(size_t n){
            void* result = malloc(n); //using malloc to get storage and free to release.
            // if fail to get storage using oom_malloc
            if (result == nullptr) result = oom_malloc(n);
            return result;
        }

        static void deallocate(void* p, size_t n){
            free(p);
        }

        static void* reallocate(void* p, size_t old_sz, size_t new_sz){
            void *result = realloc(p, new_sz);
            if (result == nullptr) result = oom_realloc(p, new_sz);
            return result;
        }

        // analysis please see "https://www.cnblogs.com/dyhui/p/4390836.html"
        // static void (* set_malloc_handler(void (*f)()))()
        // set_malloc_handler first combine with "()" that is to say, 
        // set_malloc _handler is a function, which parameter is a function 
        // pointer, and then combine with "*", that means it returns a void
        // pointer, last combine with "()", so it returns a void func pointer
        static ptr set_malloc_handler(ptr){
            void (*old)() = __malloc_alloc_oom_handler;
            __malloc_alloc_oom_handler = f;
            return (old);
        }
    };
}
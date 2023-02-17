#pragma once

#include <new>
#include <cstdlib>
#include "iostream.h"


namespace TinySTL{
    
    class __malloc_alloc{
    private:
        typedef void(*ptr)();
        static void *oom_malloc(size_t n);
        static void *oom_realloc(void* p, size_t n);
        static void (* __malloc_alloc_oom_handler)(); // declare in class
    public:

        static void* allocate(size_t n){
            void* result = malloc(n); // using malloc to get storage and free to release.
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
        static ptr set_malloc_handler(ptr f){
            void (*old)() = __malloc_alloc_oom_handler;
            __malloc_alloc_oom_handler = f;
            return (old);
        }
    };


    class __default_alloc{
    private:
        enum EAlign{ ALIGN=8}; // up-regulated boundary
        enum EMaxBytes{ MAXBYTES=128}; // upper boundary
        enum ENFreeLists{ NFREELISTS= (EMaxBytes::MAXBYTES / EAlign::ALIGN)}; // number of free-lists
        
        // round up bytes to multiple of 8         
        static size_t round_up(size_t bytes){
            return ((bytes) + EAlign::ALIGN -1) & ~(EAlign::ALIGN - 1);
        }

        union obj{
            union obj* free_list_link;
            char client_data[1];  
        };

        // chunk allocation state, only changed in function chunk_alloc
        static char* start_free; // start of memory pool
        static char* end_free;  // end of memory pool
        static size_t heap_size;

        // "volatile" prevents from optimizing by compiler, if not, data may be load to
        // register, result in thread lock invalid. use volatile, ensure thread safe
        static obj* volatile free_list[ENFreeLists::NFREELISTS];
        
        static size_t freelist_index(size_t bytes){
            return (((bytes) + EAlign::ALIGN -1)/EAlign::ALIGN - 1);
        }

        // refill freelist while freelist have no memory left
        static void* refill(size_t n);
        // get memory chunk for freelist to allocate, chunk number is nobjs 
        static char* chunk_alloc(size_t size, int& nobjs);

    public:
        static void* allocate(size_t n);
        static void deallocate(void* p, size_t n);
        static void* reallocate(void* p, size_t n);
    };

    typedef __default_alloc default_alloc;

    template<class T, class Alloc>
    class simple_alloc{
    public:
        static T* allocate(size_t n){
            return n == 0 ? nullptr : (T*)Alloc::allocate(n*sizeof(T));
        }

        static T* allocate(void){
            return (T*)Alloc::allocate(sizeof(T));
        }

        static void deallocate(T* p,size_t n){
            if(n!=0) Alloc::deallocate(p,n*sizeof(T));
        }
        
        static void deallocate(T* p){
            Alloc::deallocate(p,sizeof(T));
        }
    };
}
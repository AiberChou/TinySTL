#include <cstdlib>
#include <cstddef>
#include "../include/alloc.h"
#include <iostream>

namespace TinySTL{
    
    // static member declare in class, initialize out of class
    void (* __malloc_alloc::__malloc_alloc_oom_handler)() = nullptr;

    void* __malloc_alloc::oom_malloc(size_t n){
        void (*my_malloc_handler)();
        void* result;

        for(;;){
            my_malloc_handler = __malloc_alloc_oom_handler;
            if(my_malloc_handler == nullptr) {
                std::cerr<<"out of memory"<<std::endl;
                exit(1);
            }
            (*my_malloc_handler)(); // handle for out of memory
            result = malloc(n);
            if(result) return result;
        }
    }

    void* __malloc_alloc::oom_realloc(void *p, size_t n){
        void (*my_malloc_handler)();
        void* result;

        for(;;){
            my_malloc_handler = __malloc_alloc_oom_handler;
            if(my_malloc_handler == nullptr) {
                std::cerr<<"out of memory"<<std::endl;
                exit(1);
            }
            (*my_malloc_handler)(); // handle for out of memory
            result = realloc(p,n);
            if(result) return result;
        }
    }

    typedef __malloc_alloc malloc_alloc;// useless, just a alias

    char* __default_alloc::start_free = 0;
    char* __default_alloc::end_free = 0;
    size_t __default_alloc::heap_size = 0;
    
    //this freelist point to small storage chunk, default nullptr
    __default_alloc::obj* volatile __default_alloc::free_list[__default_alloc::ENFreeLists::NFREELISTS]={nullptr};

    void* __default_alloc::allocate(size_t n){
        obj* volatile * my_free_list; //the same as free_list just using pointer rather than array
        obj* result;

        // if bytes bigger than 128, using first-level allocator to get memory
        if(n>(size_t)EMaxBytes::MAXBYTES)
            return(malloc_alloc::allocate(n));
        
        // else find a suitable freelist
        // the same as &free_list[freelist_index(n)], get a suitable freelist's address
        my_free_list = free_list + freelist_index(n);
        result = *my_free_list;
        // nullptr represents the freelist don't have memory left, get new memory
        if(result == nullptr){
            void *r = refill(round_up(n));
            return r;
        }
        *my_free_list = result -> free_list_link;
        return (result);
    }

    void __default_alloc::deallocate(void* p, size_t n){
        obj* q = (obj*)p;
        obj* volatile * my_free_list;

        if(n>(size_t)EMaxBytes::MAXBYTES){
            malloc_alloc::deallocate(p,n);
            return;
        }

        // find the freelist which needs to recycle memory
        my_free_list = free_list + freelist_index(n);
        q->free_list_link = *my_free_list;
        *my_free_list = q;
    }

    void* __default_alloc::refill(size_t n){
        int nobjs = 20;
        char* chunk = chunk_alloc(n,nobjs);
        obj* volatile *my_free_list;
        obj* result;
        obj* current_obj,* next_obj;
        
        // if only get one chunk, give it to user, needn't to adjust freelist.
        if(nobjs == 1) return chunk;

        // otherwise need to adjust freelist
        my_free_list = free_list + freelist_index(n);        
        result = (obj*)chunk;
        // char need a bytes, size_t n needs n bytes, so the address of next obj is chunk+n
        next_obj = (obj*)(chunk+n);
        *my_free_list = next_obj;
        // link all node of the freelist
        for(int i=1;i<nobjs;i++){
            current_obj = next_obj;
            next_obj = (obj*)((char*)next_obj + n);
            if(i == nobjs-1){
                current_obj->free_list_link = nullptr;
            }
            else{
                current_obj->free_list_link = next_obj;
            }
        }
        return (result);
    }

    char* __default_alloc::chunk_alloc(size_t size, int& nobjs){
        char* result;
        size_t total_bytes = size * nobjs; // required memory
        size_t bytes_left = end_free - start_free; // the left memory in the memory pool

        // if memory pool have enough bytes, allocate enough bytes to freelist
        if(bytes_left >= total_bytes){
            result = start_free;
            start_free += total_bytes;
            return (result);
        }
        // if memory pool can't allocate nobjs chunk, allocate as many chunk as it can
        else if(bytes_left>=size){
            nobjs = bytes_left/size;
            total_bytes = size* nobjs;
            result = start_free;
            start_free+=total_bytes;
            return (result);
        }
        // memory pool can't allocate a chunk, need to get memory from heap
        else{
            // we need total_bytes to allocate to freelist, the rest left for allocating later 
            size_t bytes_to_get = 2* total_bytes + round_up(heap_size >> 4);
            if(bytes_left >0){
                // allocate left bytes to suitable freelist
                obj* volatile* my_free_list = free_list + freelist_index(bytes_left);
                ((obj*)start_free)->free_list_link = *my_free_list;
                *my_free_list = (obj*)start_free;
            }
            // get memory from heap
            start_free = (char*) malloc(bytes_to_get);
            // if fail to get memroy from heap
            if(start_free == nullptr){
                obj* volatile * my_free_list, *p;
                // deallocate memory from bigger freelist and reallocate
                for(int i=size;i<EMaxBytes::MAXBYTES; i+=EAlign::ALIGN){
                    my_free_list = free_list + freelist_index(i);
                    p=*my_free_list;
                    if(p!=nullptr){
                        // reallocate a chunk of this freelist
                        *my_free_list = p->free_list_link;
                        start_free = (char*)p;
                        end_free = start_free + i;
                        return(chunk_alloc(size,nobjs));
                    }
                }
                // if nothing left in the memory pool and freelist, call first-level allocator to get memory  
                end_free=nullptr;
                start_free = (char*)malloc_alloc::allocate(bytes_to_get);
            }
            heap_size += bytes_to_get;
            end_free = start_free + bytes_to_get;
            // after get memory, allocate them to freelist
            return(chunk_alloc(size,nobjs));
        }
    }

    typedef __default_alloc default_alloc;
}
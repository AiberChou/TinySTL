#include "../include/vector.h"

namespace TinySTL{

    // keyword "inline" only when using in definition is vaild. Using in declare is invaild
    template<class T,class Alloc>
    inline void vector<T,Alloc>::resize(size_type new_size, const T& x){
        if(new_size<size()) erase(begin()+new_size,end());
        else TinySTL::insert(end,new_size-size(),x)
    }

    template<class T,class Alloc>
    void vector<T,Alloc>::reserve(size_type new_size){
        if(new_size<capacity())
            return;
        T* new_start = data_allocator::allocate(new_size);
        T* new_finish = TinySTL::uninitialized_copy(start,finish,new_start);
        destroy_and_deallocate();
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + new_size;
    }

    template<class T,class Alloc>
    void vector<T,Alloc>::push_back(const T& x){
        if(finish != end_of_storage){
                TinySTL::construct(finish,x);
                finish++;
        }
        else{
            insert(end(),x);
        }
    }

    template<class T,class Alloc>
    void vector<T,Alloc>::pop_back(){
        --finish;
        TinySTL::destroy(finish);
    }

    template<class T,class Alloc>
    vector<T,Alloc>::iterator vector<T,Alloc>::insert(iterator position,const T& x){
        // if there is memory left
        if(finish!=end_of_storage){
            // if using copy_backward(position,finish-1,finish), can we remove construct()?
            TinySTL::construct(finish,*(finish-1)); // copy last elem to the back
            ++finish;
            T* x_copy = x;
            // move all elem behind "position" back by one, contains "position"
            TinySTL::copy_backward(position,finish-2,finish-1);
            *position = x_copy; //insert
            return position;
        }
        // if no capacity left, get double capacity
        else{
            const size_type old_size = size();
            const size_type new_size = old_size != 0 ? 2*old_size : 1;
            iterator new_start = data_allocator::allocate(new_size);
            iterator new_finish = new_start;
            iterator new_position = position;
            // if failed to copy, recycle memory and exit, because computer maybe none memory left
            try{
                // copy elem which front of "position"
                new_finish = TinySTL::uninitialized_copy(start,position,new_start);
                // insert elem at "new_position"
                new_position = new_finish;
                TinySTL::construct(new_finish,x);
                // copy elem which behind "position"
                ++new_finish;
                new_finish = TinySTL::uninitialized_copy(position,finish,new_finish)
            }
            catch(...){
                // recycle new allocated memory in heap;
                TinySTL::destroy(new_start,new_finish);
                data_allocator::deallocate(new_start,new_size);
                throw;
            }
            // recycle old memory
            destroy_and_deallocate();
            // adjust iterator to new memory
            start=new_start;
            finish=new_finish;
            end_of_storage = new_start + new_size;
            return new_position;
        }
    }

    template<class T,class Alloc>
    vector<T,Alloc>::iterator vector<T,Alloc>::insert(iterator position, size_type n, const T& x){
        if(n==0) return position;
        else{
            if(size_type(end_of_storage-finish)>n){
                T* x_copy = x;
                // for class T must call "uninitialized_fill_n" or other function for "construct", 
                // otherwise u can't get memory to allocate for new elements.
                TinySTL::uninitialized_fill_n(finish,n,x_copy);
                TinySTL::copy_backward(position,finish,finish+n);
                finish = finish + n;
                TinySTL::fill(position,position+n,x_copy);
                return position;
            }
            else{
                const size_type old_size = end_of_storage - start;
                const size_type new_size = old_size + TinySTL::max(old_size,n);
                iterator new_start = data_allocator::allocate(new_size);
                iterator new_finish = new_start;
                iterator new_position = position;
                try{
                    new_finish = TinySTL::uninitialized_copy(start,position,new_start);
                    new_position = new_finish;
                    new_finish = TinySTL::uninitialized_fill_n(new_finish,n,x);
                    TinySTL::copy_backward(position,finish,new_finish);
                }
                catch(...){
                    TinySTL::destroy(new_start,new_finish);
                    data_allocator::deallocate(new_start,new_size);
                    throw;
                }
                start = new_start;
                finish = new_finish;
                end_of_storage = start + new_size;
                return new_position;
            }
        }
    }

    template<class T,class Alloc>
    vector<T,Alloc>::iterator vector<T,Alloc>::erase(iterator position){
        if(position + 1 != end()){
                TinySTL::copy(position+1,finish,position);
        }
        --finish;
        TinySTL::destroy(finish);
        return position;
    }

    template<class T,class Alloc>
    vector<T,Alloc>::iterator vector<T,Alloc>::erase(iterator first,iterator last){
        iterator i=TinySTL::copy(last,finish,first);
        destroy(i,finish);
        finish = finish - (last - first);
        return first;
    }


    template<class T,class Alloc>
    void vector<T,Alloc>::deallocate(){
        if(start) data_allocator::deallocate(start,end_of_storage-start);
    } 

    template<class T,class Alloc>
    void vector<T,Alloc>::allocate_and_fill(size_type n,const T& x){
        start = data_allocator::allocate(n);
        finish = TinySTL::uninitialized_fill_n(start,n,x);
        end_of_storage = finish;
    }

    template<class T,class Alloc>
    template<class InputIterator>
    void vector<T,Alloc>::allocate_and_copy(InputIterator first,InputIterator last){
        start = data_allocator::allocate(last-first);
        finish = TinySTL::uninitialized_copy(first,last,start);
        end_of_storage = finish;
    }

    template<class T,class Alloc>
    void vector<T,Alloc>::destroy_and_deallocate(){
        TinySTL::destroy(start,finish);
        deallocate();
    }
}
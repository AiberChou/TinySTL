/*
Why dose a member function can using other member functions without 
declare them before it?(for example in function "void fill_initialize")

This actually involves C++ name lookup rules. 
For global function, it only find name from start to where u using it.
But for member function(variate) or friend function, it find this func 
in all this class. So u needn't declare this function before u use it.  
*/



#pragma once

#include "alloc.h"
#include "construct.h"
#include "uninitialized.h"
#include "algorithm.h"
#include <cstddef> //for size_t,ptrdiff_t

namespace TinySTL{

    template<class T,class Alloc=default_alloc>
    class vector{
    public:
        typedef T                   value_type;
        typedef value_type*         pointer;
        typedef value_type*         iterator;
        typedef const value_type*   const_iterator;
        typedef value_type&         reference;
        typedef const value_type&   const_reference;
        typedef size_t              size_type;
        typedef ptrdiff_t           difference_type;

    protected:
        typedef simple_alloc<value_type, Alloc> data_allocator;

        iterator start;
        iterator finish;
        iterator end_of_storage;

    public:
        // Iterator Function
        iterator begin(){return start;}
        iterator end(){return finish;}

        // Access Function
        reference front(){return *begin();}
        reference back(){return *(end()-1);}
        reference operator[](size_type n){return *(begin()+n);}

        // Capacity Function
        // function "resize" change size(), but capacity() remains unchanged.
        size_type size() const{return size_type(end()-begin());}
        size_type capacity() const{return size_type(end_of_storage-begin());}
        bool empty() const{return begin()==end();}
        void resize(size_type new_size, const T& x);
        void resize(size_type new_size){resize(new_size,T());};
        void reserve(size_type new_size);

        // Constructor Function
        vector():start(0),finish(0),end_of_storage(0){}
        explicit vector(size_type n){allocate_and_fill(n,T());}
        vector(size_type n,const T& value){allocate_and_fill(n,value);}
        template<class InputIterator>
        vector(InputIterator begin,InputIterator end){allocate_and_copy();}
        vector(const vector& other);
        vector(vector&& other);
        vector& operator=(const vector& other);
        vector& operator=(const vector&& other);
        
        ~vector(){destroy_and_deallocate();}

        // Modify Element Function
        void push_back(const T&x);
        void pop_back();
        iterator insert(iterator position, const T& x);
        iterator insert(iterator position, size_type n,const T& x);
        iterator erase(iterator position);
        iterator erase(iterator first,iterator last);
        void clear(){erase(begin(),end());}

    protected:
        // Auxiliary Function
        void deallocate();
        void allocate_and_fill(size_type n,const T& x);
        template<class InputIterator>
        void allocate_and_copy(InputIterator first,InputIterator last);
        void destroy_and_deallocate();
    };

    
}
// separate declare and definition of template class
// because while compiling, template class(and so on) will not 
// allocate memory until a template be called. If not do so, while
// linking, some errors will happen.
#include "../src/vector.cpp"
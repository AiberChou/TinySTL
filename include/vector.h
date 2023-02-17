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

namespace TinySTL{

    template<class T,class Alloc=default_alloc>
    class vector{
    public:
        typedef T               value_type;
        typedef value_type*     pointer;
        typedef value_type*     iterator;
        typedef value_type&     reference;
        typedef size_t          size_type;
        typedef ptrdiff_t       difference_type;

    protected:
        typedef simple_alloc<value_type, Alloc> data_allocator;

        iterator start;
        iterator finish;
        iterator end_of_storage;

        void insert_aux(iterator position, const T& x);
        void deallocate(){
            if(start)
                data_allocator::deallocate(start,end_of_storage - start);
        }
        void fill_initialize(size_type n, const T& value){
            start = allocate_and_fill(n,value);
            finish = start + n;
            end_of_storage = finish;
        }

    public:
        iterator begin(){return start;}
        iterator end(){return finish;}
        size_type size() const{return size_type(end()-begin());}
        size_type capacity() const{return size_type(end_of_storage-begin());}
        bool empty() const{return begin()==end();}
        reference operator[](size_type n){return *(begin()+n);}
        
        vector():start(0),end(0),end_of_storage(0){}
        vector(size_type n,const T& value){fill_initialize(n,value);}
        vector(iterator begin,iterator end)
        explicit vector(size_type n){fill_initialize(n,T());}

        ~vector(){
            destroy(start,finish);
            deallocate();
        }

        reference front(){return *begin();}
        reference back(){return *(end()-1);}
        void push_back(const T&x){
            if(finish != end_of_storage){
                construct(finish,x);
                finish++;
            }
            else{
                insert_aux(end(),x);
            }
        }

        void pop_back(){
            --finish;
            destroy(finish);
        }

        iterator erase(iterator position){
            if(position + 1 != end()){
                copy(position+1,finish,position);
            }
            --finish;
            destroy(finish);
            return position;
        }

        void resize(size_type new_size, const T& x){
            if(new_size<size()) erase(begin()+new_size,end());
            else insert(end, new_size-size(), x);
        }

        void resize(size_type new_size){ resize(new_size,T());}
        void clear(){erase(begin(),end());}

    protected:
        iterator allocate_and_fill(size_type n,const T& x){
            iterator result = data_allocator::allocate(n);
            uninitialized_fill_n(result,n,x);
            return result;
        }
    };

    
}
// separate declare and definition of template class
// because while compiling, template class(and so on) will not 
// allocate memory until a template be called. If not do so, while
// linking, some errors will happen.
#include "../src/vector.cpp"
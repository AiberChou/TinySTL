#pragma once

#include "iterator.h"
#include "traits.h"
#include "construct.h"

namespace TinySTL{

    // compare with _true_type function, this function has a loop.So it is unsuitable to be declared as a inline function
    template<class InputIterator, class ForwardIterator, class T>
    ForwardIterator __uninitialized_copy_aux(
            InputIterator first, InputIterator last, ForwardIterator result, _false_type fp){
        ForwardIterator cur = result;
        for(;cur!=last;++first,++cur){
            construct(&*cur,*first);
        }
        return cur;
    }

    template<class InputIterator, class ForwardIterator, class T>
    inline ForwardIterator __uninitialized_copy_aux(
            InputIterator first, InputIterator last, ForwardIterator result, _true_type tp){
        return copy(first,last,result);
    }

    template<class InputIterator, class ForwardIterator, class T>
    inline ForwardIterator __uninitialized_copy(
            InputIterator first, InputIterator last, ForwardIterator result, T* t){
        typedef typename __type_traits<T>::is_POD_type is_POD;
        return __uninitialized_copy_aux(first,last,result,is_POD());
    }

    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator uninitialized_copy(
            InputIterator first, InputIterator last, ForwardIterator result){
        return __uninitialized_copy(first,last,result,value_type(first));
    }



    template<class ForwardIterator, class T>
    ForwardIterator uninitialized_fill_aux(
            ForwardIterator first, ForwardIterator last, const T& x, _false_type fp){
        ForwardIterator cur = first;
        for(;cur!=last;++first,++cur){
            construct(&*cur,x);
        }
        return cur;
    }

    template<class ForwardIterator, class T>
    inline ForwardIterator uninitialized_fill_aux(
            ForwardIterator first, ForwardIterator last, const T& x, _true_type tp){
        return fill(first,last,x);
    }

    template<class ForwardIterator, class T>
    inline ForwardIterator __uninitialized_fill(
            ForwardIterator first, ForwardIterator last, const T& x){
        typedef typename __traits_type<T>::is_POD_type is_POD;
        return __uninitialized_fill_aux(first,last,x,is_POD());
    }

    template<class ForwardIterator, class T>
    inline ForwardIterator uninitialized_fill(
            ForwardIterator first, ForwardIterator last, const T& x){
        return __uninitialized_fill(first,last,x,value_type(first));
    }



    template<class ForwardIterator, class Size, class T>
    ForwardIterator __uninitialized_fill_n_aux(
            ForwardIterator first, Size n, const T& x, _false_type fp){
        ForwardIterator cur = first;
        for(;n>0;--n,++cur){
            construct(&*cur,x); // call copy constructer
        }
        return cur;
    }

    template<class ForwardIterator, class Size, class T>
    inline ForwardIterator __uninitialized_fill_n_aux(
            ForwardIterator first, Size n, const T& x, _true_type tp){
        return fill_n(first,n,x);
    }

    template<class ForwardIterator, class Size, class T, class T1>
    inline ForwardIterator __uninitialized_fill_n(
            ForwardIterator first, Size n, const T& x,T1* t){
        typedef typename __type_traits<T1>::is_POD_type is_POD;
        return __uninitialized_fill_n_aux(first,n,x,is_POD());
    }
                                            
    template<class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n(
            ForwardIterator first, Size n, const T& x){
        return __uninitialized_fill_n(first,n,x,value_type(first));
    }
}
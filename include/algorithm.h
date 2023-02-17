#pragma once

namespace TinySTL{
    
    template<class ForwardIterator,class T>
    void fill(ForwardIterator first,ForwardIterator last,const T& value){
        for(;first!=last;++first){
            *first = value;
        }
    }

    template<class OutputIterator, class Size, class T>
    OutputIterator fill_n(OutputIterator first, Size n, const T& value){
        for(;n>0;--n,++first){
            *first = value;
        }
        return first;
    }

    // Iterator is a special pointer, this functhion using pointer as a parameter, 
    // a temporary variate(Focus) which copy from this pointer is using in this function. 
    // So the value of original pointer remain unchanged, but the value which the 
    // pointer points to can be changed. return "result" is the same as "last"
    template<class InputIterator, class OutputIterator>
    OutputIterator copy(InputIterator first,InputIterator last,OutputIterator result){
        for(;first!=last;++first,++result){
            *result = *first;
        }
        return result;
    }

    template<class BidirectionIterator>
    BidirectionIterator copy_backward(BidirectionIterator first,BidirectionIterator last,BidirectionIterator d_last){
        while(first!=last){
            *(--d_last)=*(--last);
        }
        return d_last;
    }
}
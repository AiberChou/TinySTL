/*
    before using this file to test, please change __default_malloc's 
    private member to public member.
*/


// #include <iostream>
// #include <vector>
// #include "../include/alloc.h"


// int main(){

//     size_t bytes=9;
//     //bytes = TinySTL::default_alloc::round_up(bytes);
//     //char*& start = TinySTL::default_alloc::start_free;
//     //void*p = TinySTL::default_alloc::refill(bytes);
//     void*q = TinySTL::default_alloc::allocate(bytes);
//     void*m = TinySTL::default_alloc::allocate(bytes*4);
//     //TinySTL::default_alloc::deallocate(p,bytes);
//     void*w = TinySTL::default_alloc::allocate(bytes);
//     return 0;
// }
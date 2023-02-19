#include <iostream>
#include "../include/vector.h"

class M1{
public:
    int a;
    int b;
    M1():a(0),b(0){}
    M1(int a,int b):a(a),b(b){}
    M1(const M1& other):a(other.a),b(other.b){}
};


// size(),capacity(),erase()
using namespace TinySTL;
int main(){


    vector<M1>* vec=new vector<M1>(2,M1(20,30));
    M1 a(10,20);
    auto sz= vec->size();
    auto cap = vec->capacity();
    // vec->push_back(M1(10,20));
    for (auto i = vec->begin(); i != vec->end(); ++i)
    {
        std::cout<<"sizeof M1:"<<sizeof(M1(20,30))<<"\t"<< i->a <<"\t"<< i->b <<std::endl;
    }
    vec->erase(vec->begin());
    sz=vec->size();
    vec->erase(vec->begin(),vec->end());
    sz=vec->size();
    cap=vec->capacity();
    delete vec;
    vector<M1>* vec2=new vector<M1>(2,M1(20,30));
    delete vec2;
    return 0;
}
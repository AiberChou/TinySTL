#include <iostream>

template <class T>
class test{
    public:
        T a1;
        T a2;
        T a3;

        test(T a1, T a2, T a3):a1(a1),a2(a2),a3(a3){
            std::cout << this->a1 <<'\t'<<this->a2<<'\t'<<this->a3<<std::endl;
        }
};

template<>
class test<int>{
    public:
    int a1;
    test(int a1):a1(a1){
        std::cout<< this->a1<<std::endl;
    }
};


int main(){
    int a=1;
    test<int> t1(a);
    std::cout<<t1.a2<<std::endl;
    return 0;
}
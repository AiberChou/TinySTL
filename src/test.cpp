#include<iostream>
#include<vector>

using namespace std;
int main(){
    vector<int>* v1=new vector<int>(10);
    cout<<v1->capacity()<<endl;
    v1->push_back(12);
    cout<<v1->capacity()<<endl;
    v1->resize(5);
    cout<<v1->size()<<'\t'<<v1->capacity()<<endl;
    return 0;
}
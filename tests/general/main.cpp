#include<iostream>

class test{
    public:
    int foo(){
        std::cout << "asdf" << std::endl;
    }
};


void foo(){
    std::cout << "asdf" << std::endl;
}

int main(){
    test a;
    a.foo();
}

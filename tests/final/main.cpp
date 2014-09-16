#include <iostream>
using namespace std;

class foo{
    public:
    int bar() final{
        foobar();
    }

    void foobar()(cout << "blah";)
};

class baz() : public foo{
    public:
        void foobar() override {
            cout << " not blah";
        }
};

int main(){
    baz a();

    baz.foo();
}

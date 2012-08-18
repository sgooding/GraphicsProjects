#include <iostream>
#include <stdlib.h>

void test()
{
    std::cout << "test" << std::endl;
}

void test2()
{
    std::cout << "test2" << std::endl;
}

void (*blah)() = 0;

class A;
void (A::*mFunc)() = 0;
class A
{
    public:
    A()
    {
        mFunc = &A::run;
    }
    void setrun2()
    {
        mFunc = &A::run2;
    }
    void run()
    {
        std::cout << "A run" << std::endl;
    }
    void run2()
    {
        std::cout << "A run 2" << std::endl;
    }

};

int main(int argn, char* argv[])
{
    blah = &test;
    (*blah)();
    blah = &test2;
    (*blah)();

    A a;
    (a.*mFunc)();
    a.setrun2();
    (a.*mFunc)();
 
    return EXIT_SUCCESS;
}

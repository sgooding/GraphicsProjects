#include <iostream>
#include <stdlib.h>

#include <boost/thread.hpp>

void f()
{
    while(1)
    {
        std::cout << "Sleeping" << std::endl;
        usleep(10000);
    }
}

class A
{
    public:
    void run()
    {
       f(); 
    }
};

class B
{
    public:
    B():mT(&B::run,this)
    {
        mT.join();
    }

    private:
    void run()
    {
        f();
    }
    boost::thread mT;
};

void test()
{
    std::cout << "test" << std::endl;
}

void test2()
{
    std::cout << "test2" << std::endl;
}

void (*blah)() = 0;

int main(int argn, char* argv[])
{
    std::cout << "Hello World" << std::endl;
    //boost::thread t1(&f);
    //t1.join();
    
    //A a;
    //boost::thread t2(&A::run,&a);
    //t2.join();

    //B b;

    blah = &test;
    (*blah)();
    blah = &test2;
    (*blah)();
    return EXIT_SUCCESS;
}

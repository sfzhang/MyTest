#include "a.h"
#include "b.h"

A::A()
{
    static int i = 0;
    std::cout << "---------------------------" << std::endl;
    std::cout << "A::A()" << std::endl;
    std::cout << i << std::endl;
    std::cout << "call B::print()" << std::endl;
    B::instance()->print();
    std::cout << "---------------------------" << std::endl;
}

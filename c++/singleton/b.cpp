#include "b.h"
#include "a.h"

B::B()
{
    static int i = 0;
    std::cout << "---------------------------" << std::endl;
    std::cout << "B::B()" << std::endl;
    std::cout << i << std::endl;
    std::cout << "call A::print()" << std::endl;
    A::instance()->print();
    std::cout << "---------------------------" << std::endl;
}

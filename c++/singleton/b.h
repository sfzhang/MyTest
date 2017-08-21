#ifndef B_H
#define B_H

#include <iostream>
#include <memory>

class B {

public:

    static std::shared_ptr<B> &instance()
    {
        static std::shared_ptr<B> s_b(new B);
        return s_b;
    }

    void print()
    {
        std::cout << "This is B::print()" << std::endl;
    }

protected:

    B();

};

#endif

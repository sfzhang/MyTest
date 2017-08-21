#ifndef A_H
#define A_H

#include <iostream>
#include <memory>

class A {

public:

    static std::shared_ptr<A> &instance()
    {
        static std::shared_ptr<A> s_a(new A);
        return s_a;
    }

    void print()
    {
        std::cout << "This is A::print()" << std::endl;
    }

protected:

    A();

};

#endif

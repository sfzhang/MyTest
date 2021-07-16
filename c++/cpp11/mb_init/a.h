_Pragma("once")

#include <iostream>

enum class E {
    red,
    blue
};

class A {

public:

    A() {}

    A(double d): m_d(d), m_c('m') {}

    void print() const
    {
        std::cout << m_d << "; " << m_c << "; " << m_f << std::endl;
    }

private:

    static const int K_I = 1;
    static const E K_E{E::red};

    // ISO C++ forbids in-class initialization of non-const static member ‘A::s_i’
    // static int s_i{0};
    static E s_e;

    // Use {} instead ()
    // double m_d(0);
    double m_d{0};
    char m_c{'c'};
    float m_f = 0.1;
};

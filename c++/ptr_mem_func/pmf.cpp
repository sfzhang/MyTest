#include <iostream>

using namespace std;

struct B1 {
    void print(int i)
    {
        cout << "B1::print(): " << i << endl;
    }
};

struct B2 {
    void print(const char *s)
    {
        cout << "B2::print(): " << s << endl;
    }
};

int main()
{
    using B1FPtr = void (B1::*)(int);
    using B2FPtr = void (B2::*)(const char*);

    B1FPtr b1_fptr = &B1::print;

    void *vptr = reinterpret_cast<void*>(b1_fptr);
    int *ptr = (int*)vptr;

    cout << *ptr << ' ' << *(ptr + 1) << endl;

    //B2FPtr b2_fptr = static_cast<B2FPtr>(b1_fptr); error!!!

    B2 b2;

    B2FPtr b2_fptr = reinterpret_cast<B2FPtr>(b1_fptr);
    (b2.*b2_fptr)("point to member function"); // call B1::print();

    (b2.*((B2FPtr)b1_fptr))("point to member function"); // call B1::print(), (B2FPtr) force cast!!!

    (((B1 *)0)->*b1_fptr)(100); // B1 *(nullptr) is ok!

    return 0;
}

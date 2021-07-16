#include <iostream>

using namespace std;

struct A {};

struct B {

    // explicit conversion
    explicit operator A() const { return A(); }
};

void f(A a)
{
}

int main()
{
    B b;
    A a1(b);

    // error: conversion from ‘B’ to non-scalar type ‘A’ requested
    // A a2 = b;

    A a3 = static_cast<A>(b);

    // error: could not convert ‘b’ from ‘B’ to ‘A’
    // f(b);

    f(static_cast<A>(b));

    return 0;
}

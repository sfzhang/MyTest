#include <iostream>

using namespace std;

int i{};
static int j{};
 
int getValue()
{
  return 0;
}

 
int main()
{
    static int q = 0;
    auto l = []{ return q++; };

    cout << l() << endl;
    cout << l() << endl;
    cout << l() << endl;

    auto l2 = [p=i]() mutable { return p++; };
    cout << (l2()) << endl;
    cout << (l2()) << endl;
    cout << (l2()) << endl;

  int a{};
  constexpr int b{};
  static int c{};
  static constexpr int d{};
  const int e{};
  const int f{ getValue() };
  static const int g{}; 
  static const int h{ getValue() }; 
 
  [](){
    // Try to use the variables without explicitly capturing them.
    // erro: a is local variable
    // a;
    b; // constant expression
    c; // static storage duration.
    d;
    e;
    // error: f‘s value depends on getValue, which might require the program to run.
    //f;
    g;
    h;
    i; //global variable
    j;
  }();
 
  return 0;
}

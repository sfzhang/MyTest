#include <iostream>
#include <array>
#include <string>

using namespace std;

struct S {string m_s;};

class Point {
    int m_x;
    int m_y;
public:

    constexpr Point(int x, int y): m_x(x), m_y(y) {}    // 函数体要求为空
    
    constexpr int x() const noexcept { return m_x; }
    
    constexpr int y() const noexcept { return m_y; }
    
    constexpr void setX(int x) noexcept { m_x = x; }    // C++14
    
    constexpr void setY(int y) noexcept { m_y = y; }    // C++14
};

constexpr int f(Point p)
{
    return p.x();
}

constexpr int pow(int base, int exp) noexcept 		// C++14 OK, C++11 error!!!
{
	auto result = 1;
	for (int i = 0; i < exp; i++) result *= base;
	return result;
}

// std::string is not literal
/*
constexpr void g(string s)
{
}
*/

constexpr int fun()
{
    return 1;
}

constexpr int goo(int a)
{
    return a = 1;
}

int main()
{
    const int b = 1;
    int c = 2;
    cin >> c;
    const int a = b + c;
    const int f = 0;
    constexpr auto d = b + f;
    cout << a << endl;

    constexpr auto dd = fun();
    // error: the value of ‘c’ is not usable in a constant expression
    constexpr auto gg = goo(c);
    return 0;
}

#include <iostream>
#include <cmath>

double norm(double a)
{
    return a - 2 * M_PI * std::floor((a + M_PI) / (2 * M_PI));
}

int main()
{
    std::cout << "norm(3 * M_PI): " << norm(3 * M_PI) << std::endl;
    std::cout << "norm(2 * M_PI + 1): " << norm(2 * M_PI + 1) << std::endl;
    std::cout << "norm(2 * M_PI): " << norm(2 * M_PI) << std::endl;
    std::cout << "norm(M_PI + 0.5): " << norm(M_PI + 0.5) << std::endl;
    std::cout << "norm(M_PI): " << norm(M_PI) << std::endl;
    std::cout << "norm(M_PI - 0.5): " << norm(M_PI - 0.5) << std::endl;
    std::cout << "norm(0): " << norm(0) << std::endl;
    std::cout << "norm(-M_PI + 0.5): " << norm(-M_PI + 0.5) << std::endl;
    std::cout << "norm(-M_PI): " << norm(-M_PI) << std::endl;
    std::cout << "norm(-M_PI - 0.5): " << norm(-M_PI - 0.5) << std::endl;
    std::cout << "norm(-2 * M_PI): " << norm(-2 * M_PI) << std::endl;
    std::cout << "norm(-2 * M_PI - 1): " << norm(-2 * M_PI - 1) << std::endl;
    std::cout << "norm(-3 * M_PI): " << norm(-3 * M_PI) << std::endl;

    return 0;
}

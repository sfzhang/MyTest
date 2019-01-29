#include <iostream>
#include <utility>
#include <typeinfo>
#include <boost/type_index.hpp>

using namespace boost::typeindex;
using namespace std;

void f(int, double)
{
}

int main()
{
    cout << "***** pointer *****" << endl;

    {
        int x = 0;
        auto *p = &x;
        cout << "int x = 0; auto *p = &x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        const int x = 0;
        auto *p = &x;
        cout << "const int x = 0; auto *p = &x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        int x[] = {1, 2};
        auto *p = x;
        cout << "int x[] = {1, 2}; auto *p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        const int x[] = {1, 2};
        auto *p = x;
        cout << "const int x[] = {1, 2}; auto *p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        auto *p = f;
        cout << "void f(int, double); auto *p = f" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        int x = 0;
        const auto *p = &x;
        cout << "int x = 0; const auto *p = &x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        const int x = 0;
        const auto *p = &x;
        cout << "const int x = 0; const auto *p = &x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        int x[] = {1, 2};
        const auto *p = x;
        cout << "int x[] = {1, 2}; const auto *p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        const int x[] = {1, 2};
        const auto *p = x;
        cout << "const int x[] = {1, 2}; const auto *p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    /* compile failed: types ‘const auto’ and ‘void(int, double)’ have incompatible cv-qualifiers
    {
        const auto *p = f;
        cout << "void f(int, double); auto *p = f" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }
    */

    cout << "***** reference *****" << endl;

    {
        int x = 0;
        auto &p = x;
        cout << "int x = 0; auto &p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        const int x = 0;
        auto &p = x;
        cout << "const int x = 0; auto &p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        int x[] = {1, 2};
        auto &p = x;
        cout << "int x[] = {1, 2}; auto &p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        const int x[] = {1, 2};
        auto &p = x;
        cout << "const int x[] = {1, 2}; auto &p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        auto &p = f;
        cout << "void f(int, double); auto &p = f" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        int &&a = 1;
        auto &p = a;
        cout << "int &&a = 1; auto &p = a" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    /* invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘std::remove_reference<int&>::type {aka int}
    {
        int &&a = 1;
        auto &p = std::move(a);
        cout << "int &&a = 1; auto &p = std::move(a)" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }
    */

    {
        int x = 0;
        const auto &p = x;
        cout << "int x = 0; const auto &p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        const int x = 0;
        const auto &p = x;
        cout << "const int x = 0; const auto &p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        int x[] = {1, 2};
        const auto &p = x;
        cout << "int x[] = {1, 2}; const auto &p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        const int x[] = {1, 2};
        const auto &p = x;
        cout << "const int x[] = {1, 2}; const auto &p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        const auto &p = f;
        cout << "void f(int, double); const auto &p = f" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        int &&a = 1;
        const auto &p = a;
        cout << "int &&a = 1; const auto &p = a" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        int &&a = 1;
        const auto &p = std::move(a);
        cout << "int &&a = 1; const auto &p = std::move(a)" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    cout << "***** univeral reference *****" << endl;

    {
        int x = 0;
        auto &&p = x;
        cout << "int x = 0; auto &&p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        const int x = 0;
        auto &&p = x;
        cout << "const int x = 0; auto &&p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        int x[] = {1, 2};
        auto &&p = x;
        cout << "int x[] = {1, 2}; auto &&p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        const int x[] = {1, 2};
        auto &&p = x;
        cout << "const int x[] = {1, 2}; auto &&p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        auto &&p = f;
        cout << "void f(int, double); auto &&p = f" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        auto &&p = 1;
        cout << "auto &&p = 1" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        int &&a = 1;
        auto &&p = a;
        cout << "int &&a = 1; auto &&p = a" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        int &&a = 1;
        auto &&p = std::move(a);
        cout << "int &&a = 1; auto &&p = std::move(a)" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    cout << "***** not pointer and reference *****" << endl;

    {
        int x = 0;
        auto p = x;
        cout << "int x = 0; auto p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        const int x = 0;
        auto p = x;
        cout << "const int x = 0; auto p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        int x[] = {1, 2};
        auto p = x;
        cout << "int x[] = {1, 2}; auto p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        const int x[] = {1, 2};
        auto p = x;
        cout << "const int x[] = {1, 2}; auto p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        auto p = f;
        cout << "void f(int, double); auto p = f" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        auto p = 1;
        cout << "auto p = 1" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        int a = 1;
        auto p = a;
        cout << "int a = 1; auto p = a" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        int a = 1;
        auto p = std::move(a);
        cout << "int a = 1; auto p = std::move(a)" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        int a = 1;
        int &b = a;
        auto p = b;
        cout << "int a = 1; int &b = a; auto p = b" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        const int &b = 1;
        auto p = b;
        cout << "const int &b = 1; auto p = b" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    cout << "******** cont auto *******" << endl;

    {
        int x = 0;
        const auto p = x;
        cout << "int x = 0; const auto p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        const int x = 0;
        const auto p = x;
        cout << "const int x = 0; const auto p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        int x[] = {1, 2};
        const auto p = x;
        cout << "int x[] = {1, 2}; const auto p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        const int x[] = {1, 2};
        const auto p = x;
        cout << "const int x[] = {1, 2}; const auto p = x" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        const auto p = f;
        cout << "void f(int, double); const auto p = f" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        const auto p = 1;
        cout << "const auto p = 1" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        int a = 1;
        const auto p = a;
        cout << "int a = 1; const auto p = a" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        int a = 1;
        const auto p = std::move(a);
        cout << "int a = 1; const auto p = std::move(a)" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;

    }

    {
        int a = 1;
        int &b = a;
        const auto p = b;
        cout << "int a = 1; int &b = a; const auto p = b" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        const int &b = 1;
        const auto p = b;
        cout << "const int &b = 1; const auto p = b" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    cout << "initializer_list" << endl;

    {
        auto p = { 1 };
        cout << "auto p = { 1 }" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    {
        auto p{ 1 };
        cout << "auto p{ 1 }" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }

    /* error: direct-list-initialization of ‘auto’ requires exactly one element
    {
        auto p{ 1.1, 2.2 };
        cout << "auto p{ 1.1 }" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }
    */

    /* error: unable to deduce ‘std::initializer_list<auto>’ from ‘{1, 2.2000000000000002e+0}’
    {
        auto p = { 1, 2.2 };
        cout << "auto p{ 1, 2.2 }" << endl;
        cout << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
        cout << "-----------------" << endl;
    }
    */

    return 0;
}

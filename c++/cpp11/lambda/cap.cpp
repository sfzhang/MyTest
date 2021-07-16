#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

int g_i = 0;
			
void f()
{
	static int s_i = 0;
	
	auto l = [i = g_i, s = s_i]() mutable {
		return s + i;
	};
	
    g_i = 0;
    s_i = 0;
	cout << l() << endl; // 0

    auto l2 = [=] {
        return g_i + s_i;
    };

    g_i = 10;
    s_i = 20;
	cout << l2() << endl; // 30
}

int main()
{
    f();

    return 0;
}

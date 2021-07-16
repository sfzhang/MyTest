#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    nullptr_t n;

    assert(n == nullptr);

    int *p = nullptr;
    assert(n == p);
    assert(n >= p);
    assert(n <= p);

    char *c = n;
    assert(c == nullptr);

    // error: no post-increment operator for type
    //n++;
    
    // OK, direct-initialization!
    bool b{nullptr};

    // error: converting to ‘bool’ from ‘nullptr_t’ {aka ‘std::nullptr_t’} requires direct-initialization
    //bool bb = nullptr; 

    // error: converting to ‘bool’ from ‘nullptr_t’ {aka ‘std::nullptr_t’} requires direct-initialization
    // if (!n) {
    // OK, direct-initialization!
    if (n) {
        cout << "null" << endl;
    }

    assert(sizeof(nullptr_t) == sizeof(void *));

    cout << "&n: " << &n << endl;

    const auto &&n_ptr = nullptr;
    cout << "&nullptr: " << &n_ptr << endl;

    return 0;
}

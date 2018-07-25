#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <iterator>

using namespace std;

int main()
{
    const string s[] = { "string", "1", "test", "..." };
    const auto p = get_temporary_buffer<string>(4);

    copy(s, s + p.second,
         raw_storage_iterator<string*, string>(p.first));

    copy(p.first, p.first + p.second,
         ostream_iterator<string>{cout, "\n"});

    for_each(p.first, p.first + p.second, [](std::string &e) {
            e.~basic_string<char>();
        });

    return_temporary_buffer(p.first);

    return 0;
}

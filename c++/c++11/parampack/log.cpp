#include <iostream>
#include <string>

using namespace std;

template <typename T>
void log(ostream &out, const T &t)
{
    out << t;
}

template <typename T, typename... R>
void log(ostream &out, const T &t, const R&... rest)
{
    out << t << " ";
    log(out, rest...);
}

#define LOG(level, ...) \
    do { \
        log(cout, level, __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
        cout << endl; \
    } while (0)

#define DLOG(...) LOG('D', ##__VA_ARGS__)
#define ILOG(...) LOG('I', ##__VA_ARGS__)
#define WLOG(...) LOG('W', ##__VA_ARGS__)
#define ELOG(...) LOG('E', ##__VA_ARGS__)
#define FLOG(...) LOG('F', ##__VA_ARGS__)

struct S {
};

ostream &operator<<(ostream &out, const S &s)
{
    return out << "struct s";
}

int main()
{
    log(cout, "this is test");
    cout << endl;

    int i = 0;
    double d = 1.0f;
    string s = "string";

    log(cout, "multi", s, d, s);
    cout << endl;

    DLOG("This is debug log");

    ILOG(i);

    WLOG(s, d, i);

    ELOG(s, d);

    FLOG(S{});

    return 0;
}

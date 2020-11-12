#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <stdarg.h>
#include <cstring>

using namespace std;

#define DUMP(fmt, ...) \
    do { \
        Stream sstrm; \
        sstrm.print(fmt, __VA_ARGS__); \
    } while (0)

class Stream {

public:

    char *print(const char *fmt, ...)
    {

		int size = 0;
        char *p = NULL;
        va_list ap;

        /* Determine required size */

        va_start(ap, fmt);
        size = vsnprintf(p, size, fmt, ap);
        va_end(ap);

        if (size < 0)
        	return NULL;

        size++;             /* For '\0' */
        p = reinterpret_cast<char *>(malloc(size));
        if (p == NULL)
        	return NULL;

        va_start(ap, fmt);
        size = vsnprintf(p, size, fmt, ap);
        va_end(ap);

        if (size < 0) {
        	free(p);
            return NULL;
        }

        cout << p << endl;

        return p;
    }

};

class Str {
public:

    Str() {
        cout << "constructor" << endl;
    }

    ~Str() {
        cout << "destructor" << endl;
    }

    string str()
    {
        return string("test");
    }

    const char * cstr()
    {
        return "a";
    }

};

struct C {

    Str str()
    {
        return Str();
    }
};

int main()
{
    DUMP("%s", C().str().cstr());

//    char buf[1024];

//    printf("%s\n", C().str().cstr());

    return 0;
}

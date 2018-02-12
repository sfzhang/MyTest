#include <string>
#include <vector>
#include <sstream>
#include <cstdio>

void split(const std::string &str, char delim, std::vector<std::string> &value)
{
    std::stringstream sstrm(str);
    std::string item;
    while (getline(sstrm, item, delim)) {
        value.push_back(item);
    }   
}

#include <iostream>
#include <string>

using namespace std;

/**
 * Get message from socket
 *
 * @return The message
 */
string getSocketMessage()
{
    // 1. create socket
    // 2. connect to server
    // 3. request message from server
    // 4. receive message

    return string();
}

bool parse()
{
    string msg = getSocketMessage();

    /* invalid message */
    if (msg.length() < 4) {
        return false;
    }

    /* check prefix */
    if (msg.compare(0, 4, "pref") != 0) {
        return false;
    }

    /* check body */

    return true;
}

int main()
{
    parse();

    return 0;
}

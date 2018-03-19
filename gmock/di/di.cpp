/**
 * @file Dependency injection
 *
 * @author sfzhang
 * @date 2018-3-12
 */

class Interface {
public:
    virtual ~Interface() {}
    virtual work() = 0;
};

class Client {
public:

    Client(Interface *interface): m_interface(interface) {};

    void setInterface(Interface *interface)
    {
        m_interface = interface;
    }

    void action(Interface *interface)
    {
        interface->work();
    }

    void action()
    {
        Interface *interface = make(); // Dependency
        interface->work();
    }

};

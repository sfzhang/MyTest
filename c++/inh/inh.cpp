#include <iostream>

using namespace std;

class Base {

public:

    void public_func()
    {
        cout << "Base::public func" << endl;
    }

protected:

    void protected_func()
    {
        cout << "Base::protected func" << endl;
    }

private:

    void private_func()
    {
        cout << "Base::private func" << endl;
    }

};

class DerivedPublic: public Base {

public:

    void access()
    {
        public_func();
        protected_func();

        // private can' be accessed
        //private_func();
    }

};

class DerivedProtected: protected Base {

public:

    void access()
    {
        public_func();
        protected_func();

        // private can' be accessed
        //private_func();
    }

};

class DerivedPrivate: private Base {

public:

    void access()
    {
        public_func();
        protected_func();

        // private can' be accessed
        //private_func();
    }

};


int main()
{
    DerivedPublic d_pub;
    Base *b = &d_pub;

    DerivedProtected d_pro;
    // ‘Base’ is an inaccessible base of ‘DerivedProtected’
    // b = &d_pro;

    DerivedPrivate d_pri;
    // ‘Base’ is an inaccessible base of ‘DerivedProtected’
    //b = &d_pri;

    return 0;
}

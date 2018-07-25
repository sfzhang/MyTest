#include <iostream>

using namespace std;

template <typename N>
struct Node_Base {
    N *left;
    N *right;

    Node_Base(): left(nullptr), right(nullptr) {}
};

template <typename T>
struct Node: Node_Base<Node<T>> {
    T m_t;
    Node(T t = T{}): m_t(t) {}
};

int main()
{
    Node<double> n;

    return 0;
}

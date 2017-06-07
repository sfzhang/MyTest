#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <iostream>

using namespace std;
using namespace boost;
using namespace boost::bimaps;

int main()
{
    typedef bimap<
        unordered_set_of< int >,
        unordered_set_of< string >,
        with_info< string >
    > bm;

    bm m;

    m.insert(bm::value_type(1, "zsf", "zhangshengfa"));
    m.insert(bm::value_type(2, "hly", "hly"));
    m.insert(bm::value_type(3, "zck", "zck"));
    m.insert(bm::value_type(4, "zh", "zh"));

    bm::right_iterator it = m.right.find("zsf");
    assert(it != m.right.end());
    cout << it->first << " " << it->info << endl;

    cout << m.size() << endl;

    for (bm::left_iterator it = m.left.begin();
         it != m.left.end(); ) {
        it = m.left.erase(it);
        if (it != m.left.end()) {
            cout << it->first << "->" << it->second << ":" << it->info << endl;
        }
    }
    cout << m.size() << endl;

    string n = "hly";
    const std::string &name = n;
    it = m.right.find(name);

    return 0;
}

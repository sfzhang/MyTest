#include <iostream>

using namespace std;

int main()
{
    double xymin = -5;
    double xymax = 5;

    double thickness = 3;
    double spacing = 2;
    double epsilon = 0.3;

    size_t ext_count = 2;
    size_t span = 100;

    double distance = thickness + spacing;
    double tmp = (xymax - xymin) / distance;
    size_t count = tmp;
    if (0 == count) {
        count = 1;
    }
    else if ((tmp - count) >= epsilon) {
        count += 1;
    }

    count += ext_count * 2;

    cout << "xymin: " << xymin << "\n"
         << "xymax: " << xymax << "\n"
         << "thickness: " << thickness << "\n"
         << "spacing: " << spacing << "\n"
         << "epsilon: " << epsilon << "\n"
         << "ext_count: " << ext_count << "\n"
         << "span: " << span << "\n"
         << "distance: " << distance << "\n"
         << "tmp: " << tmp << "\n"
         << "count: " << count << endl;

    double xmin = (xymax + xymin - distance * (count - 1)) / 2;
    double xmax = xmin + span;

    cout << "xmin: " << xmin << "; xmax: " << xmax << endl;

    for (size_t i = 0; i < count; i++) {
        cout << xmin + i * distance << " ";
    }
    cout << endl;

    return 0;
}

#include <iostream>
#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;

void test()
{
    // m * 3
    mat ele = { { -1, 0, -3 },
                {  0, 0, -3 },
                {  1, 0, -3 } };

    cout << "ele:\n" << ele << endl;

    // 1 * 3
    rowvec focus = { 0, 0, 3 };

    cout << "focus:\n" << focus << endl;

    // m * 3
    auto acoustic_path = focus - ele.each_row();
    cout << "acoustic_path:\n" << acoustic_path << endl;

    // m * 1
    vec acoustic_length(acoustic_path.n_rows);
    int i = 0;
    acoustic_path.each_row([&](const arma::rowvec &v) {
            acoustic_length(i++) = std::sqrt(v(0) * v(0) + v(1) * v(1) + v(2) * v(2));
            });
    cout << "acoustic_length:\n" << acoustic_length << endl;

    // m * 3
    auto acoustic_nv = acoustic_path;
    i = 0;
    acoustic_nv.each_row([&](arma::rowvec &v) {
            v /= acoustic_length(i++);
            });
    cout << "acoustic_nv:\n" << acoustic_nv << endl;

    // sp_nv: 1 * 3
    rowvec sp_nv = { 0, 0, 1 };

    // sp_pt: 1 * 3
    rowvec sp_pt = { 0, 0, -1 };


    vec dot1(acoustic_path.n_rows);
    i = 0;
    ele.each_row([&](const rowvec &v) {
            dot1(i++) = dot(sp_pt - v, sp_nv);
            });
    cout << "dot1:\n" << dot1 << endl;

    vec dot2(acoustic_nv.n_rows);
    i = 0;
    acoustic_nv.each_row([&](const rowvec &v) {
            dot2(i++) = dot(v, sp_nv);
            });
    cout << "dot2:\n" << dot2 << endl;

    auto t1 = dot1 / dot2;
    cout << "t1:\n" << t1 << endl;

    auto t2 = acoustic_length - t1;
    cout << "t2:\n" << t2 << endl;

    auto t = t1 / 10 + t2 / 20;
    vec phase = t * 2 * M_PI;
    cout << "phase:\n" << phase << endl;

    phase.for_each([](auto &a) {
            a = std::fmod(a, 2 * M_PI);
            });

    cout << "fmod phase:\n" << phase << endl;

    cout << "fmod(0, 2 * M_PI): " << fmod(0, 2 * M_PI) << endl;
    cout << "fmod(M_PI, 2 * M_PI): " << fmod(M_PI, 2 * M_PI) << endl;
    cout << "fmod(2 * M_PI, 2 * M_PI): " << fmod(2 * M_PI, 2 * M_PI) << endl;
    cout << "fmod(2 * M_PI + 1, 2 * M_PI): " << fmod(2 * M_PI + 1, 2 * M_PI) << endl;
}

int main()
{
    test();
    return 0;

    mat m = { { 1, 2, 3, 4 },
              { 5, 6, 7, 8 } };

    mat n = m;

    cout << boolalpha
         << all(m == n) << endl;
    return 0;

    vector<double> v = { 1, 2, 3, 4 };

    rowvec r(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        r(i) = v[i];
    }

    for (size_t i = 0; i < r.size(); i++) {
        cout << r[i] << endl;
    }

    return 0;
}

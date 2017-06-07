#include <iostream>
#include <cmath>

using namespace std;

double calcPoint(double t1, double t2, double interval)
{
    if (interval <= 0){
        return 0;
    }
    if (t1 < 43 && t2 < 43){
        return 0;
    }
    if ( fabs(t1 - t2) < 0.01 ){
        if (t1 > t2){
            t1 = t2 + 0.01;
        }
        else{
            t2 = t1 + 0.01;
        }
    }
    double a = (t2 - t1)/interval;
    double b = t1;
    double tT = (43-b) / a;

    double dose = 0;
    if (t1 >= 43 && t2 >= 43){
        dose = (pow(2, (a * interval + b) - 43) - pow(2, b - 43)) / (a * std::log(2));
    }
    else if (t1 >= 43 && t2 <= 43){
        dose = calcPoint(t1, 43, tT);
    }
    else if (t1 <= 43 && t2 >= 43){
        dose = calcPoint(43, t2, interval - tT);
    }
    return dose;
}

int main()
{
    cout << calcPoint(43, 43, 100) << endl;
    return 0;
}


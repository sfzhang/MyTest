#include <pub/geometry.h>
#include <probemovement/chestmovecalc.h>
#include <log/log.h>
#include <iostream>
#include <armadillo>
#include <cassert>
#include <string>

using namespace std;
using namespace arma;
using namespace hifu;
using namespace hifu::pub;
using namespace hifu::probemovement;
using namespace hifu::position;

void test_chectmove()
{
    ChestMoveCalc cmc;
    Point3dDouble v;
    ProbeMoveResult ret = cmc.calcMoveScale(Point3dDouble(1, 1, 1), v, false);
    cout << static_cast<int>(ret) << endl;
    cout << "v: " << v.x() << ", " << v.y() << ", " << v.z() << endl;

    TransformationMatrix m;
    cmc.getMoveAdjustPara(m);
    cout << "m: \n" << m << endl;

    cout << "test { 2, 2, 2 }: \n" << rowvec{2, 2, 2, 1} * m << endl;
    cout << "test { 0, 0, 0 }: \n" << rowvec{0, 0, 0, 1} * m << endl;
    cout << "test { 1, 1, 1 }: \n" << rowvec{1, 1, 1, 1} * m << endl;
    cout << "----------------" << endl;
}

/* Test transform */
void test_transform()
{
    mat m = transform(Point3dDouble(1, 1, 1), Point3dDouble(1, 1, 1));
    cout << m << endl;

    cout << "test { 2, 2, 2 }: \n" << m * vec{2, 2, 2, 1} << endl;
    cout << "test { 0, 0, 0 }: \n" << m * vec{0, 0, 0, 1} << endl;
    cout << "test { 1, 1, 1 }: \n" << m * vec{1, 1, 1, 1} << endl;

    /*
    vec v = { 1, 1, 1, 1 };
    cout << "------\n" <<  v << ":\n" << m * v << endl;

    v = { -3, -3, -1, 1 };
    cout << "------\n" <<  v << ":\n" << m * v << endl;

    v = { 7, 7, 4, 1 };
    cout << "------\n" <<  v << ":\n" << m * v << endl;

    v = { 3, -1, 1, 1 };
    cout << "------\n" <<  v << ":\n" << m * v << endl;

    v = { 1.4472, 1, 0.1056, 1 };
    cout << "------\n" <<  v << ":\n" << m * v << endl;

    v = { 2.7888, 1, -2.4976, 1 };
    cout << "------\n" <<  v << ":\n" << m * v << endl;

    v = { 0.4037, 1.7454, 0.7019, 1 };
    cout << "------\n" <<  v << ":\n" << m * v << endl;

    v = { -4.963, 8.454, -1.981, 1 };
    cout << "------\n" <<  v << ":\n" << m * v << endl;

    m = transform(Point3dDouble(-1, -2, -3), Point3dDouble(0, -1, 0));
    cout << m << endl;

    v = { -1, 8, -3, 1 };
    cout << "------\n" <<  v << ":\n" << m * v << endl;

    v = { 0, -2, -3, 1 };
    cout << "------\n" <<  v << ":\n" << m * v << endl;

    v = { -1, -2, -6, 1 };
    cout << "------\n" <<  v << ":\n" << m * v << endl;
    */
}

void test_intersect_cylinder()
{
    assert(!intersect(StdCylinder{1, 10}, Line{{0, 0, 10.1}, {0, 0, 10.2}}));
    assert(!intersect(StdCylinder{1, 10}, Line{{0, 0, -10.1}, {0, 0, -10.2}}));
    assert(!intersect(StdCylinder{1, 10}, Line{{1, 1, 1}, {1, 1, -2}}));
    assert(!intersect(StdCylinder{1, 10}, Line{{1, 1, 1}, {2, 2, 2}}));

    assert(intersect(StdCylinder{1, 10}, Line{{1, 1, 0}, {-1, 1, 0}}));

    assert(!intersect(StdCylinder{1, 10}, Line{{1, 1, 0}, {-1, -1, 10000}}));
    assert(!intersect(StdCylinder{1, 10}, Line{{0, 10, 0}, {0, 0, 10000}}));

    assert(!intersect(StdCylinder{1, 10}, Line{{1, 1, 0}, {1, 1, 10000}}));
    assert(!intersect(StdCylinder{1, 10}, Line{{1, 1, 0}, {2, 2, 0}}));

    assert(intersect(StdCylinder{1, 10}, Line{{1 / sqrt(2), 1 / sqrt(2), 0}, {1, 1, 2}}));
    assert(intersect(StdCylinder{1, 10}, Line{{1 / sqrt(2), 1 / sqrt(2), 0}, {1, 1, 2}}));

    assert(intersect(StdCylinder{1, 10}, Line{{0, 0, 5}, {0, 0, 5}}));
    assert(intersect(StdCylinder{1, 10}, Line{{0, 1, -5}, {2, 2, -10}}));

    assert(intersect(StdCylinder{1, 10}, Line{{0, 1, -5}, {2, 2, -10}}));
    assert(intersect(StdCylinder{1, 10}, Line{{1, 1, 5}, {-2, -2, 5}}));
    assert(intersect(StdCylinder{1, 10}, Line{{1, 1, 5}, {-2, 1, 5}}));

    assert(intersect(StdCylinder{1, 10}, Line{{0, 0, 5}, {0, 2, 0}}));
}

void test_intersect_cone()
{
    assert(0 == intersect(StdCone{0.5, 16, -12}, Line{{0, 0, 16.01}, {0, 0, 26}}));
    assert(0 == intersect(StdCone{0.5, 16, -12}, Line{{0, 0, -12.0001}, {0, 0, -26}}));

    assert(0 == intersect(StdCone{0.5, 16, -12}, Line{{1, 1, 0}, {-2, 1, 0}}));
    assert(0 == intersect(StdCone{0.5, 16, -12}, Line{{0, 3.86, -2}, {0, 3.86, 2}}));
    assert(0 == intersect(StdCone{0.5, 16, -12}, Line{{0, 4, 0}, {0, 4 + 2 * sqrt(3), 2}}));

    assert(1 == intersect(StdCone{0.5, 16, -12}, Line{{0, -1, 0}, {0, 1, 0}}));

    assert(-1 == intersect(StdCone{0.5, 16, -12}, Line{{0, -1, -1}, {0, 1, -1}}));
    assert(1 == intersect(StdCone{0.5, 16, -12}, Line{{0, -1, 2}, {0, 1, 2}}));

    assert(2 == intersect(StdCone{0.5, 16, -12}, Line{{0, 1, -20}, {0, 1, 20}}));

    assert(1 == intersect(StdCone{0.5, 16, -12}, Line{{0, 0, 1}, {0, sqrt(3), 0}}));

    assert(1 == intersect(StdCone{0.5, 16, -12}, Line{{0, 0, 1}, {0, sqrt(3) / 2, 0}}));

    assert(-1 == intersect(StdCone{0.5, 16, -12}, Line{{0, 0, -2}, {0, -2 * sqrt(3), 0}}));

    assert(-1 == intersect(StdCone{0.5, 16, -12}, Line{{0, 0, -2}, {0, -sqrt(3), 0}}));

    assert(-1 == intersect(StdCone{0.5, 16, -12}, Line{{0, 0, -2}, {0, -4 * sqrt(3), 0}}));

    assert(2 == intersect(StdCone{0.5, 16, -12}, Line{{0, 0, -8}, {0, -20 * sqrt(3) / 3, 12}}));

    assert(2 == intersect(StdCone{0.5, 16, -12}, Line{{0, 0, 20}, {0, 0, -40}}));

    assert(0 == intersect(StdCone{0.5, 16, -12}, Line{{0, 6, 2}, {0, 18, 4}}));

    assert(-1 == intersect(StdCone{0.5, 16, -12}, Line{{0, 0, -4}, {0, 1, -8}}));

    assert(-1 == intersect(StdCone{0.5, 16, -12}, Line{{0, 100, -4}, {0, -90, -5}}));

    assert(0 == intersect(StdCone{0.5, 16, -12}, Line{{0, 10, -4}, {0, 10, 5}}));

    assert(1 == intersect(StdCone{0.5, 16, -12}, Line{{0, 1, 16}, {0, 10, 25}}));

    assert(1 == intersect(StdCone{0.5, 16, -12}, Line{{0, 0, 0}, {0, 0, 0}}));

    assert(1 == intersect(StdCone{0.5, 16, -12}, Line{{0, 0, 1}, {0, 0, 1}}));

    assert(-1 == intersect(StdCone{0.5, 16, -12}, Line{{0, -1, -1}, {0, -1, -1}}));

    assert(-1 == intersect(StdCone{0.5, 16, -12}, Line{{0, 4 * sqrt(3), -4}, {1, 4 * sqrt(3), -4}}));

    assert(0 == intersect(StdCone{0.5, 16, -12}, Line{{4, 0, 0}, {8, 0, 4 / sqrt(3)}}));

    assert(2 == intersect(StdCone{0.5, 16, -12}, Line{{4 * sqrt(3), 0, 4}, {-4 * sqrt(3), 0, -4}}));

    assert(1 == intersect(StdCone{0.5, 16, -12}, Line{{4 * sqrt(3), 0, 4}, {2 * sqrt(3), 0, 2}}));

    assert(-1 == intersect(StdCone{0.5, 16, -12}, Line{{-100 * sqrt(3), 0, -100}, {-2 * sqrt(3), 0, -2}}));

    assert(2 == intersect(StdCone{0.5, 16, -12}, Line{{1, 1, 1}, {-1, -1, -1}}));
}

void test_distance()
{
    cout << "distance: " << pub::distance(Point3dDouble{0, 0, 0},
                                          Points3dDoubleList{{0, -4, -4}, {0, 2, -4}, {0, 2, 1}, {0, -1, 1}}) << endl;

    cout << "distance: " << pub::distance(Point3dDouble{0, 0, 0},
                                          Points3dDoubleList{{0, 0, 1}, {0, 1, 0}, {0, 1, -1}}) << endl;

    cout << "distance: " << pub::distance(Point3dDouble{0, 0, 0},
                                          Points3dDoubleList{{0, 1, 1}, {0, 10, 10}, {0, 10, -10}}) << endl;
}

int main()
{
	string app_name = "test_geometry";

	/* Initialize log4cplus */
    if (!hifu::log::initialize(app_name, std::string())) {
        return -1; 
    }   

    if (!hifu::log::setupLogger(app_name, "DEBUG", "./g.log")) {
        return -1; 
    }

    test_chectmove();

    test_transform();

    //test_intersect_cylinder();
    
    //test_intersect_cone();

    //test_distance();

    return 0;
}

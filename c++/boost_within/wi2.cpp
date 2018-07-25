    #include <iostream>
    #include <boost/geometry/algorithms/intersection.hpp>
    #include <boost/version.hpp>
    #include <boost/geometry.hpp>
    #include <boost/geometry/geometries/point_xy.hpp>
    #include <boost/geometry/geometries/ring.hpp>
    #include <boost/geometry/geometries/polygon.hpp>
    
    using namespace std;
    using namespace boost;
    using namespace boost::geometry;
    
    int main()
    {
        using Point = boost::geometry::model::d2::point_xy<double>;
        using Polygon = boost::geometry::model::polygon<Point>;
        using Ring = boost::geometry::model::ring<Point>;
    
        Ring outer;
        append(outer, Point(1, 1));
        append(outer, Point(1, 0));
        append(outer, Point(0, 0));
        append(outer, Point(0, 1));
        append(outer, Point(1, 0));
    
        Polygon polygon;
        polygon.outer() = outer;
        correct(polygon);
    
        Ring ring;
        append(ring, Point(1, 0.1));
        append(ring, Point(1, -1));
        append(ring, Point(0, -1));
        append(ring, Point(0, 0.1));
        append(ring, Point(1, 0.1));
    
        cout << boolalpha
             << within(polygon, ring) << endl /* should return false */
             << covered_by(polygon, ring) << endl; /* should retrurn false */
    
        return 0;
    }

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
        append(outer, Point(-6.46720129179205, 15.61591992211971));
        append(outer, Point(-3.617204647384145, 15.61591992211971));
        append(outer, Point(-3.617204647384145, 7.615919922119708));
        append(outer, Point(-6.46720129179205, 7.615919922119708));
        append(outer, Point(-6.46720129179205, 15.61591992211971));
    
        Polygon polygon;
        polygon.outer() = outer;
        correct(polygon);
    
        Ring ring;
        append(ring, Point(-3.542202969588097, 7.615919922119709));
        /*
        append(ring, Point(-3.542202969588097, 6.81591992211971));
        append(ring, Point(-3.542202969588097, 6.015919922119708));
        append(ring, Point(-3.542202969588097, 5.215919922119708));
        append(ring, Point(-3.542202969588097, 4.415919922119708));
        append(ring, Point(-3.542202969588097, 3.615919922119708));
        append(ring, Point(-3.542202969588097, 2.815919922119709));
        append(ring, Point(-3.542202969588097, 2.015919922119709));
        append(ring, Point(-3.542202969588097, 1.215919922119709));
        append(ring, Point(-3.542202969588097, 0.4159199221197081));
        */
        append(ring, Point(-3.542202969588097, -0.3840800778802915));
        append(ring, Point(-6.542202969588097, -0.3840800778802916));
        /*
        append(ring, Point(-6.542202969588097, 0.415919922119708));
        append(ring, Point(-6.542202969588097, 1.215919922119709));
        append(ring, Point(-6.542202969588097, 2.015919922119709));
        append(ring, Point(-6.542202969588097, 2.815919922119709));
        append(ring, Point(-6.542202969588097, 3.615919922119708));
        append(ring, Point(-6.542202969588096, 4.41591992211971));
        append(ring, Point(-6.542202969588097, 5.215919922119709));
        append(ring, Point(-6.542202969588097, 6.015919922119709));
        append(ring, Point(-6.542202969588097, 6.815919922119708));
        */
        append(ring, Point(-6.542202969588097, 7.615919922119708));
        append(ring, Point(-3.542202969588097, 7.615919922119709));
        correct(ring);
    
        cout << boolalpha
             << within(polygon, ring) << endl /* should return false */
             << within(polygon, ring) << endl /* should return false */
             << covered_by(polygon, ring) << endl; /* should retrurn false */


    
        return 0;
    }

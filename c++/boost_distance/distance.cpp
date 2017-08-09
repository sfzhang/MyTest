#include <iostream>
#include <list>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/multi/geometries/multi_point.hpp>
#include <boost/geometry/multi/geometries/multi_polygon.hpp>

#include <boost/geometry/io/wkt/wkt.hpp>

#include <boost/foreach.hpp>

int main()
{
    typedef boost::geometry::model::d2::point_xy<double> point_type;
    typedef boost::geometry::model::polygon<point_type> polygon_type;
    typedef boost::geometry::model::linestring<point_type> linestring_type;
    typedef boost::geometry::model::multi_point<point_type> multi_point_type;

    typedef boost::geometry::model::segment<point_type> segment_type;

    point_type p(0, 0);
    segment_type s(point_type(1, 2), point_type(2, 2));
    std::cout << "distance: (1, 2) => (2, 2): " << boost::geometry::distance(p, s) << std::endl;

    segment_type s1(point_type(-1, 2), point_type(2, 2));
    std::cout << "distance: (-1, 2) => (2, 2): " << boost::geometry::distance(p, s1) << std::endl;

    segment_type s2(point_type(-1, 2), point_type(-2, 2));
    std::cout << "distance: (-1, 2) => (-2, 2): " << boost::geometry::distance(p, s2) << std::endl;



/*
    point_type p(1,2);
    polygon_type poly;
    linestring_type line;
    multi_point_type mp;

    boost::geometry::read_wkt(
        "POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2,3.7 1.6,3.4 2,4.1 3,5.3 2.6,5.4 1.2,4.9 0.8,2.9 0.7,2 1.3)"
            "(4.0 2.0, 4.2 1.4, 4.8 1.9, 4.4 2.2, 4.0 2.0))", poly);
    line.push_back(point_type(0,0));
    line.push_back(point_type(0,3));
    mp.push_back(point_type(0,0));
    mp.push_back(point_type(3,3));

    std::cout
        << "Point-Poly: " << boost::geometry::distance(p, poly) << std::endl
        << "Point-Line: " << boost::geometry::distance(p, line) << std::endl
        << "Point-MultiPoint: " << boost::geometry::distance(p, mp) << std::endl;
        */

    return 0;
}

#ifndef CONVEX_HULL_HPP
#define CONVEX_HULL_HPP

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
namespace bg = boost::geometry;

typedef bg::model::d2::point_xy<double> point_2d;
typedef bg::model::multi_point<point_2d> mpoint_t;
typedef bg::model::polygon<point_2d> polygon_t;


polygon_t convex_hull(mpoint_t points);


#endif
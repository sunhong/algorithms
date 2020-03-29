#include <cmath>
#include "convex_hull.hpp"

const double ESP = 1e-8;

/*
 * The return value represents the order of points
 * Positive - a,b,c are in counter-clockwise order
 * Zero - a,b,c are on the same line
 * Negative - a,b,c are in clockwise order
*/
double cross_product(const point_2d& a,const point_2d& b,const point_2d& c)
{
	return (c.y()-a.y())*(b.x()-a.x())-(b.y()-a.y())*(c.x()-a.x());
}
/*
 * compare two points by y coordinates
 * with the same y values, compare x coordinates
*/
bool cmp_point_2d(const point_2d& a,const point_2d& b)
{
	if (a.y()<b.y()) return true;
	if (std::fabs(a.y()-b.y())<ESP && a.x()<b.x()) return true;
	return false;
}
/*
 * check if two points are the same 
 */
bool same(const point_2d& a,const point_2d& b)
{
	return std::fabs(a.x()-b.x())<ESP && std::fabs(a.y()-b.y())<ESP;
}
/*
 * remove duplicated points
 */
void compress(mpoint_t& points)
{
	sort(points.begin(), points.end(), cmp_point_2d);
	int N = bg::num_points(points);
	int idx = 1;
	for (int i=1;i<N;i++)
	{
		if (!same(points[i],points[i-1]))
		{
			points[idx].x(points[i].x());
			points[idx].y(points[i].y());
			idx++;
		}
	}
	points.resize(idx);
}
polygon_t convex_hull(mpoint_t points)
{
	mpoint_t v;	//temporarily store points on convex hull
	compress(points);
	int N = bg::num_points(points);
	//build right chain of convex hull
	for (int i=0;i<N;i++)
	{
		while (v.size()>1 && cross_product(v[v.size()-2],v.back(),points[i])<0)
		{
			v.pop_back();
		}
		v.push_back(points[i]);
	}
	//build left chain of convex hull
	for (int i=N-2;i>=0;i--)
	{
		while (v.size()>1 && cross_product(v[v.size()-2],v.back(),points[i])<0)
		{
			v.pop_back();
		}
		if (i>0)
		{
			v.push_back(points[i]);
		}
	}
	polygon_t hull;
	for (point_2d p : v)
	{
		bg::append(hull, p);
	}
	return hull;
}

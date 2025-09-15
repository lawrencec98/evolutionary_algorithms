#ifndef _FITNESS_HPP_
#define _FITNESS_HPP_

/*  Will use the Boost implementation of Weiler-Atherton clipping algorithm to calculate the
    intersection-over-union of two polygons.
*/
#include "Segment.hpp"

#include <opencv2/imgproc.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

typedef boost::geometry::model::d2::point_xy<int> BoostPoint;
typedef boost::geometry::model::polygon<BoostPoint> BoostPolygon;


BoostPolygon MakePolygon(const std::vector<cv::Point>& quad);


double CalculateFitnessScore(Segment* segment, Segment* idealroi);


#endif // _FITNESS_HPP_
#include "Fitness.hpp"

namespace bg = boost::geometry;

using point = bg::model::d2::point_xy<double>;
using box   = bg::model::box<point>;



box toBox(const RectSegment& r)
{
    double left   = r.m_tl_x;
    double top    = r.m_tl_y;
    double right  = r.m_tl_x + r.m_width;
    double bottom = r.m_tl_y + r.m_height;

    return box(point(left, top), point(right, bottom));
}

double IoU(const box& a, const box& b)
{
    if (!bg::intersects(a, b))
        return 0.0;

    box inter;
    bg::intersection(a, b, inter);

    double interArea = bg::area(inter);
    double unionArea = bg::area(a) + bg::area(b) - interArea;

    return (unionArea > 0.0) ? interArea / unionArea : 0.0;
}

double CalculateFitnessScore(const RectSegment& r1, const RectSegment& r2)
{
    box b1 = toBox(r1);
    box b2 = toBox(r2);
    return IoU(b1, b2);
}
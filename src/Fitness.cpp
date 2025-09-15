#include "Fitness.hpp"

BoostPolygon MakePolygon(const std::vector<cv::Point>& quad)
{
    BoostPolygon poly;
    for (const auto& pt : quad)
    {
        boost::geometry::append(poly.outer(), BoostPoint(pt.x, pt.y));
    }

    boost::geometry::append(poly.outer(), BoostPoint(quad[0].x, quad[0].y));

    boost::geometry::correct(poly);
    return poly;
}


double CalculateFitnessScore(Segment* segment, Segment* idealsegment)
{
    BoostPolygon poly1 = MakePolygon(segment->m_vertices);
    BoostPolygon poly2 = MakePolygon(idealsegment->m_vertices);

    double area1 = boost::geometry::area(poly1);
    double area2 = boost::geometry::area(poly2);

    std::vector<BoostPolygon> output;
    boost::geometry::intersection(poly1, poly2, output);

    double interArea = 0.0;
    for (const auto& p : output)
    {
        interArea += boost::geometry::area(p);
    }

    double unionArea = area1 + area2 - interArea;
    std::cout << "area1=" << area1 << " area2=" << area2 << " interArea=" << interArea << " union=" << unionArea << "\n";
    if (unionArea <= 0.0) return 0.0;

    return interArea / unionArea;
}
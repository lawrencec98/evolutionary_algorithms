#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <iostream>
#include <vector>

#include <opencv2/core.hpp>


struct Segment {
    Segment();

    Segment(cv::Point tl, cv::Point tr, cv::Point br, cv::Point bl); // order matters

    ~Segment();

    int MutateSegmentVertices();

    int m_numvertices;
    std::vector<cv::Point> m_vertices; // The 10 points that belong to this segment.
    double m_fitnessScore;
    cv::Scalar m_segcolour; // Colour of segment's vertices. Helps differentiate it from other segments.
};


#endif // SEGMENT_HPP
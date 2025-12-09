#ifndef RECT_SEGMENT_HPP
#define RECT_SEGMENT_HPP

#include <iostream>
#include <vector>

#include <opencv2/core.hpp>


struct RectSegment {
    RectSegment();

    RectSegment(int tl_x, int tl_y, int width, int height);

    ~RectSegment();

    void MutateSegmentVertices();

    int m_tl_x;
    int m_tl_y;
    int m_width;
    int m_height;
    double m_fitnessScore;
    cv::Scalar m_segcolour; // Colour of segment's vertices. Helps differentiate it from other segments.
};


#endif // RECT_SEGMENT_HPP
#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <iostream>
#include <vector>


struct Segment {
    Segment();

    ~Segment();

    float area();
    int m_numvertices;
    std::vector<std::pair<int,int>> m_vertices; // The 10 points that belong to this segment.
    float m_fitnessScore;
    cv::Scalar m_segcolour; // Colour of segment's vertices. Helps differentiate it from other segments.
};


#endif // SEGMENT_HPP
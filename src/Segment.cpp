#include "Globals.hpp"
#include "Segment.hpp"

#include <cstdlib>


Segment::Segment()
    :m_numvertices(SEG_NUM_VERTICES),
     m_vertices(m_numvertices),
     m_fitnessScore(-1),
     m_segcolour(cv::Scalar(rand() % 255, rand() % 255, rand() % 255))
{
    std::vector<cv::Point> randomPts;
    randomPts.reserve(m_numvertices);

    for (int i = 0; i < m_vertices.size(); ++i) {
        int randomNumberX = rand() % IMAGE_WIDTH;
        int randomNumberY = rand() % IMAGE_HEIGHT;

        randomPts.emplace_back(randomNumberX, randomNumberY);
    }

    std::vector<cv::Point> hull;
    if (!randomPts.empty()) 
    {
        cv::convexHull(randomPts, hull, true); // true = clockwise order
    }

    m_vertices = hull;
}


Segment::Segment(cv::Point tl, cv::Point tr, cv::Point bl, cv::Point br)
    :m_numvertices(SEG_NUM_VERTICES),
     m_vertices(m_numvertices),
     m_fitnessScore(-1),
     m_segcolour(cv::Scalar(rand() % 255, rand() % 255, rand() % 255))
{
    m_vertices[0] = tl;
    m_vertices[1] = tr;
    m_vertices[2] = bl;
    m_vertices[3] = br;

    for (const auto& v : m_vertices)
    {
        std::cout << "Ideal segment vertices: " << v << ", ";
    }
}


Segment::~Segment()
{
    cv::destroyAllWindows();
}
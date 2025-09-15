#include "Globals.hpp"
#include "Segment.hpp"

#include <cstdlib>


Segment::Segment()
    :m_numvertices(SEG_NUM_VERTICES),
     m_vertices(m_numvertices),
     m_fitnessScore(-1),
     m_segcolour(cv::Scalar(rand() % 255, rand() % 255, rand() % 255))
{
    for (int i = 0; i < m_vertices.size(); ++i) {
        int randomNumberX = rand() % IMAGE_WIDTH;
        int randomNumberY = rand() % IMAGE_HEIGHT;
        
        cv::Point coords(randomNumberX, randomNumberY);
        m_vertices[i] = coords;
    }
}


Segment::Segment(cv::Point tl, cv::Point tr, cv::Point bl, cv::Point br)
    :m_numvertices(SEG_NUM_VERTICES),
     m_fitnessScore(-1),
     m_segcolour(cv::Scalar(rand() % 255, rand() % 255, rand() % 255))
{
    for (int i = 0; i < m_numvertices; ++i)
    {
        m_vertices.push_back(tl);
        m_vertices.push_back(tr);
        m_vertices.push_back(bl);
        m_vertices.push_back(br);
    }
}


Segment::~Segment()
{
    cv::destroyAllWindows();
}
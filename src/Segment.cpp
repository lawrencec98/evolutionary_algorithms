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
        
        std::pair<int,int> coords(randomNumberX, randomNumberY);
        m_vertices[i] = coords;
    }
}


Segment::~Segment()
{
    cv::destroyAllWindows();
}
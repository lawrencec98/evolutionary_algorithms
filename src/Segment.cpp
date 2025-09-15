#include "Globals.hpp"
#include "Segment.hpp"

#include <cstdlib>


Segment::Segment()
    :m_numvertices(SEG_NUM_VERTICES),
     m_vertices(m_numvertices),
     m_fitnessScore(-1) 
{
    if (m_vertices.size() != SEG_NUM_VERTICES ) 
    {
        std::cerr << "Error, this segment has invalid number of vertices " << m_vertices.size() << std::endl;
    }
    else // randomly generate your vertices
    {
        for (int i = 0; i < m_vertices.size(); ++i) {
            int randomNumberX = rand() % IMAGE_WIDTH;
            int randomNumberY = rand() % IMAGE_HEIGHT;
            
            std::pair<int,int> coords(randomNumberX, randomNumberY);
            m_vertices[i] = coords;
        }
    }

    m_segcolour = cv::Scalar(rand() % 255, rand() % 255, rand() % 255);
}


Segment::~Segment()
{
    cv::destroyAllWindows();
}
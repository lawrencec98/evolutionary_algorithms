#include "Segment.hpp"

#include <cstdlib>

#define IMAGE_WIDTH 1280
#define IMAGE_HEIGHT 720
#define SEG_NUM_VERTICES 100


Segment::Segment() 
    :m_vertices(SEG_NUM_VERTICES) {

    if (m_vertices.size() != SEG_NUM_VERTICES ) {
        std::cerr << "Error, this segment has invalid number of vertices " << m_vertices.size() << std::endl;
    }

    // randomly generate your vector of vertices
    for (int i = 0; i < m_vertices.size(); ++i) {
        int randomNumberX = rand() % IMAGE_WIDTH;
        int randomNumberY = rand() % IMAGE_HEIGHT;
        
        std::pair<int,int> coords(randomNumberX, randomNumberY);
        m_vertices[i] = coords;
    }
}
#include "Segment.hpp"

#include <cstdlib>

#define IMAGE_WIDTH 1280
#define IMAGE_HEIGHT 720


Segment::Segment() {
    // randomly generate your vector of vertices
    for (int i = 0; i < m_vertices.size(); ++i) {
        int randomNumberX = rand() % IMAGE_WIDTH;
        int randomNumberY = rand() % IMAGE_HEIGHT;
        
        std::pair<int,int> coords(randomNumberX, randomNumberY);
        m_vertices[i] = coords;
    }
}
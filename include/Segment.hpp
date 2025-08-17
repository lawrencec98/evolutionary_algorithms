#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <iostream>
#include <vector>


struct Segment {
    Segment();

    std::vector<std::pair<int,int>> m_vertices;
};


#endif // SEGMENT_HPP
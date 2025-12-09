#include "Globals.hpp"
#include "RectSegment.hpp"

#include <cstdlib>


RectSegment::RectSegment()
    : m_fitnessScore(-1),
      m_segcolour(cv::Scalar(rand() % 255, rand() % 255, rand() % 255))
{
    m_tl_x = rand() % IMAGE_WIDTH - 50;
    m_tl_y = rand() % IMAGE_HEIGHT - 30;

    m_width = 50;
    m_height = 30;
}


RectSegment::RectSegment(int x, int y, int width, int height)
    :   m_tl_x(x),
        m_tl_y(y),
        m_width(width),
        m_height(height),
        m_fitnessScore(-1),
        m_segcolour(cv::Scalar(rand() % 255, rand() % 255, rand() % 255))
{

}


RectSegment::~RectSegment()
{
    cv::destroyAllWindows();
}


// int RectSegment::MutateSegmentVertices()
// {
//     // Randomly determine how many vertices get mutated
//     for (int i = 0; i < numVerticesToMutate; ++i)
//     {
//         int toAddX = 0; // determines whether we add or subtract from X-coordinate
//         int toAddY = 0; // determines whether we add or subtract from Y-coordinate

//         float lottery = static_cast<float>(rand()) / RAND_MAX;
//         lottery > 0.5 ? toAddX=1 : toAddX=0;
//         lottery = static_cast<float>(rand()) / RAND_MAX;
//         lottery > 0.5 ? toAddY=1 : toAddY=0;

//         // Mutate x
//         if (toAddX)
//         {
//             int vertexToMutate = rand() % 4;
//             int mutationAmount = rand() % MAX_MUTATION_VARIATION;

//             if (m_vertices[vertexToMutate].x + mutationAmount < IMAGE_WIDTH)
//             {
//                 m_vertices[vertexToMutate].x += mutationAmount;
//             }
//         }
//         else
//         {
//             int vertexToMutate = rand() % 4;
//             int mutationAmount = rand() % MAX_MUTATION_VARIATION;
            
//             if (m_vertices[vertexToMutate].x - mutationAmount > 0)
//             {
//                 m_vertices[vertexToMutate].x -= mutationAmount;
//             }
//         }

//         // Mutate y
//         if (toAddY)
//         {
//             int vertexToMutate = rand() % 4;
//             int mutationAmount = rand() % MAX_MUTATION_VARIATION;
            
//             if (m_vertices[vertexToMutate].y + mutationAmount < IMAGE_HEIGHT)
//             {
//                 m_vertices[vertexToMutate].y += mutationAmount;
//             }
//         }
//         else
//         {
//             int vertexToMutate = rand() % 4;
//             int mutationAmount = rand() % MAX_MUTATION_VARIATION;
            
//             if (m_vertices[vertexToMutate].y - mutationAmount > 0)
//             {
//                 m_vertices[vertexToMutate].y -= mutationAmount;
//             }
//         }
//     }

//     return 0;
// }
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
    std::vector<cv::Point> segPts;
    segPts.reserve(m_numvertices);

    segPts.emplace_back(tl);
    segPts.emplace_back(tr);
    segPts.emplace_back(br);
    segPts.emplace_back(bl);

    std::vector<cv::Point> hull;
    if (!segPts.empty()) 
    {
        cv::convexHull(segPts, hull, true); // true = clockwise order
    }

    m_vertices = hull;

    for (const auto& v : m_vertices)
    {
        std::cout << "Ideal segment vertices: " << v << ", ";
    }
}


Segment::~Segment()
{
    cv::destroyAllWindows();
}


int Segment::MutateSegmentVertices()
{
    // Randomly determine how many vertices get mutated
    int numVerticesToMutate = rand() % 4;

    for (int i = 0; i < numVerticesToMutate; ++i)
    {
        int toAddX = 0; // determines whether we add or subtract from X-coordinate
        int toAddY = 0; // determines whether we add or subtract from Y-coordinate

        float lottery = static_cast<float>(rand()) / RAND_MAX;
        lottery > 0.5 ? toAddX=1 : toAddX=0;
        lottery = static_cast<float>(rand()) / RAND_MAX;
        lottery > 0.5 ? toAddY=1 : toAddY=0;

        // Mutate x
        if (toAddX)
        {
            int vertexToMutate = rand() % 4;
            int mutationAmount = rand() % MAX_MUTATION_VARIATION;

            if (m_vertices[vertexToMutate].x + mutationAmount < IMAGE_WIDTH)
            {
                m_vertices[vertexToMutate].x += mutationAmount;
            }
        }
        else
        {
            int vertexToMutate = rand() % 4;
            int mutationAmount = rand() % MAX_MUTATION_VARIATION;
            
            if (m_vertices[vertexToMutate].x - mutationAmount > 0)
            {
                m_vertices[vertexToMutate].x -= mutationAmount;
            }
        }

        // Mutate y
        if (toAddY)
        {
            int vertexToMutate = rand() % 4;
            int mutationAmount = rand() % MAX_MUTATION_VARIATION;
            
            if (m_vertices[vertexToMutate].y + mutationAmount < IMAGE_HEIGHT)
            {
                m_vertices[vertexToMutate].y += mutationAmount;
            }
        }
        else
        {
            int vertexToMutate = rand() % 4;
            int mutationAmount = rand() % MAX_MUTATION_VARIATION;
            
            if (m_vertices[vertexToMutate].y - mutationAmount > 0)
            {
                m_vertices[vertexToMutate].y -= mutationAmount;
            }
        }
    }

    return 0;
}
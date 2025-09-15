// Evolutionary algorithm will optimize image segmentation accuracy.

// Starting population will be 100 randomly generated Segments.

// Fitness function will be intersection over union of those segments with the ground truth segment.

#include "Globals.hpp"
#include "Fitness.hpp"
#include "Segment.hpp"

#include <vector>


int main() {
    std::cout << "Start of program...\n";

    /* Start the program with a random population of 20 segments. */
    std::vector<Segment> population(POPULATION_SIZE);

    cv::Mat window(IMAGE_HEIGHT,IMAGE_WIDTH, CV_8UC3);

    for (int i = 0; i < POPULATION_SIZE; ++i)
    {
        for (int j = 0; j < population[i].m_numvertices; ++j)
        {
            cv::Point center(population[i].m_vertices[j].first, population[i].m_vertices[j].second);
            cv::circle(window, center, 1, population[i].m_segcolour, 1);
        }
    }
    cv::imshow("window with population", window);
    cv::waitKey(0);

    // for each segment in population:
        // CalculateFitnessScore();
    // Kill the bottom 50 Segments.
    // Reproduce + Mutations.
    // Higher fitness population has higher chance to reproduce.

}
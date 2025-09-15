// Evolutionary algorithm will optimize image segmentation accuracy.

// Starting population will be 100 randomly generated Segments.

// Fitness function will be intersection over union of those segments with the ground truth segment.

#include "Globals.hpp"
#include "Fitness.hpp"
#include "Segment.hpp"

#include <vector>


int main() {
    std::cout << "Start of program...\n";
    srand(static_cast<unsigned>(time(NULL))); // For rand() to randomize properly.

    /* TEMPORARY: Hard code an ideal segment for population to aim for */
    cv::Point idealseg_tl(300,200); // topleft
    cv::Point idealseg_tr(600,200); // topright
    cv::Point idealseg_bl(300,400); // bottomleft
    cv::Point idealseg_br(600,400); // bottomright

    Segment idealseg(idealseg_tl, idealseg_tr, idealseg_bl, idealseg_br);


    /* Start the program with a random population of 20 segments. */
    std::vector<Segment> population(POPULATION_SIZE);

    /* Draw the environment and population */
    cv::Mat window(IMAGE_HEIGHT,IMAGE_WIDTH, CV_8UC3);
    cv::Rect ideal(idealseg_tl, idealseg_br);
    cv::rectangle(window, ideal, cv::Scalar(255,255,255), IDEAL_SEGMENT_THICKNESS);

    /* Do the simulation */
    int iteration = 0;
    while (iteration < NUM_GENERATIONS_TO_SIMULATE)
    {
        /* Display current state of population */
        for (int i = 0; i < POPULATION_SIZE; ++i)
        {
            for (int j = 0; j < population[i].m_numvertices; ++j)
            {
                cv::circle(window, population[i].m_vertices[j], 1, population[i].m_segcolour, SEG_VERTEX_THICKNESS);
            }
        }
        cv::imshow("window with population", window);
        cv::waitKey(0);


        /* Determine fitness scores */
        for (int i = 0; i < POPULATION_SIZE; ++i)
        {
            population[i].m_fitnessScore = CalculateFitnessScore(&population[i], &idealseg);
        }

        /* Cull Stage */

        /* Reproduction Stage */

        /* Mutation Stage */
    }
    

    // for each segment in population:
        // CalculateFitnessScore();
    // Kill the bottom 50 Segments.
    // Reproduce + Mutations.
    // Higher fitness population has higher chance to reproduce.

}
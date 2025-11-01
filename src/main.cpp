// Evolutionary algorithm will optimize image segmentation accuracy.

// Starting population will be 100 randomly generated Segments.

// Fitness function will be intersection over union of those segments with the ground truth segment.

#include "Globals.hpp"
#include "Fitness.hpp"
#include "Segment.hpp"
#include "Queue.hpp"

#include <vector>
#include <algorithm>
#include <thread>


cv::Point idealseg_tl(300,200); // topleft
cv::Point idealseg_tr(600,200); // topright
cv::Point idealseg_bl(300,400); // bottomleft
cv::Point idealseg_br(600,400); // bottomright

Segment idealseg(idealseg_tl, idealseg_tr, idealseg_br, idealseg_bl);
cv::Rect ideal(idealseg_tl, idealseg_br);


void PerformEvolution(std::shared_ptr<std::vector<Segment>> population, std::shared_ptr<queue_t> framebuffer)
{
    /****************************************************************************************************************************/
        /* Determine fitness scores */
        for (int i = 0; i < POPULATION_SIZE; ++i)
        {
            population->at(i).m_fitnessScore = CalculateFitnessScore(&population->at(i), &idealseg);
        }

        /****************************************************************************************************************************/
        /* Cull Stage */
        std::sort(population->begin(), population->end(), [](Segment a, Segment b){return a.m_fitnessScore > b.m_fitnessScore;});

        int numToCull = population->size() * BOTTOM_CULL_PERCENTAGE;

        for (int i = 0; i < numToCull; ++i)
        {
            population->pop_back();
        }

        // for (auto i : population)
        // {
        //     std::cout << i.m_fitnessScore << std::endl;
        // }

        /****************************************************************************************************************************/
        /* Reproduction Stage */
        // Top 20% of population is allowed to reproduce.
        int numAllowedToReproduce = POPULATION_SIZE * TOP_REPRODUCE_PERCENTAGE;
        std::cout << "numalllowedtoreproduce = " << numAllowedToReproduce << std::endl;

        // Reproducing means passing down 50% of genetics from each parent.
        std::sort(population->begin(), population->end(), [](Segment a, Segment b){return a.m_fitnessScore > b.m_fitnessScore;});

        for (int i = 0; i < numAllowedToReproduce / 2; i += 2)
        {
            // Choose two parents at random
            Segment parent1 = population->at(rand() % numAllowedToReproduce);
            Segment parent2 = population->at(rand() % numAllowedToReproduce); // Yes parent can reproduce with itself for now. Will fix.

            cv::Point vertex1 = parent1.m_vertices[rand() % 4];
            cv::Point vertex2 = parent2.m_vertices[rand() % 4];
            cv::Point vertex3 = parent1.m_vertices[rand() % 4];
            cv::Point vertex4 = parent2.m_vertices[rand() % 4];

            /****************************************************************************************************************************/
            /* Mutation Stage */
            int mutate = false;
            float lottery = static_cast<float>(rand()) / RAND_MAX;
            lottery > MUTATION_CHANCE ? mutate=true:mutate=false;

            Segment newSegment(vertex1, vertex2, vertex3, vertex4);

            if (mutate)
            {
                newSegment.MutateSegmentVertices();
            }

            population->push_back(newSegment);
        }
}


void DrawPopulation(std::shared_ptr<std::vector<Segment>> population, std::shared_ptr<queue_t> framebuffer)
{

    while (1)
    {
        cv::Mat background(IMAGE_HEIGHT,IMAGE_WIDTH, CV_8UC3, cv::Scalar(0,0,0));
        cv::rectangle(background, ideal, cv::Scalar(255,255,255), IDEAL_SEGMENT_THICKNESS);
        cv::Mat frame;
        
        /* Main simulation loop */
        int iteration = 0;
        while (iteration < NUM_GENERATIONS_TO_SIMULATE)
        {
            /****************************************************************************************************************************/
            /* Display current state of population */
            frame = background.clone();

            for (int i = 0; i < population->size(); ++i)
            {
                for (int j = 0; j < population->at(i).m_numvertices; ++j)
                {
                    cv::polylines(frame, population->at(i).m_vertices, true, population->at(i).m_segcolour, 1);
                }
            }

            queue_enqueue(framebuffer, &frame);
        }

    }
}


int main() {
    std::cout << "Start of program...\n";
    srand(static_cast<unsigned>(time(NULL))); // For rand() to randomize properly.    

    /* Start the program with a random population of 20 segments. */
    // std::vector<Segment> population(POPULATION_SIZE);
    std::shared_ptr<std::vector<Segment>> population_sp = std::make_shared<std::vector<Segment>>(POPULATION_SIZE);
    std::shared_ptr<queue_t> framebuffer = std::make_shared<queue_t>();
    queue_init(framebuffer);
    
    std::thread drawThread(DrawPopulation, population_sp, framebuffer);
    std::thread evolutionThread(PerformEvolution, population_sp, framebuffer);

    cv::namedWindow("MyWindow", cv::WINDOW_AUTOSIZE);
    cv::Mat* frame;

    while (1)
    {
        frame = (cv::Mat*) queue_pop(framebuffer);
        cv::imshow("MyWindow", *frame);
        char c = (char)cv::waitKey(20); // ~20 fps smooth
        if (c == 27) break;
    }

}
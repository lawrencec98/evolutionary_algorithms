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
#include <semaphore>


cv::Point idealseg_tl(300,200); // topleft
cv::Point idealseg_tr(700,200); // topright
cv::Point idealseg_bl(300,400); // bottomleft
cv::Point idealseg_br(700,400); // bottomright

RectSegment idealseg(300, 200, 400, 200);
cv::Rect ideal(idealseg_tl, idealseg_br);


void PerformEvolution(std::shared_ptr<std::vector<RectSegment>> population, std::shared_ptr<queue_t> framebuffer)
{
    while(1)
    {
        /****************************************************************************************************************************/
        /* Determine fitness scores */
        for (int i = 0; i < POPULATION_SIZE; ++i)
        {
            population->at(i).m_fitnessScore = CalculateFitnessScore(population->at(i), idealseg);
        }

        /****************************************************************************************************************************/
        /* Cull Stage */
        std::sort(population->begin(), population->end(), [](RectSegment a, RectSegment b){return a.m_fitnessScore > b.m_fitnessScore;});

        int numToCull = 5;

        for (int i = 0; i < numToCull; ++i)
        {
            population->pop_back();
        }

        /****************************************************************************************************************************/
        /* Reproduction Stage */
        // Top 20% of population is allowed to reproduce.
        int numAllowedToReproduce = 10;
        std::cout << "numalllowedtoreproduce = " << numAllowedToReproduce << std::endl;

        // Reproducing means passing down 50% of genetics from each parent.
        std::sort(population->begin(), population->end(), [](RectSegment a, RectSegment b){return a.m_fitnessScore > b.m_fitnessScore;});

        for (int i = 0; i < numAllowedToReproduce / 2; i += 2)
        {
            // Choose two parents at random
            RectSegment parent1 = population->at(rand() % numAllowedToReproduce);
            RectSegment parent2 = population->at(rand() % numAllowedToReproduce); // Yes parent can reproduce with itself for now. Will fix.

            int x = parent1.m_tl_x;
            int y = parent2.m_tl_y;
            int width = parent1.m_width;
            int height = parent2.m_height;

            /****************************************************************************************************************************/
            /* Mutation Stage */
            int mutate = false;
            float lottery = static_cast<float>(rand()) / RAND_MAX;
            lottery > MUTATION_CHANCE ? mutate=true:mutate=false;

            RectSegment newSegment(x,y,width,height);

            if (mutate)
            {
                newSegment.MutateSegmentVertices();
            }

            population->push_back(newSegment);
        }
    }
}


void DrawPopulation(std::shared_ptr<std::vector<RectSegment>> population, std::shared_ptr<queue_t> framebuffer)
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
                cv::rectangle(frame, cv::Point(population->at(i).m_tl_x, population->at(i).m_tl_y), cv::Point(population->at(i).m_tl_x + population->at(i).m_width, population->at(i).m_tl_x + population->at(i).m_height), population->at(i).m_segcolour, 2);
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
    std::shared_ptr<std::vector<RectSegment>> population_sp = std::make_shared<std::vector<RectSegment>>(POPULATION_SIZE);
    std::shared_ptr<queue_t> framebuffer = std::make_shared<queue_t>();
    queue_init(framebuffer);
    
    std::thread drawThread(DrawPopulation, population_sp, framebuffer);
    std::thread evolutionThread(PerformEvolution, population_sp, framebuffer);

    cv::namedWindow("MyWindow", cv::WINDOW_AUTOSIZE);
    cv::Mat* frame;

    while (1)
    {
        if (!queue_isempty(framebuffer))
        {
            frame = (cv::Mat*) queue_pop(framebuffer);   
        }

        cv::imshow("MyWindow", *frame); 
        char c = (char)cv::waitKey(50); // ~20 fps smooth
        if (c == 27) break;
    }

}
// Evolutionary algorithm will optimize image segmentation accuracy.

// Starting population will be 100 randomly generated Segments.

// Fitness function will be intersection over union of those segments with the ground truth segment.


#include "Segment.hpp"

#include <vector>


int main() {
    std::cout << "Start of program...\n";

    // Start the program with 100 randomly constructed Segments.
    std::vector<Segment> population(100);

    // Run the fitness function on the population.
    // Kill the bottom 50 Segments.
    // Reproduce + Mutations.
    // Higher fitness population has higher chance to reproduce.

}
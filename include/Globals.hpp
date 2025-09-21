#ifndef _GLOBALS_HPP_
#define _GLOBALS_HPP_

// Generic to entire program
#define IMAGE_WIDTH 1280
#define IMAGE_HEIGHT 720
#define POPULATION_SIZE 50
#define NUM_GENERATIONS_TO_SIMULATE 1000
#define IDEAL_SEGMENT_THICKNESS 0.1
#define MUTATION_CHANCE 0.05
#define BOTTOM_CULL_PERCENTAGE 0.2
#define TOP_REPRODUCE_PERCENTAGE 0.4

// Specific to Segments
#define SEG_NUM_VERTICES 4
#define SEG_VERTEX_THICKNESS 3
#define MAX_MUTATION_VARIATION 30 //in pixels


#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>


#endif // _GLOBALS_HPP_
cmake_minimum_required(VERSION 3.12)
project(evolutionary_algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(eaprog
    src/main.cpp
    src/Segment.cpp
)

# --- Find OpenCV ---
set(OpenCV_DIR /home/lawrence/libraries/opencv4/lib/cmake/opencv4)
find_package(OpenCV REQUIRED)

# --- Find Boost ---
find_package(Boost REQUIRED COMPONENTS filesystem system)

# --- Includes ---
target_include_directories(eaprog PRIVATE
    include
    ${OpenCV_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

# --- Libraries ---
target_link_libraries(eaprog PRIVATE
    ${OpenCV_LIBS}
    Boost::filesystem
    Boost::system
)

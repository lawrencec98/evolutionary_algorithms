cmake_minimum_required(VERSION 3.12)

project(evolutionary_algorithms)

add_executable(eaprog src/main.cpp)

target_include_directories(eaprog PRIVATE include)
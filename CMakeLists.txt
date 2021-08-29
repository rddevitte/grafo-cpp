cmake_minimum_required(VERSION 3.16)

project(grafo-cpp VERSION 0.1
                  DESCRIPTION "Grafo em C++"
                  LANGUAGES CXX)

add_executable(grafo-cpp src/main.cpp)

target_include_directories(grafo-cpp PUBLIC include)

target_compile_options(grafo-cpp PUBLIC --verbose -Wall -Wextra -Werror -Wpedantic -g)
target_compile_features(grafo-cpp PUBLIC cxx_std_11)

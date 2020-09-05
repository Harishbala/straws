cmake_minimum_required(VERSION 3.5)

project(graph_lib LANGUAGES CXX)

set(SRC graph_test.cpp)
set(INC graph.h)

add_executable(graph_test ${SRC} ${INC})

target_compile_features(graph_test PUBLIC cxx_std_17)

cmake_minimum_required(VERSION 3.5)

project(graph_lib LANGUAGES CXX)

set(SRC graph_test.cpp)
set(INC graph.hpp graph_as_dot.hpp)

add_executable(graph_test ${SRC} ${INC})
include_directories(graph_test PRIVATE /usr/local/include)

add_executable(graph_jazzon graph_jazzon.cpp)
target_compile_features(graph_test PUBLIC cxx_std_17)
target_compile_features(graph_jazzon PUBLIC cxx_std_17)

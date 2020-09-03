cmake_minimum_required(VERSION 3.5)

project(graph_lib LANGUAGES CXX)

set(SRC graph.cpp)
set(INC graph.h)

add_library(graph_lib SHARED ${SRC} ${INC})

add_executable(graph_test graph_test.cpp ${INC})

target_link_libraries(graph_test graph_lib)

target_compile_features(graph_lib PUBLIC cxx_std_17)

target_compile_features(graph_test PUBLIC cxx_std_17)

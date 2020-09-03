cmake_minimum_required(VERSION 3.5.0)
project(client LANGUAGES CXX)

add_executable(websocket_client websocket_client.cpp)

target_compile_features(websocket_client PUBLIC cxx_std_17)

target_include_directories(websocket_client PUBLIC /usr/local/include/)

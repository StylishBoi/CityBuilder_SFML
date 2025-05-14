cmake_minimum_required(VERSION 3.30)
project(city_builder)

set(CMAKE_CXX_STANDARD 20)

#Package : external libraries managed by
find_package(SFML COMPONENTS Graphics Window System REQUIRED)

add_subdirectory(core/)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(city_builder main.cc)

target_link_libraries(city_builder PRIVATE core SFML::Graphics SFML::Window SFML::System)

cmake_minimum_required(VERSION 3.30)
project(CityBuilder)

set(CMAKE_CXX_STANDARD 20)

#Package : external libraries managed by
find_package(SFML COMPONENTS Graphics Window System REQUIRED)

add_subdirectory(core/)
add_subdirectory(game/)


file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(CityBuilder main.cc
        core/src/map_generation.cc)

target_link_libraries(CityBuilder PRIVATE game core SFML::System SFML::Graphics SFML::Window)

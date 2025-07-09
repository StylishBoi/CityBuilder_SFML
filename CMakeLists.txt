cmake_minimum_required(VERSION 3.30)

option(ENABLE_TESTING "Enable gtest" OFF)
if(ENABLE_TESTING)
    list(APPEND VCPKG_MANIFEST_FEATURES "testing")
endif(ENABLE_TESTING)

option(ENABLE_PROFILING "Enable tracy" OFF)
if(ENABLE_PROFILING)
    list(APPEND VCPKG_MANIFEST_FEATURES "profiling")
endif(ENABLE_PROFILING)

project(CityBuilder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(ENABLE_TESTING)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
endif(ENABLE_TESTING)

if(ENABLE_PROFILING)
    find_package(Tracy CONFIG REQUIRED)
endif(ENABLE_PROFILING)

add_subdirectory(core/)
add_subdirectory(api/)
add_subdirectory(game/)

file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_assets")
file(COPY ${CMAKE_SOURCE_DIR}/_assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(CityBuilder main.cc)

target_link_libraries(CityBuilder PRIVATE game)

target_compile_options(CityBuilder PRIVATE
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Od /Zi>
        $<$<AND:$<CONFIG:Debug>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-g -O0>
)

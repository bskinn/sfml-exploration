cmake_minimum_required(VERSION 3.28)
project(sfml--rgb-canvas LANGUAGES CXX VERSION 0.1.0)

# Global build output settings, for now
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/static)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(shape-demo
    src/shape_demo/demo.cpp
    src/shape_demo/helper/demo_helper.cpp
)

add_library(sfml--rgb-canvas
    src/canvas/canvas.cpp
    src/canvas/helper.cpp
)

target_compile_features(sfml--rgb-canvas PUBLIC cxx_std_17)
target_link_libraries(sfml--rgb-canvas PUBLIC SFML::Graphics)

target_compile_features(shape-demo PRIVATE cxx_std_17)
target_link_libraries(shape-demo PRIVATE sfml--rgb-canvas)

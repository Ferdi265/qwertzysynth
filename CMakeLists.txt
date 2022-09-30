cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(sdl-3dtest CXX)

# dependencies
find_package(SDL2 REQUIRED)
find_package(fmt REQUIRED)

# project
add_executable(3dtest)

# compile options
target_compile_options(3dtest PRIVATE -Wall -Wextra)
set_property(TARGET 3dtest PROPERTY CXX_STANDARD 20)
set_property(TARGET 3dtest PROPERTY CXX_STANDARD_REQUIRED ON)

# sources
file(GLOB 3dtest-sources src/*.cpp)
target_sources(3dtest PRIVATE ${3dtest-sources})
target_include_directories(3dtest PRIVATE include/)

# embedded files
add_subdirectory(embed)

# libraries
target_include_directories(3dtest PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(3dtest PRIVATE ${SDL2_LIBRARIES} fmt::fmt)

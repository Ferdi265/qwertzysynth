cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(qwertzysynth CXX)

# dependencies
find_package(SDL2 REQUIRED)
find_package(fmt REQUIRED)

# local dependencies
add_subdirectory(lib)

# project
add_executable(qwertzysynth)

# compile options
target_compile_options(qwertzysynth PRIVATE -Wall -Wextra)
set_property(TARGET qwertzysynth PROPERTY CXX_STANDARD 20)
set_property(TARGET qwertzysynth PROPERTY CXX_STANDARD_REQUIRED ON)

# sources
file(GLOB qwertzysynth-sources CONFIGURE_DEPENDS src/*.cpp)
target_sources(qwertzysynth PRIVATE ${qwertzysynth-sources})
target_compile_options(qwertzysynth PRIVATE -UNDEBUG)
target_include_directories(qwertzysynth PRIVATE include/)

# embedded files
add_subdirectory(embed)

# libraries
target_include_directories(qwertzysynth PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(qwertzysynth PRIVATE ${SDL2_LIBRARIES} fmt::fmt imgui cxx_lockfree_ring_queue)

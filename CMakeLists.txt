cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(sdl-musictest CXX)

# dependencies
find_package(SDL2 REQUIRED)
find_package(fmt REQUIRED)

# project
add_executable(musictest)

# compile options
target_compile_options(musictest PRIVATE -Wall -Wextra)
set_property(TARGET musictest PROPERTY CXX_STANDARD 20)
set_property(TARGET musictest PROPERTY CXX_STANDARD_REQUIRED ON)

# sources
file(GLOB musictest-sources CONFIGURE_DEPENDS src/*.cpp)
target_sources(musictest PRIVATE ${musictest-sources})
target_compile_options(musictest PRIVATE -UNDEBUG)
target_include_directories(musictest PRIVATE include/)

# embedded files
add_subdirectory(embed)

# libraries
target_include_directories(musictest PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(musictest PRIVATE ${SDL2_LIBRARIES} fmt::fmt)

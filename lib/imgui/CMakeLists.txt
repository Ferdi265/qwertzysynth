project(imgui CXX)

find_package(SDL2 REQUIRED)

file(GLOB imgui-sources CONFIGURE_DEPENDS *.cpp)
add_library(imgui STATIC ${imgui-sources})
target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(imgui PUBLIC ${SDL2_LIBRARIES})

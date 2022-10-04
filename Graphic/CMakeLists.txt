# CMakeList.txt : CMake project for Graphic, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Graphic "Graphic.hpp" "common.h" )

find_package(glad CONFIG REQUIRED)
target_link_libraries(Graphic PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Graphic PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(Graphic PRIVATE imgui::imgui)

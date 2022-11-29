# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)
project ("Triviador")

# Include sub-projects.
add_subdirectory ("Triviador")

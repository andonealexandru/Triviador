cmake_minimum_required (VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)
project ("Triviador")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory ("Triviador")

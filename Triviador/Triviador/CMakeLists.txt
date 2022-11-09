# CMakeList.txt : CMake project for Triviador, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.

#set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_executable (Triviador 
	"src/Triviador.cpp" 
	"include/Triviador.h"
)

add_subdirectory("UI")
add_subdirectory("Database")

# TODO: Add tests and install targets if needed.
# CMakeList.txt : CMake project for Triviador, include source and define
# project specific logic here.


# Add source to this project's executable.

add_executable (Triviador
	"Triviador.h"
	"Triviador.cpp"

)

add_subdirectory("UI")
add_subdirectory("Database")

# TODO: Add tests and install targets if needed
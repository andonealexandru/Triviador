find_package(Crow CONFIG REQUIRED)

add_executable (Triviador
	"Triviador.h"
	"Triviador.cpp"
)

add_subdirectory("UI")
add_subdirectory("Database")
add_subdirectory("Server")

target_link_libraries(Triviador
	PRIVATE
		Database
		Server
)

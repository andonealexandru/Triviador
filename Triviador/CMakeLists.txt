add_executable (Triviador
	"Triviador.h"
	"Triviador.cpp"
)

add_subdirectory("UI")
add_subdirectory("Database")
add_subdirectory("Server")
add_subdirectory("Validator")

target_link_libraries(Triviador
	PRIVATE
		Database
		Server
)

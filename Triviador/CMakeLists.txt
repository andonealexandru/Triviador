add_executable (Triviador
	"Triviador.h"
	"Triviador.cpp"
)

add_subdirectory("UI")
add_subdirectory("Database")

target_link_libraries(Triviador
	PRIVATE
		Database
)

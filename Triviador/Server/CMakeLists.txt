find_package(Crow CONFIG REQUIRED)

add_library(Server STATIC
    #*.h
    "include/Backend.h"
    "include/Lobby.h"
    "include/Player.h"
    #.cpp
    "src/Backend.cpp"
    "src/Lobby.cpp"
    "src/Player.cpp"
)

target_link_libraries(Server
    PRIVATE
        Database
        Crow::Crow
)

target_include_directories(Server
    PUBLIC 
    "include" 
    PRIVATE 
    "include" 
    "src"
)
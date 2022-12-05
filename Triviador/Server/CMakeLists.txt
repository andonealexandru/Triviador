find_package(Crow CONFIG REQUIRED)
find_package(SqliteOrm CONFIG REQUIRED)

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
    PUBLIC
        Crow::Crow
        sqlite_orm::sqlite_orm
)

target_include_directories(Server
    PUBLIC 
    "include" 
    PRIVATE 
    "include" 
    "src"
)
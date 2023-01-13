find_package(Crow CONFIG REQUIRED)

add_library(Server STATIC
    #*.h
    "include/Status.h"
    "include/Backend.h"
    "include/Player.h"
    "include/Map.h"
    "include/Region.h"
    "include/BaseChoiceService.h"
    "include/PlayerService.h"
    #.cpp
    "src/Backend.cpp"
    "src/Player.cpp"
    "src/Map.cpp"
    "src/Region.cpp"
    "src/BaseChoiceService.cpp"
    "src/PlayerService.cpp"
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
find_package(Crow CONFIG REQUIRED)

add_library(Server STATIC
    #*.h
    "include/Backend.h"
    "include/Player.h"
    "include/Question.h"
    "include/QuestionChoice.h"
    #.cpp
    "src/Backend.cpp"
    "src/Player.cpp"
    "src/Question.cpp"
    "src/QuestionChoice.cpp"
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
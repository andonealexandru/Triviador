find_package(SqliteOrm CONFIG REQUIRED)

add_library(Database STATIC
    #*.h   
    "include/User.h"  
    "include/DBAccess.h"
    "include/Question.h"
    "include/QuestionChoice.h"
    "include/UserStatistics.h"
    #.cpp
    "src/DBAccess.cpp"
    "src/Question.cpp"
    "src/QuestionChoice.cpp"
    "src/UserStatistics.cpp"
    "src/User.cpp"
)

target_link_libraries(Database
    PUBLIC
        sqlite_orm::sqlite_orm
)


target_include_directories(Database
    PUBLIC 
    "include" 
    PRIVATE 
    "include" 
    "src"
)

set(PATH_TO_DATABASE "${CMAKE_CURRENT_SOURCE_DIR}/Triviador.sqlite")
add_definitions(-DDATABASE_PATH="${PATH_TO_DATABASE}")

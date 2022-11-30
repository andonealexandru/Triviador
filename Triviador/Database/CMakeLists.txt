find_package(Crow CONFIG REQUIRED)
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
        Crow::Crow
        sqlite_orm::sqlite_orm
)


target_include_directories(Database
    PUBLIC 
    "include" 
    PRIVATE 
    "include" 
    "src"
)

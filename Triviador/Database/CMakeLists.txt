include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)
find_package(SqliteOrm CONFIG REQUIRED)

add_library(Database STATIC
    #*.h
    "include/Game.h"
    "include/Question.h"
    "include/QuestionChoice.h"
    "include/User.h"
    "include/UserStatistics.h"
    "include/DBAccess.h"
    #.cpp
    "src/Game.cpp"
    "src/Question.cpp"
    "src/QuestionChoice.cpp"
    "src/User.cpp"
    "src/UserStatistics.cpp"
    "src/DBAccess.cpp"
    "src/main.cpp"
        )
target_link_libraries(Database PUBLIC sqlite_orm::sqlite_orm)

target_include_directories(Database
    PUBLIC 
    "include" 
    PRIVATE 
    "include" 
    "src"
)

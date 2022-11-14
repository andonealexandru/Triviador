include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)
find_package(SqliteOrm CONFIG REQUIRED)

add_executable(Database
    #*.h
    "include/Game.h"
    "include/Question.h"
    "include/QuestionChoice.h"
    "include/User.h"
    "include/UserStatistics.h"
    #.cpp
    "src/Game.cpp"
    "src/Question.cpp"
    "src/QuestionChoice.cpp"
    "src/User.cpp"
    "src/UserStatistics.cpp"
    "src/main.cpp"
)

target_link_libraries(Database PRIVATE sqlite_orm::sqlite_orm)

target_include_directories(Database
    PUBLIC 
    "include" 
    PRIVATE 
    "include" 
    "src"
)

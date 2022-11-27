include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)


find_package(SqliteOrm CONFIG REQUIRED)
find_package(Crow CONFIG REQUIRED)

add_library(Database STATIC
    #*.h
    "include/Game.h"
    "include/Question.h"
    "include/QuestionChoice.h"
    "include/User.h"
    "include/UserService.h"
    "include/UserStatistics.h"
    "include/DBAccess.h"
    "include/QuestionService.h"
    "include/QuestionChoiceService.h"
    "include/UserStatisticsService.h"
    "include/GameService.h"
    #.cpp
    "src/Game.cpp"
    "src/Question.cpp"
    "src/QuestionChoice.cpp"
    "src/User.cpp"
    "src/UserStatistics.cpp"
    "src/DBAccess.cpp"
    "src/QuestionService.cpp"
    "src/QuestionChoiceService.cpp"
    "src/UserStatisticsService.cpp"
    "src/GameService.cpp"
    "src/UserService.cpp"
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

#include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)
find_package(SqliteOrm CONFIG REQUIRED)

add_executable(Database
    "src/main.cpp"
)

target_link_libraries(Database PRIVATE sqlite_orm::sqlite_orm)

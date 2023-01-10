SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(Validator SHARED
    src/Validator.cpp
    include/Validator.h
)

target_include_directories(Validator
    PUBLIC
        include
    PRIVATE
        include
        src
)

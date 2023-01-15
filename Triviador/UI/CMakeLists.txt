find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

#=================== INCLUSION OF Project Files ====================#
set(FORMS_DIR "forms")
set(INCLUDE_DIR "include")
set(SOURCE_DIR "src")

include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "${FORMS_DIR}/*.ui"
    "${FORMS_DIR}/*.qrc"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

# Add the executable
add_executable(GUI ${SOURCES})

target_include_directories(GUI 
    PUBLIC
        ${INCLUDE_DIR}
    PRIVATE 
        ${FORMS_DIR}
        ${INCLUDE_DIR}
        ${SOURCE_DIR}
)

#===================== LINKING LIBRARIES =======================#
target_link_libraries(GUI
        Qt6::Widgets
        Database
        cpr::cpr
        nlohmann_json::nlohmann_json
        Validator
)

add_definitions(-DRESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources")

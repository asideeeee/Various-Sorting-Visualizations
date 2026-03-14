cmake_minimum_required(VERSION 3.16)

project(SortingVisualizer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# Include directories
include_directories(include)

# Find sources
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INC_FILES include/*.h)
file(GLOB_RECURSE UI_FILES ui/*.ui)

add_executable(${PROJECT_NAME} 
    ${SRC_FILES} 
    ${INC_FILES} 
    ${UI_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt5::Core 
    Qt5::Gui 
    Qt5::Widgets
)

# Force macOS to not use AGL framework if Qt falls back to it in older versions
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
endif()
